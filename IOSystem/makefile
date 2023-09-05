Target = IOSystem

CC = g++
bin = ./bin/
WindowsApi = Windows/
MathApi = ../Math/
libpath = ../libs/

SCR = ${wildcard *.cpp}
SCR += ${wildcard ${WindowsApi}*.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}

IFlags += -I ${WindowsApi}
IFlags += -I ${MathApi}

main: binFile clear builder


builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}


binFile: 
	if not exist "bin" mkdir bin
	if not exist "bin\Windows" mkdir bin\Windows


${bin}%.o: %.cpp
	${CC} ${IFlags} -o $@ -c $<

clear:
	del ${OBJ_DEL} 