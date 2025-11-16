#include <iostream>
#include <string>
#include <windows.h>
#include "CameraCtrl.h"

// Helper function to clear screen
void ClearScreen() {
    system("cls");
}

// Helper function to wait for user input
void WaitForInput() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Display menu
void DisplayMenu() {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Camera Control Test Application\n";
    std::cout << "========================================\n\n";
    std::cout << "1.  List available cameras\n";
    std::cout << "2.  Connect to camera\n";
    std::cout << "3.  Test PTZ Controls (Pan/Tilt/Zoom)\n";
    std::cout << "4.  Test Focus Controls\n";
    std::cout << "5.  Test Image Settings\n";
    std::cout << "6.  Test Camera Features\n";
    std::cout << "7.  Get Camera Properties\n";
    std::cout << "8.  Test Presets\n";
    std::cout << "9.  Get Pan/Tilt Position\n";
    std::cout << "10. Set Pan/Tilt Position\n";
    std::cout << "0.  Exit\n";
    std::cout << "\nSelect option: ";
}

// List available cameras
void ListCameras(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Available Cameras\n";
    std::cout << "========================================\n\n";
    
    DeviceList deviceList;
    if (BaseDevice::EnumUSBDevices(deviceList)) {
        if (deviceList.empty()) {
            std::cout << "No cameras found!\n";
        } else {
            for (size_t i = 0; i < deviceList.size(); i++) {
                std::cout << "[" << i << "] " << deviceList[i].Name << "\n";
                std::cout << "    Path: " << deviceList[i].Path << "\n\n";
            }
        }
    } else {
        std::cout << "Failed to enumerate cameras!\n";
    }
    WaitForInput();
}

// Connect to camera
bool ConnectToCamera(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Connect to Camera\n";
    std::cout << "========================================\n\n";
    
    DeviceList deviceList;
    if (!BaseDevice::EnumUSBDevices(deviceList) || deviceList.empty()) {
        std::cout << "No cameras found!\n";
        WaitForInput();
        return false;
    }
    
    std::cout << "Available cameras:\n";
    for (size_t i = 0; i < deviceList.size(); i++) {
        std::cout << "[" << i << "] " << deviceList[i].Name << "\n";
    }
    
    std::cout << "\nEnter camera index: ";
    int index;
    std::cin >> index;
    
    if (index < 0 || index >= (int)deviceList.size()) {
        std::cout << "Invalid index!\n";
        WaitForInput();
        return false;
    }
    
    char deviceId[10];
    sprintf_s(deviceId, sizeof(deviceId), "%d", index);
    
    if (device->OpenDevice(deviceId)) {
        std::cout << "Successfully connected to: " << deviceList[index].Name << "\n";
        device->GetPropertyValues();
        WaitForInput();
        return true;
    } else {
        std::cout << "Failed to connect to camera!\n";
        WaitForInput();
        return false;
    }
}

// Test PTZ controls
void TestPTZ(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   PTZ Control Test\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Pan Left\n";
    std::cout << "2. Pan Right\n";
    std::cout << "3. Tilt Up\n";
    std::cout << "4. Tilt Down\n";
    std::cout << "5. Zoom In (Tele)\n";
    std::cout << "6. Zoom Out (Wide)\n";
    std::cout << "7. Stop All Movement\n";
    std::cout << "0. Back\n";
    std::cout << "\nSelect option: ";
    
    int choice;
    std::cin >> choice;
    
    int speed = 5; // Default speed
    
    switch (choice) {
    case 1:
        std::cout << "Panning left...\n";
        device->StartMoveLeft(speed);
        Sleep(1000);
        device->StopMoveLeft();
        break;
    case 2:
        std::cout << "Panning right...\n";
        device->StartMoveRight(speed);
        Sleep(1000);
        device->StopMoveRight();
        break;
    case 3:
        std::cout << "Tilting up...\n";
        device->StartMoveUp(speed);
        Sleep(1000);
        device->StopMoveUp();
        break;
    case 4:
        std::cout << "Tilting down...\n";
        device->StartMoveDown(speed);
        Sleep(1000);
        device->StopMoveDown();
        break;
    case 5:
        std::cout << "Zooming in...\n";
        device->StartZoomTele(speed);
        Sleep(1000);
        device->StopZoom();
        break;
    case 6:
        std::cout << "Zooming out...\n";
        device->StartZoomWide(speed);
        Sleep(1000);
        device->StopZoom();
        break;
    case 7:
        std::cout << "Stopping all movement...\n";
        device->StopMoveUp();
        device->StopMoveDown();
        device->StopMoveLeft();
        device->StopMoveRight();
        device->StopZoom();
        break;
    }
    
    if (choice != 0) {
        WaitForInput();
    }
}

// Test Focus controls
void TestFocus(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Focus Control Test\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Set Auto Focus\n";
    std::cout << "2. Set Manual Focus\n";
    std::cout << "3. Focus Near\n";
    std::cout << "4. Focus Far\n";
    std::cout << "5. Stop Focus\n";
    std::cout << "6. Get Focus Value\n";
    std::cout << "0. Back\n";
    std::cout << "\nSelect option: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
    case 1:
        std::cout << "Setting auto focus...\n";
        device->SetFocusAuto();
        break;
    case 2:
        std::cout << "Setting manual focus...\n";
        device->SetFocusManual();
        break;
    case 3:
        std::cout << "Focusing near...\n";
        device->StartFocusNear(5);
        Sleep(1000);
        device->StopFocus();
        break;
    case 4:
        std::cout << "Focusing far...\n";
        device->StartFocusFar(5);
        Sleep(1000);
        device->StopFocus();
        break;
    case 5:
        std::cout << "Stopping focus...\n";
        device->StopFocus();
        break;
    case 6: {
        long value;
        if (device->GetFocus(&value)) {
            std::cout << "Current focus value: " << value << "\n";
        } else {
            std::cout << "Failed to get focus value!\n";
        }
        break;
    }
    }
    
    if (choice != 0) {
        WaitForInput();
    }
}

// Test image settings
void TestImageSettings(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Image Settings Test\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Brightness\n";
    std::cout << "2. Contrast\n";
    std::cout << "3. Saturation\n";
    std::cout << "4. Sharpness\n";
    std::cout << "5. White Balance\n";
    std::cout << "6. Gain\n";
    std::cout << "0. Back\n";
    std::cout << "\nSelect option: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return;
    
    std::cout << "Enter value: ";
    int value;
    std::cin >> value;
    
    bool success = false;
    switch (choice) {
    case 1:
        success = device->SetBrightness(value);
        std::cout << (success ? "Brightness set successfully\n" : "Failed to set brightness\n");
        break;
    case 2:
        success = device->SetContrast(value);
        std::cout << (success ? "Contrast set successfully\n" : "Failed to set contrast\n");
        break;
    case 3:
        success = device->SetSaturation(value);
        std::cout << (success ? "Saturation set successfully\n" : "Failed to set saturation\n");
        break;
    case 4:
        success = device->SetSharpness(value);
        std::cout << (success ? "Sharpness set successfully\n" : "Failed to set sharpness\n");
        break;
    case 5:
        success = device->SetWhiteBalance(value);
        std::cout << (success ? "White balance set successfully\n" : "Failed to set white balance\n");
        break;
    case 6:
        success = device->SetGain(value);
        std::cout << (success ? "Gain set successfully\n" : "Failed to set gain\n");
        break;
    }
    
    WaitForInput();
}

// Test camera features
void TestCameraFeatures(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Camera Features Test\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Flip On\n";
    std::cout << "2. Flip Off\n";
    std::cout << "3. Mirror On\n";
    std::cout << "4. Mirror Off\n";
    std::cout << "5. Home Position\n";
    std::cout << "6. Freeze On\n";
    std::cout << "7. Freeze Off\n";
    std::cout << "8. IR On\n";
    std::cout << "9. IR Off\n";
    std::cout << "10. Day Mode\n";
    std::cout << "11. Night Mode\n";
    std::cout << "0. Back\n";
    std::cout << "\nSelect option: ";
    
    int choice;
    std::cin >> choice;
    
    bool success = false;
    switch (choice) {
    case 1:
        success = device->OpenFlip();
        break;
    case 2:
        success = device->CloseFlip();
        break;
    case 3:
        success = device->OpenMirror();
        break;
    case 4:
        success = device->CloseMirror();
        break;
    case 5:
        success = device->HomePosition();
        break;
    case 6:
        success = device->OpenFreeze();
        break;
    case 7:
        success = device->CloseFreeze();
        break;
    case 8:
        success = device->SetIRON();
        break;
    case 9:
        success = device->SetIROFF();
        break;
    case 10:
        success = device->SetIR_DAY_MODE();
        break;
    case 11:
        success = device->SetIR_NIGHT_MODE();
        break;
    }
    
    if (choice != 0) {
        std::cout << (success ? "Command executed successfully\n" : "Command failed\n");
        WaitForInput();
    }
}

// Get camera properties
void GetCameraProperties(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Camera Properties\n";
    std::cout << "========================================\n\n";
    
    device->GetPropertyValues();
    
    std::cout << "Brightness: " << device->Brightness.Current 
              << " (Min: " << device->Brightness.Min 
              << ", Max: " << device->Brightness.Max 
              << ", Default: " << device->Brightness.Default << ")\n";
    
    std::cout << "Contrast: " << device->Contrast.Current 
              << " (Min: " << device->Contrast.Min 
              << ", Max: " << device->Contrast.Max 
              << ", Default: " << device->Contrast.Default << ")\n";
    
    std::cout << "Saturation: " << device->Saturation.Current 
              << " (Min: " << device->Saturation.Min 
              << ", Max: " << device->Saturation.Max 
              << ", Default: " << device->Saturation.Default << ")\n";
    
    std::cout << "Sharpness: " << device->Sharpness.Current 
              << " (Min: " << device->Sharpness.Min 
              << ", Max: " << device->Sharpness.Max 
              << ", Default: " << device->Sharpness.Default << ")\n";
    
    std::cout << "White Balance: " << device->WhiteBalance.Current 
              << " (Min: " << device->WhiteBalance.Min 
              << ", Max: " << device->WhiteBalance.Max 
              << ", Default: " << device->WhiteBalance.Default << ")\n";
    
    std::cout << "Gain: " << device->Gain.Current 
              << " (Min: " << device->Gain.Min 
              << ", Max: " << device->Gain.Max 
              << ", Default: " << device->Gain.Default << ")\n";
    
    char* info = device->GetDeviceInfo();
    if (info) {
        std::cout << "\nDevice Info: " << info << "\n";
    }
    
    WaitForInput();
}

// Test presets
void TestPresets(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Preset Test\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Set Preset (0-255)\n";
    std::cout << "2. Call Preset (0-255)\n";
    std::cout << "3. Clear Preset (0-255)\n";
    std::cout << "0. Back\n";
    std::cout << "\nSelect option: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) return;
    
    std::cout << "Enter preset number (0-255): ";
    int preset;
    std::cin >> preset;
    
    if (preset < 0 || preset > 255) {
        std::cout << "Invalid preset number!\n";
        WaitForInput();
        return;
    }
    
    bool success = false;
    switch (choice) {
    case 1:
        success = device->SetPreset((unsigned char)preset);
        std::cout << (success ? "Preset set successfully\n" : "Failed to set preset\n");
        break;
    case 2:
        success = device->CallPreset((unsigned char)preset);
        std::cout << (success ? "Preset called successfully\n" : "Failed to call preset\n");
        break;
    case 3:
        success = device->ClearPreset((unsigned char)preset);
        std::cout << (success ? "Preset cleared successfully\n" : "Failed to clear preset\n");
        break;
    }
    
    WaitForInput();
}

// Get Pan/Tilt position
void GetPanTiltPosition(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Get Pan/Tilt Position\n";
    std::cout << "========================================\n\n";
    
    long pan, tilt, roll;
    bool panOk = device->GetPan(&pan);
    bool tiltOk = device->GetTilt(&tilt);
    bool rollOk = device->GetRoll(&roll);
    
    if (panOk) {
        std::cout << "Pan: " << pan << "\n";
    } else {
        std::cout << "Failed to get Pan\n";
    }
    
    if (tiltOk) {
        std::cout << "Tilt: " << tilt << "\n";
    } else {
        std::cout << "Failed to get Tilt\n";
    }
    
    if (rollOk) {
        std::cout << "Roll: " << roll << "\n";
    } else {
        std::cout << "Failed to get Roll\n";
    }
    
    WaitForInput();
}

// Set Pan/Tilt position
void SetPanTiltPosition(BaseDevice* device) {
    ClearScreen();
    std::cout << "========================================\n";
    std::cout << "   Set Pan/Tilt Position\n";
    std::cout << "========================================\n\n";
    
    std::cout << "Enter Pan value: ";
    long pan;
    std::cin >> pan;
    
    std::cout << "Enter Tilt value: ";
    long tilt;
    std::cin >> tilt;
    
    bool panOk = device->SetPan(pan);
    Sleep(50);
    bool tiltOk = device->SetTilt(tilt);
    
    if (panOk && tiltOk) {
        std::cout << "Position set successfully\n";
    } else {
        std::cout << "Failed to set position (Pan: " << (panOk ? "OK" : "FAIL") 
                  << ", Tilt: " << (tiltOk ? "OK" : "FAIL") << ")\n";
    }
    
    WaitForInput();
}

int main() {
    // Initialize the SDK
    BaseDevice::Initial();
    
    // Create device instance
    BaseDevice* device = BaseDevice::CreateDevice(DeviceType::USB_Device);
    if (!device) {
        std::cout << "Failed to create device instance!\n";
        return 1;
    }
    
    bool connected = false;
    int choice;
    
    while (true) {
        DisplayMenu();
        std::cin >> choice;
        
        switch (choice) {
        case 1:
            ListCameras(device);
            break;
        case 2:
            connected = ConnectToCamera(device);
            break;
        case 3:
            if (connected) {
                TestPTZ(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 4:
            if (connected) {
                TestFocus(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 5:
            if (connected) {
                TestImageSettings(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 6:
            if (connected) {
                TestCameraFeatures(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 7:
            if (connected) {
                GetCameraProperties(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 8:
            if (connected) {
                TestPresets(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 9:
            if (connected) {
                GetPanTiltPosition(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 10:
            if (connected) {
                SetPanTiltPosition(device);
            } else {
                std::cout << "Please connect to a camera first!\n";
                WaitForInput();
            }
            break;
        case 0:
            // Cleanup
            if (connected) {
                device->CloseDevice();
            }
            BaseDevice::DeleteDevice(device);
            BaseDevice::Release();
            return 0;
        default:
            std::cout << "Invalid option!\n";
            WaitForInput();
            break;
        }
    }
    
    return 0;
}

