# Camera Control Test Application

This is a simple console-based test application to verify camera controls using the CameraCtrl SDK.

## Files Included

- `main.cpp` - Main test application source code
- `CameraCtrl.h` - SDK header file
- `CameraCtrl.dll` - SDK dynamic library (required at runtime)
- `CameraCtrl.lib` - SDK import library (required for linking)
- `CMakeLists.txt` - CMake build configuration
- `build.bat` - Simple batch file for Visual Studio compilation

## Building the Application

### Using Visual Studio (Recommended)

1. Open **Developer Command Prompt for VS** (or Visual Studio x64 Native Tools Command Prompt)
   - Search for "Developer Command Prompt for VS" in Start Menu
   - Or "x64 Native Tools Command Prompt for VS"
2. Navigate to the `camera_control_test` directory
3. Run:
   ```
   build.bat
   ```
4. The executable `CameraControlTest.exe` will be created

### Alternative: Using Visual Studio IDE

1. Open Visual Studio
2. File > Open > CMake...
3. Select the `CMakeLists.txt` file in the `camera_control_test` directory
4. Build > Build All

### Manual Compilation (Visual Studio Command Line)

From Visual Studio Developer Command Prompt:
```
cl /EHsc /std:c++11 /O2 main.cpp CameraCtrl.lib strmiids.lib Ws2_32.lib ole32.lib oleaut32.lib Advapi32.lib /Fe:CameraControlTest.exe /link /SUBSYSTEM:CONSOLE
```

## Running the Application

1. Make sure `CameraCtrl.dll` is in the same directory as `CameraControlTest.exe`
2. Connect your camera via USB to the Windows computer
3. Run `CameraControlTest.exe`
4. Follow the menu to:
   - List available cameras
   - Connect to a camera
   - Test various camera controls

## Features Tested

- **Camera Enumeration**: List all connected USB cameras
- **PTZ Controls**: Pan, Tilt, Zoom
- **Focus Controls**: Auto/Manual focus, focus near/far
- **Image Settings**: Brightness, Contrast, Saturation, Sharpness, White Balance, Gain
- **Camera Features**: Flip, Mirror, Home Position, Freeze, IR controls
- **Presets**: Set, Call, Clear presets
- **Position Control**: Get/Set absolute Pan/Tilt positions

## Requirements

- Windows OS (Windows 7 or later)
- **Visual Studio** (2015 or later) with C++ support
  - Visual Studio Community (free)
  - Or Visual Studio Build Tools
- Camera connected via USB
- Camera must support UVC extension units

**Note:** You need to use Visual Studio Developer Command Prompt to run `build.bat`

## Troubleshooting

- **"No cameras found"**: Make sure the camera is connected via USB and recognized by Windows
- **"Failed to connect"**: The camera may not support the required UVC extension units
- **"DLL not found"**: Make sure `CameraCtrl.dll` is in the same directory as the executable
- **Build errors**: Make sure you're using Visual Studio Developer Command Prompt with proper environment variables set

## Notes

- This is a test application to verify the SDK functionality
- All camera controls are tested through the SDK's UVC interface
- The application uses a simple console menu interface for easy testing

