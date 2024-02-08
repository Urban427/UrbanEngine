Target = UrbanEngine
build = ../../build/
include ../../makefilePatterns/${platform}.mk

AppDir = ../../App/
MathDir = ../../Math/
IOSystemDir = ../../IOSystem/
WindowsDir = ../../IOSystem/Windows/
AndroidDir = ../../IOSystem/Android/Filter/
OpenGlDib = ../../OpenGL37/
GameDib = ../../Game/
PhysicLib = ../../Physic/
GraphicsEngineDir = ../../GraphicsEngine/


Libs += -L../../libs
Libs += -l App
Libs += -l Game
Libs += -l IOSystem
Libs += -l GraphicsEngine
Libs += -l glad
Libs += -l Math
Libs += -l Physic

IFlags += -I ${AppDir}
IFlags += -I ${PhysicLib}
IFlags += -I ${GameDib}
IFlags += -I ${MathDir}
IFlags += -I ${IOSystemDir}
IFlags += -I ${AndroidDir}
IFlags += -I ${WindowsDir}
IFlags += -I ${GraphicsEngineDir}


LFlags += -lgdi32
LFlags += -lopengl32

resources = ManifestWindows.res

include ../../makefilePatterns/pattern.mk