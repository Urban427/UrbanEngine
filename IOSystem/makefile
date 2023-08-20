Target = IOSystem

CC = g++
bin = ./bin/
WindowsApi = ./Windows/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

OpenGlLib = ../OpenGL37/
libpath = ../libs/


main: binFile builder


builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}


binFile: 
	if not exist "bin" mkdir bin


${bin}%.o: %.cpp
	${CC} -I ${WindowsApi} -o $@ -c $< 