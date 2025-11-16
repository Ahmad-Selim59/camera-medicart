@echo off
REM Build using MinGW import library (.a file)
echo ========================================
echo Camera Control Test - MinGW Build (Using .a file)
echo ========================================
echo.

if not exist CameraCtrl.a (
    echo ERROR: CameraCtrl.a not found!
    echo.
    echo Please run create_mingw_lib.bat first to create the import library.
    echo.
    pause
    exit /b 1
)

REM Check if g++ is available
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: g++ compiler not found!
    pause
    exit /b 1
)

echo Compiling and linking with MinGW import library...
echo.

g++ -std=c++11 -Wall -O2 -DCAMCTRL_API= -DCAMCTRL_EXPORTS= main.cpp -o CameraControlTest.exe CameraCtrl.a -lstrmiids -lws2_32 -lole32 -loleaut32 -ladvapi32 -Wl,--enable-auto-import -static-libgcc -static-libstdc++

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

REM Copy DLL
if exist CameraCtrl.dll (
    copy /Y CameraCtrl.dll . >nul 2>&1
)

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Executable: CameraControlTest.exe
echo.
pause

