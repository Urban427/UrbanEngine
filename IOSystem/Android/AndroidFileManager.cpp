#include "AndroidFileManager.h"
#include <malloc.h>
#include <memory.h>

FileManager* FileManager::androidFileManager = nullptr;

FileManager::FileManager()
{
	
}

FileManager::FileManager(JNIEnv* env, jobject* java_obj)
{
	cls = env->GetObjectClass(*java_obj);
	printTextID = env->GetMethodID(cls, "printText", "([B)V");
	readFileID = env->GetMethodID(cls, "readFile", "([B)[B");
	this->env = env;
	this->java_obj = java_obj;
}

void FileManager::init(JNIEnv* env, jobject* java_obj)
{
	if(androidFileManager == nullptr)
	{
		androidFileManager = new FileManager();
	}
	
	androidFileManager->cls = env->GetObjectClass(*java_obj);
	androidFileManager->printTextID = env->GetMethodID(androidFileManager->cls, "printText", "([B)V");
	androidFileManager->readFileID =  env->GetMethodID(androidFileManager->cls, "readFile", "([B)[B");
	androidFileManager->env = env;
	androidFileManager->java_obj = java_obj;
}

FileManager* FileManager::get()
{
	return androidFileManager;
}








char* FileManager::readFile(const char* name)
{
	//count file name size
	int size_of_filename = 0;
	while(1) {
		if(name[size_of_filename] == 0) {
			break;
		}
		size_of_filename++;
	}
	
	
	//use native java
	jbyteArray textArray = androidFileManager->env->NewByteArray(size_of_filename);
	androidFileManager->env->SetByteArrayRegion(textArray, 0, size_of_filename, (jbyte*)name);
	jbyteArray ReadFileArray = (jbyteArray)androidFileManager->env->CallObjectMethod(*androidFileManager->java_obj, androidFileManager->readFileID, textArray);
	
	int size = 3;
	const char* text = "lol";
	jbyteArray textArray1 = androidFileManager->env->NewByteArray(size);
	androidFileManager->env->SetByteArrayRegion(textArray1, 0, size, (jbyte*)text);
	
	return (char*)androidFileManager->env->GetByteArrayElements(ReadFileArray, NULL);
}