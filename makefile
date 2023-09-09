Target = FNAF_Extra_Delivery

helperDir = ./CustomHelpApps/
MAINDir = ./MAIN/
MathDir = ./Math/
IOSystemDir = ./IOSystem/
AndroidDir = ./IOSystem/Android/
GameLibrary = ./Game/
GraphicLibrary = ./GraphicsEngine/

${Target}:
	${MAKE} -C ${MathDir}
	${MAKE} -C ${IOSystemDir}
	${MAKE} -C ${GameLibrary}
	${MAKE} -C ${GraphicLibrary}
	${MAKE} -C ${MAINDir}
	
Android:
	${MAKE} -C ${helperDir}
	${MAKE} android -C ${MathDir}
	${MAKE} android -C ${GraphicLibrary}
	${MAKE} -C ${AndroidDir}