Target=AndroidApp

pacakge = com.UrbanEngine.main
pacakgePath = com/UrbanEngine/main
AdnroidJarPath = ./lib/android.jar

SRC = ${wildcard ./jni/*.cpp}
OBJ = ${patsubst %.cpp, ${objDir}%.o, ${SRC}}

Main:
	aapt package -f -m -S ./res -J ./build/gen/ -M ./AndroidManifest.xml -I ${AdnroidJarPath}
	javac -h ./jni -bootclasspath "C:\Program Files\Java\jdk-1.8\jre\lib\rt.jar" -cp ${AdnroidJarPath} -d ./build/obj ./build/gen/${pacakgePath}/R.java ./src/${pacakgePath}/*.java
	dx --dex --output=./build/apk/classes.dex ./build/obj

	clang++ --target=aarch64-none-linux-android21 -stdlib=libstdc++ -O2 -shared ${SRC} -o ./build/apk/lib/arm64-v8a/libFilter.so
	
	aapt package -f -M ./AndroidManifest.xml -S res/ -I ${AdnroidJarPath} -F build/${Target}.unsigned.apk build/apk/
	zipalign -f -p 4 build/${Target}.unsigned.apk build/${Target}.aligned.apk
	apksigner sign --ks keystore.jks --ks-key-alias androidkey --out build/${Target}.apk build/${Target}.aligned.apk
	adb install -r build/${Target}.apk
	adb shell am start --activity-clear-top -n ${pacakge}/.MainActivity

Key:
	keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -keysize 2048