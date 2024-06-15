helperDir = ./CustomHelpApps/
MAINDir = ./MAIN/
AppDir = ./App/
MathDir = ./Math/
IOSystemDir = ./IOSystem/
AndroidDir = ./IOSystem/Android/
LogicLibrary = ./Logic/
GraphicLibrary = ./GraphicsEngine/
PhysicLibrary = ./Physic/

androidAPI = Android/
windowsAPI = Windows/


target = windows


windows: binFile
	@echo ${MAKE} platform=${target} -C ${helperDir}
	 ${MAKE} platform=${target} -C ${MathDir}
	${MAKE} platform=${target} -C ${IOSystemDir}
	@echo ${MAKE} platform=${target} -C ${LogicLibrary}
	 ${MAKE} platform=${target} -C ${GraphicLibrary}
	@echo ${MAKE} platform=${target} -C ${PhysicLibrary}
	${MAKE} platform=${target} -C ${AppDir}
	${MAKE} platform=${target} -C ${MAINDir}${${target}API} buildApp



binFile: 
	if not exist "build" mkdir build