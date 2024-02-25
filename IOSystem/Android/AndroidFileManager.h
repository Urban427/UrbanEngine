#pragma once
#include <jni.h>

class FileManager
{
public:
	FileManager();
	
	static void init(JNIEnv* env, jobject* java_obj);
	static char* readFile(const char* fileName);
public:
	static FileManager* androidFileManager;

	JNIEnv* env;
	jobject* java_obj;
	jclass cls;
	jmethodID printTextID;
	jmethodID readFileID;
};