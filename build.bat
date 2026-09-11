@echo off
SET IMAGE_NAME=windows_builder
SET PROJECT_PATH=%~dp0
SET PLATFORM=windows
set PROJECT_NAME=%~1
set COMPILE_MODE=%~2
set CONTAINER=podman

if /I "%~1"=="cleanFull" (
    echo.
    echo ========================================
    echo       PODMAN FULL CLEANUP
    echo ========================================
    echo.

    echo [1/6] Stopping all containers...
    %CONTAINER% stop -a >nul 2>&1

    echo [2/6] Removing all containers...
    %CONTAINER% rm -a -f >nul 2>&1

    echo [3/6] Removing all volumes...
    %CONTAINER% volume rm -a -f >nul 2>&1

    echo [4/6] Removing all images...
    %CONTAINER% image rm -a -f >nul 2>&1

    echo [5/6] Removing build cache...
    %CONTAINER% builder prune -a -f >nul 2>&1

    echo [6/6] Removing unused Podman data...
    %CONTAINER% system prune -a --volumes -f >nul 2>&1

    echo.
    echo ========================================
    echo       PODMAN CLEANUP COMPLETED
    echo ========================================
    echo.

    %CONTAINER% system df

    pause
    exit /b
)

if /I "%~1"=="clean" (
    echo.
    echo ========================================
    echo       CLEAN WORKSPACE
    echo ========================================
    echo.

    echo Removing workspace volume...

    %CONTAINER% volume rm -f project >nul 2>&1

    echo Workspace cleaned.
    echo.

    pause
    exit /b
)



if /I "%COMPILE_MODE%"=="release" (
    set "COMPILE_MODE=release"
) else (
    set "COMPILE_MODE=debug"
)


set ENGINE_PATH=%~dp0
set "ENGINE_PATH=%ENGINE_PATH:~0,-1%"
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

%CONTAINER% --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo %CONTAINER% not found.
    pause
    exit /b
)


%CONTAINER% machine start >nul 2>&1
%CONTAINER% info >nul 2>&1
IF ERRORLEVEL 1 (
    echo %CONTAINER% machine is not running.
    echo Try:
    %CONTAINER% machine init
    %CONTAINER% machine start
    pause
    exit /b
)


%CONTAINER% image inspect %IMAGE_NAME% >nul 2>&1
IF ERRORLEVEL 1 (
    echo Image not found. Building new image.
    %CONTAINER% build -t %IMAGE_NAME% "%ENGINE_PATH%"
) ELSE (
    echo Image found
)


%CONTAINER% volume inspect %PROJECT_NAME% >nul 2>&1
IF ERRORLEVEL 1 (
    echo Volume not found.
    %CONTAINER% volume create %PROJECT_NAME%
) ELSE (
    echo Volume found
)

echo Start building
if /I "%COMPILE_MODE%"=="release" (
    echo === PRE-RELEASE: baking assets ===
    "%CONTAINER%" run --rm ^
        -v "project:/workspace" ^
        -v "%ENGINE_PATH%:/engine" ^
        -v "%PROJECT_PATH%:/project" ^
        -v "%BUILD_PATH%:/build" ^
        %IMAGE_NAME% ^
        bash /engine/tools/build.sh %PLATFORM% /project /engine /build %PROJECT_NAME% prerelease

    if errorlevel 1 (
        echo Pre-release build failed.
        exit /b 1
    )

    "%BUILD_PATH%\%PROJECT_NAME%\%PROJECT_NAME%.exe"
    echo === RELEASE: final build ===

    "%CONTAINER%" run --rm ^
        -v "project:/workspace" ^
        -v "%ENGINE_PATH%:/engine" ^
        -v "%PROJECT_PATH%:/project" ^
        -v "%BUILD_PATH%:/build" ^
        %IMAGE_NAME% ^
        bash /engine/tools/build.sh %PLATFORM% /project /engine /build %PROJECT_NAME% release

    if errorlevel 1 (
        echo Release build failed.
        exit /b 1
    )
) else (
    echo === %COMPILE_MODE% build ===

    "%CONTAINER%" run --rm ^
        -v "project:/workspace" ^
        -v "%ENGINE_PATH%:/engine" ^
        -v "%PROJECT_PATH%:/project" ^
        -v "%BUILD_PATH%:/build" ^
        %IMAGE_NAME% ^
        bash /engine/tools/build.sh %PLATFORM% /project /engine /build %PROJECT_NAME% %COMPILE_MODE%

    if errorlevel 1 (
        echo Build failed.
        exit /b 1
    )

    @REM start "" "./build/GlassWars/GlassWars.exe"
    "%BUILD_PATH%\%PROJECT_NAME%\%PROJECT_NAME%.exe"
)

