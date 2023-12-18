Target = Physic

CC = g++
AndroidCC = clang++
bin = ./bin/
libpath = ../libs/
androidlibpath = ../IOSystem/Android/libs/arm64-v8a/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
AndroidOBJ = ${patsubst %.cpp,${bin}%.oa, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}
OBJ_DEL += ${subst /,\, ${AndroidOBJ}}

IFlags = -I ../Math/

main: binFile clear builder 
android: binFile clear androidBuilder

builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}

androidBuilder: ${AndroidOBJ}
	ar rcs ${androidlibpath}lib${Target}.a ${AndroidOBJ}

binFile: 
	if not exist "bin" mkdir bin


${bin}%.o: %.cpp
	${CC} ${IFlags} -o $@ -c $< 
	
${bin}%.oa: %.cpp
	${AndroidCC} -D android ${IFlags} -o $@ -c $< --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O2
	
clear:
	del ${OBJ_DEL} 