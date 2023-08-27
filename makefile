Target = FNAF_Extra_Delivery

WindowsApiDir = ./IOSystem/Windows/
MAINDir = ./MAIN/
IOSystemDir = ./IOSystem/
AndroidDir = ./IOSystem/Android/
GameLibrary = ./Game/
GraphicLibrary = ./GraphicsEngine/

${Target}:
	${MAKE} -C ${WindowsApiDir}
	${MAKE} -C ${IOSystemDir}
	${MAKE} -C ${GameLibrary}
	${MAKE} -C ${GraphicLibrary}
	${MAKE} -C ${MAINDir}
	
Android:
	${MAKE} -C ${AndroidDir}