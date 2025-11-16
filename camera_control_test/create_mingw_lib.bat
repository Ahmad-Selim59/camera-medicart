@echo off
REM Script to create MinGW import library from Visual Studio DLL
echo ========================================
echo Create MinGW Import Library
echo ========================================
echo.

if not exist CameraCtrl.dll (
    echo ERROR: CameraCtrl.dll not found!
    pause
    exit /b 1
)

REM Check for pexports
where pexports >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: pexports tool not found!
    echo.
    echo Please download pexports:
    echo http://sourceforge.net/projects/mingw/files/MinGW/Extension/pexports/
    echo.
    echo Extract pexports.exe and add it to your PATH, or place it in this folder.
    echo.
    pause
    exit /b 1
)

echo Step 1: Generating .def file from DLL...
pexports CameraCtrl.dll > CameraCtrl.def
if %ERRORLEVEL% NEQ 0 (
    echo Failed to generate .def file!
    pause
    exit /b 1
)

if not exist CameraCtrl.def (
    echo ERROR: .def file was not created!
    pause
    exit /b 1
)

echo Step 2: Creating MinGW import library (.a file)...
dlltool -d CameraCtrl.def -l CameraCtrl.a -D CameraCtrl.dll
if %ERRORLEVEL% NEQ 0 (
    echo Failed to create import library!
    pause
    exit /b 1
)

if not exist CameraCtrl.a (
    echo ERROR: Import library was not created!
    pause
    exit /b 1
)

echo.
echo ========================================
echo Success!
echo ========================================
echo.
echo Created: CameraCtrl.a (MinGW import library)
echo.
echo You can now use build_mingw_with_a.bat to compile
echo.
pause

