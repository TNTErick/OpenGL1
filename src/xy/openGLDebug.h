/*
 *
 * File:        src/xy/openGLDebug.h
 * Author:      TNTErick
 * Created:     2023-11-24
 * Modified:    2023-12-26
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */
#pragma once
#include <wx/wx.h>
#include <GL/glew.h>

#define XY_GLVMA 3
#define XY_GLVMIN 3
typedef wxUint32 GLid_t;

namespace xy
{

    void _glErrorLoopThroughAndLog(int lineNum, const char *fileName);

    unsigned int glSizeOf(unsigned int glEnumType);

    template <typename T>
    static constexpr GLenum glEnumTypeOf();
    constexpr long double PI = 3.1415926535897932384626433832795028841971693993L;
    constexpr long double TE = PI / 2.L;
    constexpr long double TAU = PI * 2.L;
}

#define xy_glRun(x)      \
    while (glGetError()) \
        ;                \
    x;                   \
    xy::_glErrorLoopThroughAndLog(__LINE__, __FILE__)
