//
// Created by Yavuz on 24.01.2020.
//

#ifndef GLRECT_DRAWRECTANGLE_H
#define GLRECT_DRAWRECTANGLE_H

#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <math.h>

class DrawRectangle {
public:
    DrawRectangle();
    void onSurfaceCreated();
    void onSurfaceChanged();
    void onDrawFrame();
    void setPoints(float *points, int size);

private:
    GLuint loadShader(GLuint shaderType, const char* shaderSource);
    GLuint createProgram(const char* vertexSource, const char* fragmentSource);
    GLuint shaderProgram;
    GLuint vPosition;
    float hue = 0;
    int vertexSize = 0;
    GLfloat *vertexPoints = nullptr;
};


#endif //GLRECT_DRAWRECTANGLE_H
