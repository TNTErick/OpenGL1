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
    glGetShaderiv(id, GL_COMPILE_STATUS, &good);

    if(!good)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length +1 );
        glGetShaderInfoLog(id, length, nullptr, message);
        wxLogDebug("Shader is Compiled with Failure: %s", message);
    }

    return id;
}

GLid_t getGLShadingProgram()
{
    
    // add the shaders, and compile them along with the program.
    constexpr const GLchar *vertexShaderSourceCode = R"(
        #version 330 core
        layout (location = 0) in vec3 pos;
        void main()
        {
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        }
    )";

    GLid_t vertexShader = getShader(GL_VERTEX_SHADER, vertexShaderSourceCode);

    constexpr const GLchar *fragmentShaderSourceCode = R"(
        #version 330 core
        out vec4 fragColor;
        uniform vec4 triangleColor;
        void main()
        {
            fragColor = triangleColor;
        }
    )";

    GLid_t fragmentShader = getShader(GL_FRAGMENT_SHADER, fragmentShaderSourceCode);


    GLid_t shadingProgram = glCreateProgram();
    glAttachShader(shadingProgram, vertexShader);
    glAttachShader(shadingProgram, fragmentShader);
    glLinkProgram(shadingProgram);
    glValidateProgram(shadingProgram);

    //TODO: error handling with retrieving the state of the shader program.

    glDeleteShader(vertexShader), glDeleteShader(fragmentShader);

    return shadingProgram;
}
