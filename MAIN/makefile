CC = g++
AndroidCC = clang++
Target = UrbanEngine

build = ./build/
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
AndroidOBJ = ${patsubst %.cpp,${bin}%.oa, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}
OBJ_DEL += ${subst /,\, ${AndroidOBJ}}

MathDir = ../Math/
IOSystemDir = ../IOSystem/
WindowsDir = ../IOSystem/Windows/
AndroidDir = ../IOSystem/Android/Filter/
OpenGlDib = ../OpenGL37/
GameDib = ../Game/
GraphicsEngineDir = ../GraphicsEngine/


Libs += -L../libs
Libs += -l Game
Libs += -l IOSystem
Libs += -l GraphicsEngine
Libs += -l glad
Libs += -l Math

IFLAGS = -I ${GameDib}
IFLAGS = -I ${MathDir}
IFLAGS += -I ${IOSystemDir}
IFLAGS += -I ${AndroidDir}
IFLAGS += -I ${WindowsDir}
IFLAGS += -I ${GraphicsEngineDir}


windows: binFile clear builder
	${build}${Target}


android: binFile clear androidBuilder

builder: ${OBJ}
	${CC} -O3 -o ${build}${Target} $^ ManifestWindows.res ${Libs} -lgdi32  -lopengl32

androidBuilder: ${AndroidOBJ}
	ar rcs ../IOSystem/Android/libs/arm64-v8a/lib${Target}.a ${AndroidOBJ}
	

binFile: 
	windres ManifestWindows.rc -O coff -o ManifestWindows.res
	if not exist "bin" mkdir bin
	if not exist "build" mkdir build

${bin}%.o: %.cpp
	${CC} -D windows ${IFLAGS} -o $@ -c $< -Wl,--subsystem,windows

${bin}%.oa: %.cpp
	${AndroidCC} -D android ${IFLAGS} -o $@ -c $< --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O2

clear:
	del ${OBJ_DEL} 