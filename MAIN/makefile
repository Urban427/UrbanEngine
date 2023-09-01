CC = g++
Target = UrbanEngine

build = ./build/
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

IOSystemDir = ../IOSystem/
WindowsDir = ../IOSystem/Windows/
OpenGlDib = ../OpenGL37/
GameDib = ../Game/
GraphicEngineDir = ../GraphicsEngine/


Libs = -L../libs
Libs += -l Game
Libs += -l IOSystem
Libs += -l API

IFLAGS = -I ${GameDib}
IFLAGS += -I ${IOSystemDir}
IFLAGS += -I ${WindowsDir}
IFLAGS += -I ${GraphicEngineDir}


${Target}: binFile builder
	${build}${Target}


builder: ${OBJ}
	${CC} -O3 -o ${build}${Target} $^ ManifestWindows.res ${Libs} -lgdi32 

binFile: 
	windres ManifestWindows.rc -O coff -o ManifestWindows.res
	if not exist "bin" mkdir bin
	if not exist "build" mkdir build

${bin}%.o: %.cpp
	${CC} ${IFLAGS} -o $@ -c $< 