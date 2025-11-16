@echo off
REM Simple one-line compilation script
REM Just double-click this file after installing MinGW/TDM-GCC

echo Compiling Camera Control Test...
g++ -std=c++11 -Wall -O2 main.cpp -o CameraControlTest.exe CameraCtrl.lib -lstrmiids -lws2_32 -lole32 -loleaut32 -ladvapi32

if %ERRORLEVEL% EQU 0 (
    echo.
    echo SUCCESS! CameraControlTest.exe created.
    echo Make sure CameraCtrl.dll is in the same folder.
    echo.
    echo You can now run: CameraControlTest.exe
) else (
    echo.
    echo ERROR: Compilation failed!
    echo Make sure you have MinGW or TDM-GCC installed.
    echo See WINDOWS7_SETUP.txt for instructions.
)

echo.
pause

