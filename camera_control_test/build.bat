@echo off
echo ========================================
echo Camera Control Test - Visual Studio Build
echo ========================================
echo.

REM 
where cl >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Visual Studio compiler (cl.exe) not found!
    echo.
    echo Please run this from a Visual Studio Developer Command Prompt.
    echo.
    echo To open Developer Command Prompt:
    echo 1. Open Start Menu
    echo 2. Search for "Developer Command Prompt for VS"
    echo 3. Or search for "x64 Native Tools Command Prompt"
    echo 4. Navigate to this folder and run build.bat
    echo.
    pause
    exit /b 1
)

REM 
if not exist CameraCtrl.dll (
    echo ERROR: CameraCtrl.dll not found!
    echo Make sure CameraCtrl.dll is in this folder.
    pause
    exit /b 1
)

if not exist CameraCtrl.lib (
    echo ERROR: CameraCtrl.lib not found!
    echo Make sure CameraCtrl.lib is in this folder.
    pause
    exit /b 1
)

echo Compiling and linking...
echo.

REM 
cl /EHsc /std:c++11 /O2 /W3 main.cpp CameraCtrl.lib strmiids.lib Ws2_32.lib ole32.lib oleaut32.lib Advapi32.lib /Fe:CameraControlTest.exe /link /SUBSYSTEM:CONSOLE

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ========================================
    echo Build failed!
    echo ========================================
    echo.
    echo Common issues:
    echo 1. Missing required files (CameraCtrl.dll, CameraCtrl.lib, CameraCtrl.h)
    echo 2. Wrong architecture (try x64 Native Tools Command Prompt)
    echo 3. Missing Windows SDK
    echo.
    pause
    exit /b 1
)

REM 
del main.obj 2>nul

REM 
if exist CameraCtrl.dll (
    copy /Y CameraCtrl.dll . >nul 2>&1
)

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Executable created: CameraControlTest.exe
echo Make sure CameraCtrl.dll is in the same folder when running.
echo.
echo You can now run: CameraControlTest.exe
echo.
pause

