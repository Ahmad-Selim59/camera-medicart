#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "../Cameralib/CameraCtrl.h"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void print_error(const std::string& code, const std::string& message) {
    std::cout << "DATA:ERROR code=" << code << " message=\"" << message << "\"\n";
}

static void print_ok(const std::string& command) {
    std::cout << "DATA:OK command=" << command << "\n";
}

static void print_help() {
    std::cout
        << "Camera CLI (CameraCtrl.dll wrapper)\n"
        << "Usage:\n"
        << "  camera_cli.exe -help\n"
        << "  camera_cli.exe -list\n"
        << "  camera_cli.exe -move-right\n"
        << "  camera_cli.exe -move-left\n"
        << "  camera_cli.exe -move-up\n"
        << "  camera_cli.exe -move-down\n"
        << "\n"
        << "Commands:\n"
        << "  -help         Show this help text in a human‑readable form.\n"
        << "  -list         List all detected compatible cameras.\n"
        << "  -move-right   Pan camera to the right briefly.\n"
        << "  -move-left    Pan camera to the left briefly.\n"
        << "  -move-up      Tilt camera up briefly.\n"
        << "  -move-down    Tilt camera down briefly.\n"
        << "\n"
        << "Machine‑readable output (for non‑help commands):\n"
        << "  Success lines start with:   DATA:OK ...\n"
        << "  Error lines start with:     DATA:ERROR code=... message=\"...\"\n"
        << "  List command:\n"
        << "    DATA:LIST count=N\n"
        << "    DATA:CAMERA index=i id=deviceId name=\"...\" path=\"...\"\n";
}

// Ensure exactly one camera is present. Fills deviceList on success.
static bool ensure_single_camera(DeviceList& deviceList, std::string& errorCode, std::string& errorMsg) {
    deviceList.clear();

    if (!BaseDevice::EnumUSBDevices(deviceList)) {
        errorCode = "ENUM_FAILED";
        errorMsg = "EnumUSBDevices returned false";
        return false;
    }

    if (deviceList.empty()) {
        errorCode = "NO_CAMERA";
        errorMsg = "No compatible camera detected";
        return false;
    }

    if (deviceList.size() > 1) {
        errorCode = "MULTIPLE_CAMERAS";
        errorMsg = "More than one compatible camera detected";
        return false;
    }

    return true;
}

// Open the single detected camera and return a BaseDevice*. Caller owns it.
static BaseDevice* open_single_camera(const DeviceList& deviceList, std::string& errorCode, std::string& errorMsg) {
    if (deviceList.empty()) {
        errorCode = "NO_CAMERA";
        errorMsg = "No compatible camera detected";
        return nullptr;
    }

    const DeviceInfo& info = deviceList[0];

    BaseDevice* device = BaseDevice::CreateDevice(DeviceType::USB_Device);
    if (!device) {
        errorCode = "CREATE_DEVICE_FAILED";
        errorMsg = "BaseDevice::CreateDevice returned null";
        return nullptr;
    }

    char idBuf[16];
    // The SDK uses the index (DeviceId) as a string when opening.
    std::snprintf(idBuf, sizeof(idBuf), "%u", info.DeviceId);

    if (!device->OpenDevice(idBuf)) {
        errorCode = "OPEN_FAILED";
        errorMsg = "Failed to open camera device";
        BaseDevice::DeleteDevice(device);
        return nullptr;
    }

    return device;
}

// Perform a short relative move; used for pan/tilt commands.
static bool do_relative_move(BaseDevice* dev,
                             const std::string& cmd,
                             int speed,
                             int durationMs,
                             std::string& errorCode,
                             std::string& errorMsg) {
    bool ok = false;

    if (cmd == "-move-right") {
        ok = dev->StartMoveRight(speed);
        if (!ok) { errorCode = "MOVE_FAILED"; errorMsg = "StartMoveRight failed"; return false; }
        Sleep(durationMs);
        dev->StopMoveRight();
    } else if (cmd == "-move-left") {
        ok = dev->StartMoveLeft(speed);
        if (!ok) { errorCode = "MOVE_FAILED"; errorMsg = "StartMoveLeft failed"; return false; }
        Sleep(durationMs);
        dev->StopMoveLeft();
    } else if (cmd == "-move-up") {
        ok = dev->StartMoveUp(speed);
        if (!ok) { errorCode = "MOVE_FAILED"; errorMsg = "StartMoveUp failed"; return false; }
        Sleep(durationMs);
        dev->StopMoveUp();
    } else if (cmd == "-move-down") {
        ok = dev->StartMoveDown(speed);
        if (!ok) { errorCode = "MOVE_FAILED"; errorMsg = "StartMoveDown failed"; return false; }
        Sleep(durationMs);
        dev->StopMoveDown();
    } else {
        errorCode = "UNKNOWN_COMMAND";
        errorMsg = "Internal error: unsupported move command";
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string cmd = argv[1];
    if (cmd == "-help" || cmd == "--help" || cmd == "/?") {
        print_help();
        return 0;
    }

    // Only DATA: lines will be printed from here on.

    // Initialize SDK (COM / Winsock)
    BaseDevice::Initial();

    int exitCode = 0;
    std::string errorCode;
    std::string errorMsg;

    if (cmd == "-list") {
        DeviceList deviceList;
        if (!BaseDevice::EnumUSBDevices(deviceList)) {
            print_error("ENUM_FAILED", "EnumUSBDevices returned false");
            BaseDevice::Release();
            return 1;
        }

        std::cout << "DATA:LIST count=" << deviceList.size() << "\n";
        for (size_t i = 0; i < deviceList.size(); ++i) {
            const DeviceInfo& d = deviceList[i];
            std::cout << "DATA:CAMERA index=" << i
                      << " id=" << d.DeviceId
                      << " name=\"" << d.Name << "\""
                      << " path=\"" << d.Path << "\"\n";
        }

        BaseDevice::Release();
        return 0;
    }

    // For movement commands we require exactly one camera.
    DeviceList deviceList;
    if (!ensure_single_camera(deviceList, errorCode, errorMsg)) {
        print_error(errorCode, errorMsg);
        BaseDevice::Release();
        return 1;
    }

    BaseDevice* dev = open_single_camera(deviceList, errorCode, errorMsg);
    if (!dev) {
        print_error(errorCode, errorMsg);
        BaseDevice::Release();
        return 1;
    }

    // Default movement parameters.
    const int speed = 5;
    const int durationMs = 500; // move for 0.5s then stop

    if (cmd == "-move-right" || cmd == "-move-left" || cmd == "-move-up" || cmd == "-move-down") {
        if (!do_relative_move(dev, cmd, speed, durationMs, errorCode, errorMsg)) {
            print_error(errorCode, errorMsg);
            exitCode = 1;
        } else {
            // Strip leading '-' for the success command name
            std::string name = cmd;
            if (!name.empty() && name[0] == '-') {
                name = name.substr(1);
            }
            print_ok(name);
        }
    } else {
        print_error("UNKNOWN_COMMAND", "Unsupported command: " + cmd);
        exitCode = 1;
    }

    // Cleanup
    dev->CloseDevice();
    BaseDevice::DeleteDevice(dev);
    BaseDevice::Release();

    return exitCode;
}


