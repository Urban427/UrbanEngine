CC = g++
Target = UrbanEngine

build = ./build/
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}

MathDir = ../Math/
IOSystemDir = ../IOSystem/
WindowsDir = ../IOSystem/Windows/
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
IFLAGS += -I ${WindowsDir}
IFLAGS += -I ${GraphicsEngineDir}


${Target}: binFile clear builder
	${build}${Target}


builder: ${OBJ}
	${CC} -O3 -o ${build}${Target} $^ ManifestWindows.res ${Libs} -lgdi32  -lopengl32

binFile: 
	windres ManifestWindows.rc -O coff -o ManifestWindows.res
	if not exist "bin" mkdir bin
	if not exist "build" mkdir build

${bin}%.o: %.cpp
	${CC} ${IFLAGS} -o $@ -c $< 

clear:
	del ${OBJ_DEL} 