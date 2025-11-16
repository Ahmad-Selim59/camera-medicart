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

### For Windows 7 or Minimal Setup (Recommended)

**Easiest Method: Install TDM-GCC (Free, ~100MB)**

1. Download TDM-GCC from: https://jmeubank.github.io/tdm-gcc/
2. Install it (make sure "Add to PATH" is checked)
3. Open Command Prompt in the `camera_control_test` directory
4. Run: `compile_simple.bat` (or double-click it)
5. Done! See `WINDOWS7_SETUP.txt` for detailed instructions

**Alternative: Use build_mingw.bat**
```
build_mingw.bat
```

### Option 1: Using Visual Studio (Windows 8+)

1. Open **Developer Command Prompt for VS** (or Visual Studio x64 Native Tools Command Prompt)
2. Navigate to the `camera_control_test` directory
3. Run:
   ```
   build.bat
   ```

### Option 2: Using CMake

1. Open CMake GUI or use command line
2. Set source directory to `camera_control_test`
3. Set build directory (e.g., `camera_control_test/build`)
4. Configure and Generate
5. Open the generated solution in Visual Studio and build

### Option 3: Manual Compilation (MinGW/GCC)

From Command Prompt (after installing MinGW or TDM-GCC):
```
g++ -std=c++11 -Wall -O2 main.cpp -o CameraControlTest.exe CameraCtrl.lib -lstrmiids -lws2_32 -lole32 -loleaut32 -ladvapi32
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
- C++ Compiler (choose one):
  - **TDM-GCC** (recommended for Windows 7, free, ~100MB) - https://jmeubank.github.io/tdm-gcc/
  - **MinGW-w64** (free, lightweight)
  - **Visual Studio** (Windows 8+, larger download)
- Camera connected via USB
- Camera must support UVC extension units

**For Windows 7 users:** See `WINDOWS7_SETUP.txt` for detailed setup instructions.

## Troubleshooting

- **"No cameras found"**: Make sure the camera is connected via USB and recognized by Windows
- **"Failed to connect"**: The camera may not support the required UVC extension units
- **"DLL not found"**: Make sure `CameraCtrl.dll` is in the same directory as the executable
- **Build errors**: Make sure you're using Visual Studio Developer Command Prompt with proper environment variables set

## Notes

- This is a test application to verify the SDK functionality
- All camera controls are tested through the SDK's UVC interface
- The application uses a simple console menu interface for easy testing

