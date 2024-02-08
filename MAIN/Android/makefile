Target=AndroidApp

pacakge = com.UrbanEngine.main
pacakgePath = com/UrbanEngine/main
AdnroidJarPath = ./lib/android.jar

SRC = ${wildcard ./jni/*.cpp}
OBJ = ${patsubst %.cpp, ${objDir}%.o, ${SRC}}

IFlags += -I ../../GraphicsEngine/
IFlags += -I ../../MAIN/
IFlags += -I ../../IOSystem/Android/
IFlags += -I ../../IOSystem/
IFlags += -I ../../Math/
IFlags += -I ../../App/

CFlags += -L ./
CFlags += -lGLESv2
CFlags += -L ../../libs
CFlags += -lIOSystem
CFlags += -lGraphicsEngine
CFlags += -lMath
CFlags += -lApp

appBuilder:
	if not exist "build\apk" mkdir build\apk
	if not exist "build\gen\com\UrbanEngine\main" mkdir build\gen\com\UrbanEngine\main
	if not exist "build\apk\lib\arm64-v8a" mkdir build\apk\lib\arm64-v8a
	
	
	aapt package -f -m -S ./res -J ./build/gen/ -M ./AndroidManifest.xml -I ${AdnroidJarPath}
	javac -h ./jni -bootclasspath "C:\Program Files\Java\jdk-1.8\jre\lib\rt.jar" -cp ${AdnroidJarPath} -d ./build/obj ./build/gen/${pacakgePath}/R.java ./src/${pacakgePath}/*.java
	d8 --output=./build/apk/ .\build\obj\com\UrbanEngine\main\\*.class

	clang++ --target=aarch64-none-linux-android21  -D android -stdlib=libstdc++ -O3 -shared -o ./build/apk/lib/arm64-v8a/libFilter.so ${SRC} ${IFlags}  ${CFlags}
	
	aapt package -f -M ./AndroidManifest.xml -S .\res -I ./lib/android.jar -F build/AndroidApp.unsigned.apk .\build\apk
	zipalign -f -p 4 build/${Target}.unsigned.apk build/${Target}.aligned.apk
	jarsigner -sigalg SHA1withRSA -digestalg SHA1 -keystore keystore.jks -storepass android -keypass android -signedjar build/${Target}.apk build/${Target}.aligned.apk androidkey
	adb install -r build/${Target}.apk
	adb shell am start --activity-clear-top -n ${pacakge}/.MainActivity

Key:
	keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -7 2048