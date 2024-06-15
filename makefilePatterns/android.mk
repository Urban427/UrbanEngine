CC = clang++.exe --target=aarch64-none-linux-android21
bin = ./bin/
folders += ${bin}
libpath = ../libs/

SCR += ${wildcard *.cpp}
OBJ += ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL += ${subst /,\, ${OBJ}}

IFlags += -I ../Math/
IFlags += -I ../Math/

DFlags += -D gles2
DFlags += -D android
DFlags += 