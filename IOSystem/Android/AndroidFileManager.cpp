#include "AndroidFileManager.h"
#include <malloc.h>
#include <memory.h>

static AndroidFileManager* androidFileManager = nullptr;

AndroidFileManager::AndroidFileManager()
{
	
}

AndroidFileManager::AndroidFileManager(JNIEnv* env, jobject* java_obj)
{
	cls = env->GetObjectClass(*java_obj);
	printTextID = env->GetMethodID(cls, "printText", "([B)V");
	readFileID = env->GetMethodID(cls, "readFile", "([B)[B");
	this->env = env;
	this->java_obj = java_obj;
}

void AndroidFileManager::init(JNIEnv* env, jobject* java_obj)
{
	if(androidFileManager == nullptr)
	{
		androidFileManager = new AndroidFileManager();
	}
	
	androidFileManager->cls = env->GetObjectClass(*java_obj);
	androidFileManager->printTextID = env->GetMethodID(androidFileManager->cls, "printText", "([B)V");
	androidFileManager->readFileID =  env->GetMethodID(androidFileManager->cls, "readFile", "([B)[B");
	androidFileManager->env = env;
	androidFileManager->java_obj = java_obj;
}

AndroidFileManager* AndroidFileManager::get()
{
	return androidFileManager;
}


void print(const char* text)
{
	int size = 0;
	while(1)
	{
		if(text[size] == 0)
		{
			break;
		}
		size++;
	}
	char* res = (char*)malloc(size);
	for(int i = 0; i < size; i++)
	{
		res[i] = text[i];
	}
	
	jbyteArray textArray = androidFileManager->env->NewByteArray(size);
	androidFileManager->env->SetByteArrayRegion(textArray, 0, size, (jbyte*)res);



    androidFileManager->env->CallObjectMethod(*androidFileManager->java_obj, androidFileManager->printTextID, textArray);
}


File* open(const char* file, const char* mode)
{
	File* result = (File*)malloc(sizeof(File));
	
	int size_of_filename = 0;
	while(1)
	{
		if(file[size_of_filename] == 0)
		{
			break;
		}
		size_of_filename++;
	}
	char* res = (char*)malloc(size_of_filename);
	for(int i = 0; i < size_of_filename; i++)
	{
		res[i] = file[i];
	}
	
	jbyteArray textArray = androidFileManager->env->NewByteArray(size_of_filename);
	androidFileManager->env->SetByteArrayRegion(textArray, 0, size_of_filename, (jbyte*)res);
	
	jbyteArray ReadFileArray = (jbyteArray)androidFileManager->env->CallObjectMethod(*androidFileManager->java_obj, androidFileManager->readFileID, textArray);
	
	
	result->size = androidFileManager->env->GetArrayLength(ReadFileArray);
	result->buffer = (unsigned char*)androidFileManager->env->GetByteArrayElements(ReadFileArray, NULL);
	result->pointer = result->buffer;

	return result;
}


int read(void* ptr, size_t size, size_t nmemb, File* stream)
{
	int to_read = size * nmemb;
	for(int i = 0; i < to_read; i++)
	{
		((char*)ptr)[i] = *stream->pointer;	
		stream->pointer++;
	}
	return to_read;
}


void seek(File* stream, long int offset, int whence)
{
	if(whence == CUR)
	{
		
	}
	else if(whence == END)
	{
		stream->pointer = stream->buffer + stream->size;
	}
	else if(whence == SET)
	{
		stream->pointer = stream->buffer;
	}
	else
	{
		return;
	}
	
	stream->pointer += offset;
}

void close(File* stream)
{
	free(stream->buffer);
	stream->pointer = nullptr;
	stream->size = 0;
}
