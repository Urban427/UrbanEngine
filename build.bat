@echo off
SET IMAGE_NAME=windows_builder
SET PROJECT_PATH=%~dp0
SET PLATFORM=windows
set PROJECT_NAME=%~1


if "%~1"=="clean" (
    echo Cleaning build environment...

    podman volume rm %PROJECT_NAME% >nul 2>&1
    podman volume create %PROJECT_NAME% >nul 2>&1

    podman builder prune -a -f >nul 2>&1
    exit /b
)

set ENGINE_PATH=%~dp0 
set PROJECT_PATH=%~dp0..\Projects\%PROJECT_NAME% 
set BUILD_PATH=%~dp0..\build\%PROJECT_NAME%
set BUILD_PATH=%~dp0..\build

if not exist "%PROJECT_PATH%" ( 
    echo Project not found: 
    echo %PROJECT_PATH% 
    exit /b 1 
) 
if not exist "%BUILD_PATH%" ( mkdir "%BUILD_PATH%" )

echo Build for %PLATFORM%

podman --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo Docker not found.
    pause
    exit /b
)


podman machine start >nul 2>&1
podman info >nul 2>&1
IF ERRORLEVEL 1 (
    echo Podman machine is not running.
    echo Try:
    echo podman machine init
    echo podman machine start
    pause
    exit /b
)


podman image inspect %IMAGE_NAME% >nul 2>&1
IF ERRORLEVEL 1 (
    echo Image not found. Building new image.
    podman build -t %IMAGE_NAME% "%ENGINE_PATH%"
) ELSE (
    echo Image found
)


podman volume inspect %PROJECT_NAME% >nul 2>&1
IF ERRORLEVEL 1 (
    echo Volume not found.
    podman volume create %PROJECT_NAME%
) ELSE (
    echo Volume found
)

echo Start building
podman run --rm ^
    -v "project:/workspace" ^
    -v "%ENGINE_PATH%:/engine" ^
    -v "%PROJECT_PATH%:/project" ^
    -v "%BUILD_PATH%:/build" ^
    %IMAGE_NAME% ^
    bash /engine/tools/build.sh %PLATFORM% /project /engine /build  %PROJECT_NAME% 

if errorlevel 1 ( 
    echo Build failed. 
    exit /b 1 
)

@REM start "" "./build/GlassWars/GlassWars.exe"
"%BUILD_PATH%\%PROJECT_NAME%\%PROJECT_NAME%.exe"
