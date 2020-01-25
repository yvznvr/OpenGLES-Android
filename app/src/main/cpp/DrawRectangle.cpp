//
// Created by Yavuz on 24.01.2020.
//

#include "DrawRectangle.h"

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

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

DrawRectangle::DrawRectangle()
{



}

GLuint DrawRectangle::loadShader(GLuint shaderType, const char *shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char * buf = new char[infoLen];
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    delete[] buf;
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint DrawRectangle::createProgram(const char *vertexSource, const char *fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }
    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);
        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = new char[bufLength];
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    delete[] buf;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}
void DrawRectangle::onSurfaceCreated()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    shaderProgram = createProgram(glVertexShader, glFragmentShader);
    if (!shaderProgram)
    {
        LOGE ("Could not create program");
    }
    vPosition = glGetAttribLocation(shaderProgram, "vPosition");
    //glViewport(0, 0, w, h);
}

void DrawRectangle::onSurfaceChanged()
{

}

void DrawRectangle::onDrawFrame()
{
    GLfloat verticeMatrix[] = {
            0.0f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0 ,verticeMatrix);
    glEnableVertexAttribArray(vPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}