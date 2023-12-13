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
#include <fstream>
#include <string>
#include "2d.shaders"

GLid_t getShader(GLenum shaderType, const char *shaderSourceCode)
{
    GLid_t id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderSourceCode, nullptr);
    glCompileShader(id);

    int good;
    glGetShaderiv(id, GL_COMPILE_STATUS, &good);

    if (!good)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length + 1);
        glGetShaderInfoLog(id, length, nullptr, message);
        wxLogDebug("Shader is Compiled with Failure: %s", message);
        free(message);
    }

    return id;
}

GLid_t getGLShadingProgram()
{

    // add the shaders, and compile them along with the program.
    GLid_t vertexShader = getShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLid_t fragmentShader = getShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLid_t shadingProgram = glCreateProgram();
    glAttachShader(shadingProgram, vertexShader);
    glAttachShader(shadingProgram, fragmentShader);
    glLinkProgram(shadingProgram);
    glValidateProgram(shadingProgram);

    // retrieving the state of the shader program.
    int good;
    glGetProgramiv(shadingProgram, GL_VALIDATE_STATUS, &good);

    if (!good)
    {
        int length;
        glGetProgramiv(shadingProgram, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length + 1);
        glGetShaderInfoLog(shadingProgram, length, nullptr, message);
        wxLogDebug("Shader is Compiled with Failure: %s", message);
    }
    glDeleteShader(vertexShader), glDeleteShader(fragmentShader);

    return shadingProgram;
}
