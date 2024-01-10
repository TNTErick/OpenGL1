/*
 *
 * File:        src/xy/Shader.cpp
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-12-26
 * Description: This file implements the shaders that the program needs.
 * Change:      2023-12-25 shaders.cpp -> Shader.cpp
 */

#include "Shader.h"
#include <fstream>
#include "2dshaders.h"

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

    if (_DEBUG)
    {
        int count;
        glGetProgramiv(shadingProgram, GL_ACTIVE_UNIFORMS, &count);
        wxLogDebug("There are %d uniforms:", count);
        GLuint i;
        GLsizei len, size;
        GLenum type;
        char buffer[512];
        memset(buffer, 0, sizeof(buffer));

        for (i = 0; i < count; i++)
        {
            glGetActiveUniform(shadingProgram, i, 511, &len, &size, &type, buffer);
            wxLogDebug("\tUniform #%03d Type: %X Name: %s", i, type, buffer);
        }
    }
    return shadingProgram;
}

xy::Shader::Shader()
    : mID(0),
      mUniforms()
{
}

xy::Shader::~Shader()
{
    if (!IsValid())
        return;
    xy_glRun(glDeleteProgram(mID));
    mID = 0;
}

void xy::Shader::Init()
{
    xy_glRun(mID = getGLShadingProgram());
}

void xy::Shader::Bind() const
{
    xy_glRun(glUseProgram(mID));
}

void xy::Shader::Unbind() const
{
    xy_glRun(glUseProgram(0));
}

GLint xy::Shader::GetUniformLocation(const std::string &name)
{
    xy_glRun(GLint i = glGetUniformLocation(mID, name.c_str()));
    if (i == -1)
        wxASSERT_MSG(false, "Invalid Uniform Name!");
    return i;
}

template<typename T>
void xy::Shader::SetUniform(const std::string &, const T&)
{
    wxASSERT_MSG(false, "Invalid Uniform Type!");
}

template<>
void xy::Shader::SetUniform<glm::vec4>(const std::string &name, const glm::vec4& value)
{
    xy_glRun(glUniform4f(GetUniformLocation(name), (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z, (GLfloat)value.w));
}

template<>
void xy::Shader::SetUniform<int>(const std::string &name, const int& i)
{
    xy_glRun(glUniform1i(GetUniformLocation(name), i));
}

template<>
void xy::Shader::SetUniform<glm::mat4>(const std::string &name, const glm::mat4& matrix)
{
    xy_glRun(glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE, &matrix[0][0]));
}