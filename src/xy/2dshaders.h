/*
 *
 * File:        src/xy/2d.shaders
 * Author:      TNTErick
 * Created:     2023-12-13
 * Modified:    2023-12-26
 * Description: This is where shader is placed. Still treated as a cpp include file.
 *
 */

#pragma once
namespace
{
    constexpr const char vertexShaderSource[] = R"(
    #version 330 core

    layout (location = 0) in vec2 pos;
    layout (location = 1) in vec2 texCoord;
    uniform mat4 uMVP;

    out vec2 vTexCoord;

    void main()
    {
        gl_Position = uMVP * vec4(pos.x, pos.y, 0.0f, 1.0f);
        vTexCoord = texCoord;
    };

    )";
    constexpr const char fragmentShaderSource[] = R"(
    #version 330 core

    in vec2 vTexCoord;
    uniform sampler2D uTexture;

    layout (location = 0) out vec4 color;

    void main()
    {
        color = texture(uTexture, vTexCoord);
    };

    )";
}