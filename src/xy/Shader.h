/*
 *
 * File:        src/xy/Shader.h
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-12-26
 * Description: This file implements the shaders that the program needs.
 * Change:      1225 shaders.h -> Shader.h
 */

#pragma once

#include <glm/glm.hpp>
#include "openGLDebug.h"
#include <string>
#include <map>
namespace xy
{
    class Shader
    {
    private:
        GLid_t mID;
        // std::map<std::string, int> mUniforms;

        GLint GetUniformLocation(const std::string &name);
    public:
        Shader();
        ~Shader();
        void Bind() const;
        void Unbind() const;
        void Init();

        void ResizeWindow(const wxSize& size) const;
        inline bool IsValid() const { return mID != 0; }
        template<typename T> void SetUniform(const std::string&, const T&);
        // void SetUniform4f(const std::string &name, const glm::vec4 &value) const;
        // void SetUniform1i(const std::string &name, int i) const;

    };
}