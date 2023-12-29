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
}

#define xy_glRun(x) while (glGetError());x;xy::_glErrorLoopThroughAndLog(__LINE__, __FILE__)
