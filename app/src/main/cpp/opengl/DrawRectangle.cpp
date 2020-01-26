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
        "uniform float hue;\n"
        "vec3 hsv2rgb(vec3 c)\n"
        "{\n"
        "  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);\n"
        "  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);\n"
        "  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);\n"
        "}\n"
        "void main()\n"
        "{\n"
        "  vec3 fragColor = hsv2rgb(vec3(hue, 1.0, 1.0));\n"
        "  gl_FragColor = vec4(fragColor, 1.0);\n"
        "}\n";

#define LOG_TAG "libNative"
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
}

void DrawRectangle::onSurfaceChanged()
{

}

void DrawRectangle::onDrawFrame()
{
    // This function draw shape in each frame
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    // to changing color, increments value of hue channel value in HSV color space
    GLint loc = glGetUniformLocation(shaderProgram, "hue");
    if(loc != -1)
    {
        glUniform1f(loc, hue);
    }

    if(hue < 1.0f)
    {
        hue = hue + 0.01f;
    }
    else
    {
        hue = 0;
    }
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0 ,vertexPoints);
    glEnableVertexAttribArray(vPosition);
    glDrawArrays(GL_TRIANGLES, 0, vertexSize);
}

void DrawRectangle::setPoints(float *points, int size)
{
    // set points and size of polygon
    delete[] vertexPoints;
    vertexSize = size;
    vertexPoints = new float[size];
    for(int i=0; i<size; i++)
    {
        vertexPoints[i] = points[i];
    }
}