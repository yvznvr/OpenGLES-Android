#include <jni.h>
#include <string>
#include "DrawRectangle.h"
#include <stdio.h>

static DrawRectangle *pObject = new DrawRectangle();

extern "C" JNIEXPORT void JNICALL
Java_com_example_glrect_MyRenderer_surfaceCreated(
        JNIEnv *env,
        jobject /* this */) {
    pObject->onSurfaceCreated();
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_glrect_MyRenderer_drawFrame(
        JNIEnv *env,
        jobject /* this */) {
    pObject->onDrawFrame();
}

extern "C" JNIEXPORT void JNICALL
        Java_com_example_glrect_MyRenderer_setPoints(
        JNIEnv *env,
        jobject jobj,
        jfloatArray points){

    jsize size = env->GetArrayLength(points);
    float arr[size];
    env->GetFloatArrayRegion(points,0,size,arr);
    pObject->setPoints(arr, size);

}