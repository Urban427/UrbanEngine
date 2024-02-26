#include "AndroidFileManager.h"
#include <malloc.h>
#include <memory.h>

FileManager* FileManager::androidFileManager = nullptr;

FileManager::FileManager()
{
	
}

void FileManager::init(JNIEnv* env, jobject* java_obj)
{
	if(androidFileManager == nullptr)
	{
		androidFileManager = (FileManager*)malloc(sizeof(FileManager));
	}
	
	androidFileManager->cls = env->FindClass("com/UrbanEngine/main/NativeLib");
	androidFileManager->printTextID = env->GetStaticMethodID(androidFileManager->cls, "printText", "([B)V");
	androidFileManager->readFileID =  env->GetStaticMethodID(androidFileManager->cls, "readFile",  "([B)[B");
	androidFileManager->env = env;
	androidFileManager->java_obj = java_obj;
}


char* FileManager::readFile(const char* fileName)
{	
	//count size of filename
	int filename_size = 0;
	while(1) {
		if(fileName[filename_size] == 0) {
			break;
		}
		filename_size++;
	}
	
	//use java to read file
	jbyteArray textArray = androidFileManager->env->NewByteArray(filename_size);
	androidFileManager->env->SetByteArrayRegion(textArray, 0, filename_size, (jbyte*)fileName);
	jbyteArray ReadFileArray = (jbyteArray)androidFileManager->env->CallStaticObjectMethod(androidFileManager->cls, androidFileManager->readFileID, textArray);
	
	static char f = 0;
	if(f < 3){
		f++;
		androidFileManager->env->CallStaticObjectMethod(androidFileManager->cls, androidFileManager->printTextID, textArray);
	}
	
	
	
	char* res = (char*)androidFileManager->env->GetByteArrayElements(ReadFileArray, NULL);
	int size =  int((res[0]) << 24 |
					(res[1]) << 16 |
					(res[2]) << 8  |
					(res[3])	   );
	res += 4;
	res[size - 1] = 0;
	
	
	return res;
}