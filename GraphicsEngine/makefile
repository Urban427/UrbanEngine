Target = GraphicsEngine

CC = g++
bin = ./bin/
libpath = ../libs/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}

main: binFile clear builder 

IFlags = -I ../Math/


builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}


binFile: 
	if not exist "bin" mkdir bin


${bin}%.o: %.cpp
	${CC} ${IFlags} -o $@ -c $< 
	
clear:
	del ${OBJ_DEL} 