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

    layout (location = 0) in vec3 pos;
    void main()
    {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    };

    )";
    constexpr const char fragmentShaderSource[] = R"(
    #version 330 core

    uniform vec4 uColor;
    layout (location = 0) out vec4 color;

    void main()
    {
    color = uColor;
    };

    )";
}