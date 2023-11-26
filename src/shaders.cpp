/*
 *
 * File:        src/shaders.cpp
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-11-25
 * Description: This file implements the shaders that the program needs.
 *
 */

#include "shaders.h"

GLid_t getShader(GLenum shaderType, const char* shaderSourceCode)
{
    GLid_t id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderSourceCode, nullptr);
    glCompileShader(id);

    int good;
    char infoBuffer[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &good);

    if(!good)
    {
        glGetShaderInfoLog(id, sizeof infoBuffer, nullptr, infoBuffer);
        wxLogDebug("Shader of Vertices is Compiled with Failure:%s", infoBuffer);
    }

    return id;
}
