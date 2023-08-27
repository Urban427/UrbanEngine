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


${Target}: ${OBJ}
	${CC} -o ${build}${Target} $^ ${Libs} -lgdi32 
	${build}${Target}
	
${bin}%.o: %.cpp
	${CC} ${IFLAGS} -o $@ -c $< 