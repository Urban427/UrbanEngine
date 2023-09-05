Target = API

CC = g++
bin = ./bin/
MathDir = ../../Math/
libpath = ../../libs/


SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}

IFlags += -I ${MathDir}

${Target}: binFile clear builder

builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a $^

binFile: 
	if not exist "bin" mkdir bin

${bin}%.o: %.cpp
	${CC} ${IFlags} -o $@ -c $<

clear:
	del ${OBJ_DEL} 