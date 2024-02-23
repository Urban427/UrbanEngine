#pragma once
#include <jni.h>


class FileManager
{
public:
	FileManager();
	FileManager(JNIEnv* env, jobject* java_obj);
	static FileManager* get();
	static void init(JNIEnv* env, jobject* java_obj);
	
	
	static char* readFile(const char* name);
public:
	static FileManager* androidFileManager;

	JNIEnv* env;
	jobject* java_obj;
	jclass cls;
	jmethodID printTextID;
	jmethodID readFileID;
};