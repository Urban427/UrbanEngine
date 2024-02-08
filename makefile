helperDir = ./CustomHelpApps/
MAINDir = ./MAIN/
AppDir = ./App/
MathDir = ./Math/
IOSystemDir = ./IOSystem/
AndroidDir = ./IOSystem/Android/
GameLibrary = ./Game/
GraphicLibrary = ./GraphicsEngine/
PhysicLibrary = ./Physic/

androidAPI = Android/
windowsAPI = Windows/


target = windows


windows: 
	@echo ${MAKE} platform=${target} -C ${helperDir}
	${MAKE} platform=${target} -C ${MathDir}
	${MAKE} platform=${target} -C ${IOSystemDir}
	${MAKE} platform=${target} -C ${GameLibrary}
	${MAKE} platform=${target} -C ${GraphicLibrary}
	${MAKE} platform=${target} -C ${PhysicLibrary}
	${MAKE} platform=${target} -C ${AppDir}
	${MAKE} platform=${target} -C ${MAINDir}${${target}API} appBuilder