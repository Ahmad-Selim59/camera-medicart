@echo off
echo Building Camera Control Test Application...
echo.

REM Check if Visual Studio is available
where cl >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Visual Studio compiler not found in PATH.
    echo Please run this from a Visual Studio Developer Command Prompt
    echo or set up the environment variables manually.
    pause
    exit /b 1
)

REM Compile
cl /EHsc /std:c++11 main.cpp CameraCtrl.lib strmiids.lib Ws2_32.lib ole32.lib oleaut32.lib Advapi32.lib /Fe:CameraControlTest.exe /link /SUBSYSTEM:CONSOLE

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Executable: CameraControlTest.exe
    echo.
    echo Make sure CameraCtrl.dll is in the same directory as the executable.
) else (
    echo.
    echo Build failed!
)

pause

