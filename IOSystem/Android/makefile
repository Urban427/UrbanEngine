Target=AndroidApp

pacakge = com.UrbanEngine.main
pacakgePath = com/UrbanEngine/main
AdnroidJarPath = ./lib/android.jar

SRC = ${wildcard ./jni/*.cpp}
OBJ = ${patsubst %.cpp, ${objDir}%.o, ${SRC}}

Main:
	if not exist "build\apk" mkdir build\apk
	if not exist "build\gen\com\UrbanEngine\main" mkdir build\gen\com\UrbanEngine\main
	if not exist "build\apk\lib\arm64-v8a" mkdir build\apk\lib\arm64-v8a
	
	
	aapt package -f -m -S ./res -J ./build/gen/ -M ./AndroidManifest.xml -I ${AdnroidJarPath}
	C:\Program Files\Java\jdk-1.8\bin\javac -h ./jni -bootclasspath "C:\Program Files\Java\jdk-1.8\jre\lib\rt.jar" -cp ${AdnroidJarPath} -d ./build/obj ./build/gen/${pacakgePath}/R.java ./src/${pacakgePath}/*.java
	dx --dex --output=./build/apk/classes.dex ./build/obj

	clang++ --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O2 -shared ${SRC} -o ./build/apk/lib/arm64-v8a/libFilter.so -L ./ -lGLESv2
	
	aapt package -f -M ./AndroidManifest.xml -S res/ -I ${AdnroidJarPath} -F build/${Target}.unsigned.apk build/apk/
	zipalign -f -p 4 build/${Target}.unsigned.apk build/${Target}.aligned.apk
	jarsigner -sigalg SHA1withRSA -digestalg SHA1 -keystore keystore.jks -storepass android -keypass android -signedjar build/${Target}.apk build/${Target}.aligned.apk androidkey
	adb install -r build/${Target}.apk
	adb shell am start --activity-clear-top -n ${pacakge}/.MainActivity

Key:
	keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -keysize 2048