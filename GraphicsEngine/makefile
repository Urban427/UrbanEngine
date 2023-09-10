Target = GraphicsEngine

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

main: binFile clear builder 
android: binFile clear androidBuilder

IFlags = -I ../Math/


builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}

androidBuilder: ${AndroidOBJ}
	ar rcs ${androidlibpath}lib${Target}.a ${AndroidOBJ}

binFile: 
	if not exist "bin" mkdir bin


${bin}%.o: %.cpp
	${CC} -D pc -D glad ${IFlags} -o $@ -c $< 
	
${bin}%.oa: %.cpp
	${AndroidCC} -D android -D gles2 ${IFlags} -o $@ -c $< --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O3
	
clear:
	del ${OBJ_DEL} 