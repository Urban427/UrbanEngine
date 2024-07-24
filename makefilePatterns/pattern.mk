buildLib: binFile clear libBuilder

buildApp: binFile clear appBuilder

appBuilder: ${OBJ}
	${CC} -o ${build}${Target}.exe $^ ${resources} ${Libs} ${CFlags} ${LFlags}

libBuilder: ${OBJ}
	ar rcs ${libpath}lib${Target}.a ${OBJ}

binFile: 
	if not exist ${bin} mkdir ${subst /,\, ${folders}}

${bin}%.o: %.cpp
	${CC} ${IFlags} ${DFlags} -o $@ -c $< ${CFlags}
	
clear:
	del ${OBJ_DEL} 