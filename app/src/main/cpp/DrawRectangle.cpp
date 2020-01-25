//
// Created by Yavuz on 24.01.2020.
//

#include "DrawRectangle.h"
#include <GLES2/gl2.h>

static const char glVertexShader[] =
        "attribute vec4 vPosition;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vPosition;\n"
        "}\n";

static const char glFragmentShader[] =
        "precision mediump float;\n"
        "void main()\n"
        "{\n"
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

DrawRectangle::DrawRectangle()
{

}
void DrawRectangle::onSurfaceCreated()
{
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void DrawRectangle::onSurfaceChanged()
{

}

void DrawRectangle::onDrawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
}