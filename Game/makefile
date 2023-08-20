Target = Game

CC = g++
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

IOSystemDir = ../IOSystem/
WindowsDir = ../IOSystem/Windows/
libpath = ../libs/
CFlags = -I ${IOSystemDir}
CFlags += -I ${WindowsDir}

${Target}: ${OBJ}
	if not exist "bin" mkdir bin
	ar rcs ${libpath}lib${Target}.a $^

${bin}%.o: %.cpp
	${CC} ${CFlags} -o $@ -c $< 