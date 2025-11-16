# Quick Start Guide

## Prerequisites
- Windows computer with the camera connected via USB
- Visual Studio 2015 or later (or Visual Studio Build Tools)

## Building the Application

### Easiest Method: Visual Studio Solution

1. Double-click `CameraControlTest.sln` to open in Visual Studio
2. Select **Release** or **Debug** configuration (x64)
3. Press **F7** or go to **Build > Build Solution**
4. The executable will be in `x64\Release\` or `x64\Debug\` folder

### Alternative: Command Line

1. Open **Developer Command Prompt for VS** (search for it in Start menu)
2. Navigate to the `camera_control_test` directory
3. Run: `build.bat`
4. The executable `CameraControlTest.exe` will be created in the same directory

## Running the Application

1. Make sure `CameraCtrl.dll` is in the same directory as `CameraControlTest.exe`
   - If using Visual Studio, the DLL is automatically copied to the output folder
   - If using build.bat, the DLL should already be in the same directory

2. Connect your camera via USB to the Windows computer

3. Run `CameraControlTest.exe`

4. Follow the menu:
   - First, select option **1** to list available cameras
   - Then, select option **2** to connect to a camera
   - After connecting, you can test various controls (options 3-10)

## Testing Camera Controls

### Basic Test Sequence:
1. **List cameras** (option 1) - Verify camera is detected
2. **Connect to camera** (option 2) - Select camera index from list
3. **Test PTZ** (option 3) - Try pan, tilt, zoom movements
4. **Get properties** (option 7) - View current camera settings
5. **Test image settings** (option 5) - Adjust brightness, contrast, etc.

### What to Verify:
- ✅ Camera is detected in the list
- ✅ Connection succeeds
- ✅ PTZ movements work (pan, tilt, zoom)
- ✅ Focus controls respond
- ✅ Image settings can be changed
- ✅ Camera features (flip, mirror, etc.) work

## Troubleshooting

**"No cameras found"**
- Check USB connection
- Verify camera is recognized in Windows Device Manager
- Camera must support UVC extension units

**"Failed to connect"**
- Try a different USB port
- Check if camera is being used by another application
- Verify camera PID matches SDK requirements (8888, 7588, 9999, or 00f9)

**"DLL not found" error**
- Ensure `CameraCtrl.dll` is in the same folder as the executable
- Check Windows PATH if error persists

**Build errors**
- Make sure you're using Visual Studio Developer Command Prompt
- Verify all SDK files (CameraCtrl.h, CameraCtrl.lib, CameraCtrl.dll) are present
- Check that you have Windows SDK installed

## Next Steps

Once you've verified the camera controls work:
1. Note which features work and which don't
2. Test all PTZ movements
3. Verify image settings can be adjusted
4. Test presets if your camera supports them
5. Then proceed to set up server/client architecture for remote control

