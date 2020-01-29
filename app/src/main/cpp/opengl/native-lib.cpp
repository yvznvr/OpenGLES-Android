#include <jni.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "DrawRectangle.h"
#include "../delaunator/delaunator.h"

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

/*
extern "C" JNIEXPORT void JNICALL
        Java_com_example_glrect_MyRenderer_setPoints(
        JNIEnv *env,
        jobject jobj,
        jfloatArray points){

    jsize size = env->GetArrayLength(points);
    float arr[size];
    env->GetFloatArrayRegion(points,0,size,arr);
    pObject->setPoints(arr, size);
    delaunator::Delaunator d();

}
*/

extern "C" JNIEXPORT jfloatArray JNICALL
Java_com_example_glrect_MyRenderer_setPoints(
        JNIEnv *env,
        jobject jobj,
        jfloatArray points){

    jsize size = env->GetArrayLength(points);
    float arr[size];
    env->GetFloatArrayRegion(points,0,size,arr);

    std::vector<double> coords;
    for(int i=0; i<size; i++)
    {
        coords.push_back(arr[i]);
    }
    delaunator::Delaunator d(coords);

    int pointSize = d.triangles.size()*2;
    float trianglePoint[pointSize];
    jfloatArray javaArr  = env->NewFloatArray(pointSize);

    for (std::size_t i = 0; i < d.triangles.size(); i += 3) {
        trianglePoint[2*i] = d.coords[2 * d.triangles[i]];
        trianglePoint[2*i + 1] = d.coords[2 * d.triangles[i] + 1];
        trianglePoint[2*i + 2] = d.coords[2 * d.triangles[i + 1]];
        trianglePoint[2*i + 3] = d.coords[2 * d.triangles[i + 1] + 1];
        trianglePoint[2*i + 4] = d.coords[2 * d.triangles[i + 2]];
        trianglePoint[2*i + 5] = d.coords[2 * d.triangles[i + 2] + 1];
    }
    env->SetFloatArrayRegion(javaArr,0,pointSize,trianglePoint);

    pObject->setPoints(trianglePoint, pointSize);

    return javaArr;
}