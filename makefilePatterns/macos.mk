CC = g++
bin = ./bin/
libpath = ../libs/

SCR = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp,${bin}%.o, ${SCR}}
OBJ_DEL = ${subst /,\, ${OBJ}}

IFlags = -I ../Math/
DFlags = -D gles2 android

include ./pattern.mk