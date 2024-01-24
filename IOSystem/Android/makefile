Target=AndroidApp

pacakge = com.UrbanEngine.main
pacakgePath = com/UrbanEngine/main
AdnroidJarPath = ./lib/android.jar

SRC = ${wildcard ./jni/*.cpp}
OBJ = ${patsubst %.cpp, ${objDir}%.o, ${SRC}}

IFlags += -I ../../GraphicsEngine/
IFlags += -I ../../MAIN/
IFlags += -I ./Filter/
IFlags += -I ../../IOSystem/
IFlags += -I ../../Math/

CFlags += -L ./
CFlags += -lGLESv2
CFlags += -L ./libs/arm64-v8a/
CFlags += -lUrbanEngine
CFlags += -lIOSystem
CFlags += -lGraphicsEngine
CFlags += -lMath

Main:
	if not exist "build\apk" mkdir build\apk
	if not exist "build\gen\com\UrbanEngine\main" mkdir build\gen\com\UrbanEngine\main
	if not exist "build\apk\lib\arm64-v8a" mkdir build\apk\lib\arm64-v8a
	
	
	aapt package -f -m -S ./res -J ./build/gen/ -M ./AndroidManifest.xml -I ${AdnroidJarPath}
	C:\Program Files\Java\jdk-1.8\bin\javac -h ./jni -bootclasspath "C:\Program Files\Java\jdk-1.8\jre\lib\rt.jar" -cp ${AdnroidJarPath} -d ./build/obj ./build/gen/${pacakgePath}/R.java ./src/${pacakgePath}/*.java
	dx --dex --output=./build/apk/classes.dex ./build/obj

	clang++ -D android ${IFlags} --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O3 -shared ${SRC} -o ./build/apk/lib/arm64-v8a/libFilter.so ${CFlags}
	
	aapt package -f -M ./AndroidManifest.xml -S res/ -I ${AdnroidJarPath} -F build/${Target}.unsigned.apk build/apk/
	zipalign -f -p 4 build/${Target}.unsigned.apk build/${Target}.aligned.apk
	jarsigner -sigalg SHA1withRSA -digestalg SHA1 -keystore keystore.jks -storepass android -keypass android -signedjar build/${Target}.apk build/${Target}.aligned.apk androidkey
	adb install -r build/${Target}.apk
	adb shell am start --activity-clear-top -n ${pacakge}/.MainActivity

Key:
	keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -7 2048