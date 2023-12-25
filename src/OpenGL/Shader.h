/*
 *
 * File:        src/shaders.h
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-11-25
 * Description: This file implements the shaders that the program needs.
 *
 */

#pragma once

#include <wx/glcanvas.h>
#include <glm/glm.hpp>
#include "openGLDebug.h"
#include<string>

class Shader
{
private:
    unsigned int mID;
    unsigned int GetUniformLocation(const std::string &name);

public:
    Shader(); //
    ~Shader();
    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string &name, const glm::vec4 value);
};