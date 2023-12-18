Target = FNAF_Extra_Delivery

helperDir = ./CustomHelpApps/
MAINDir = ./MAIN/
MathDir = ./Math/
IOSystemDir = ./IOSystem/
AndroidDir = ./IOSystem/Android/
GameLibrary = ./Game/
GraphicLibrary = ./GraphicsEngine/
PhysicLibrary = ./Physic/

${Target}:
	${MAKE} -C ${MathDir}
	${MAKE} -C ${IOSystemDir}
	${MAKE} -C ${GameLibrary}
	${MAKE} -C ${GraphicLibrary}
	${MAKE} -C ${PhysicLibrary}
	${MAKE} -C ${MAINDir}
	
Android:
	${MAKE} -C ${helperDir}
	${MAKE} android -C ${MathDir}
	${MAKE} android -C ${IOSystemDir}
	${MAKE} android -C ${GraphicLibrary}
	${MAKE} -C ${PhysicLibrary}
	${MAKE} android -C ${MAINDir}
	${MAKE} -C ${AndroidDir}