CC = g++
Target = UrbanEngine

build = ./build/
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

OpenGlLib = ../OpenGL37/
GameLib = ../Game/
Libs = -L../libs
Libs += -l Game
Libs += -l IOSystem
Libs += -l API


${Target}: ${OBJ}
	${CC} -o ${build}${Target} $^ ${Libs}
	${build}${Target}
	
${bin}%.o: %.cpp
	${CC} -I ${GameLib} -o $@ -c $< 