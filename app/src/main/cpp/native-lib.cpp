#include <jni.h>
#include <string>
#include "DrawRectangle.h"
#include <stdio.h>

static DrawRectangle *pObject = new DrawRectangle();

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_glrect_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello Native";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_glrect_MyRenderer_surfaceCreated(
        JNIEnv *env,
        jobject /* this */) {
    pObject->onSurfaceCreated();
    //printf("adadasdadasdadad");
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_glrect_MyRenderer_drawFrame(
        JNIEnv *env,
        jobject /* this */) {
    pObject->onDrawFrame();
    //printf("adadasdadasdadad");
}
