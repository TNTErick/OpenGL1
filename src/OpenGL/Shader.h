/*
 *
 * File:        src/Shader.h
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-12-25
 * Description: This file implements the shaders that the program needs.
 * Change:      1225 shaders.h -> Shader.h
 */

#pragma once

#include <glm/glm.hpp>
#include "openGLDebug.h"
#include <string>

class Shader
{
private:
    GLid_t mID;

public:
    Shader();
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void Init();

    inline bool isValid() const { return mID != 0; }
    void SetUniform4f(const std::string &name, const glm::vec4 &value) const;

private:
    GLint GetUniformLocation(const std::string &name) const;
};