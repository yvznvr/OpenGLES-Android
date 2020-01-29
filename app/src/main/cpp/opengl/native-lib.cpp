#include <jni.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "DrawRectangle.h"
#include "../triangulation/Triangulate.h"

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

    Vector2dVector coords;
    for(int i=0; i<size; i+=2)
    {
        coords.push_back(Vector2d(arr[i], arr[i+1]));
    }

    Vector2dVector result;
    //  Invoke the triangulator to triangulate this polygon.
    Triangulate::Process(coords, result);
    int tcount = result.size() / 3;
    float trianglePoint[result.size()*2];
    for (int i = 0; i<tcount; i++)
    {
        const Vector2d &p1 = result[i * 3 + 0];
        const Vector2d &p2 = result[i * 3 + 1];
        const Vector2d &p3 = result[i * 3 + 2];
        trianglePoint[i*6] = p1.GetX();
        trianglePoint[i*6 +1] = p1.GetY();
        trianglePoint[i*6 +2] = p2.GetX();
        trianglePoint[i*6 +3] = p2.GetY();
        trianglePoint[i*6 +4] = p3.GetX();
        trianglePoint[i*6 +5] = p3.GetY();
    }

    pObject->setPoints(trianglePoint, result.size()*2);
}