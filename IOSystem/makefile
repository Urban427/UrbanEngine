Target = IOSystem

CC = g++
AndroidCC = clang++
bin = ./bin/
WindowsApi = Windows/
AndroidApi = Android/Filter/
MathApi = ../Math/
libpath = ../libs/
androidlibpath = ../IOSystem/Android/libs/arm64-v8a/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR} ${wildcard ${WindowsApi}*.cpp}}
AndroidOBJ = ${patsubst %.cpp,${bin}%.oa, ${SCR} ${wildcard ${AndroidApi}*.cpp}}
OBJ_DEL = ${subst /,\, ${OBJ}}
OBJ_DEL += ${subst /,\, ${AndroidOBJ}}

IFlags = -I ${WindowsApi}
IFlags += -I ${AndroidApi}
IFlags += -I ${MathApi}

main: binFile clear builder
android: binFile clear androidBuilder

androidBuilder: ${AndroidOBJ}
	ar rcs ${androidlibpath}lib${Target}.a ${AndroidOBJ}

builder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}


binFile: 
	if not exist "bin" mkdir bin
	if not exist "bin\Windows" mkdir bin\Windows
	if not exist "bin\Android\Filter" mkdir bin\Android\Filter


${bin}%.o: %.cpp
	${CC} -D windows ${IFlags} -o $@ -c $<
	
${bin}%.oa: %.cpp
	${AndroidCC} ${IFlags} -D android -o $@ -c $< --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O3

clear:
	del ${OBJ_DEL} 