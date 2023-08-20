CC = g++
Target = FNAF_Extra_Delivery

build = ./build/
bin = ./bin/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}

Libs = -L ../Game/ -l game

${Target}: ${OBJ}
	${CC} -o ${build}${Target} $^
	${build}${Target}
	
${bin}%.o: %.cpp
	${CC} -o $@ -c $< 