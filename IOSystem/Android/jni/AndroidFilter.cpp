#include <jni.h>
#include <malloc.h>

class Example
{
public:
    Example()
    {
        a = 3;
        b = 2;
    }
    ~Example()
    {

    }
    void matb()
    {
        a *= b;
    }
public:
    int a;
    int b;
};

int lol()
{
    Example a;
    a.matb();
    a.a -= 1;
    return a.a;
}

    extern "C" JNIEXPORT jstring JNICALL
        Java_com_UrbanEngine_main_MainActivity_AndroidLogicProcess(
            JNIEnv * env,
            jobject /* this */) {

        int a = lol();
        const char* text = "test0";
        char* test = (char*)malloc(6);
        for (int i = 0; i < 6; i++)
        {
            test[i] = text[i];
        }
        test[4] = 48 + a % 10;

        return env->NewStringUTF(test);
    }
