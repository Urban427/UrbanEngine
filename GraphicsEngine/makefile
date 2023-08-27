Target = GraphicsEngine

CC = g++
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

libpath = ../libs/
openGlDir = ./OpenGl37/
CFlags = -I ${openGlDir}

main: binFile builder 


builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}


binFile: 
	if not exist "bin" mkdir bin


${bin}%.o: %.cpp
	${CC} ${CFlags} -o $@ -c $< 