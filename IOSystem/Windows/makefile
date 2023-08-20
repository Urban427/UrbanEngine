Target = API
CC = g++
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

OpenGlLib = ../../OpenGL37/
libpath = ../../libs/

${Target}: binFile builder

builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a $^

binFile: 
	if not exist "bin" mkdir bin

${bin}%.o: %.cpp
	${CC} -I ${OpenGlLib} -o $@ -c $< 