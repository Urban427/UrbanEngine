#pragma once
#include <jni.h>

#define CUR 0
#define END 1
#define SET 2

typedef struct File
{
	unsigned char* buffer;
	unsigned char* pointer;
	int size;
}File;

File* open(const char* file, const char* mode);
int read(void* ptr, size_t size, size_t nmemb, File* stream);

void seek(File* stream, long int offset, int whence);
void close(File* stream);


void print(const char* text);




class AndroidFileManager
{
public:
	AndroidFileManager();
	AndroidFileManager(JNIEnv* env, jobject* java_obj);
	
	static void init(JNIEnv* env, jobject* java_obj);

	AndroidFileManager* get();
public:
	JNIEnv* env;
	jobject* java_obj;
	jclass cls;
	jmethodID printTextID;
	jmethodID readFileID;
};