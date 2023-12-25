/*
 *
 * File:        src/openGLDebug.h
 * Author:      TNTErick
 * Created:     2023-11-24
 * Modified:    2023-11-24
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */
#pragma once
#ifndef __XY_OPENGL_DEBUG_H
#define __XY_OPENGL_DEBUG_H
#include <wx/wx.h>
#include <GL/glew.h>

#define XY_GLVMA 3
#define XY_GLVMIN 3
typedef wxUint32 GLid_t;

namespace xy
{

    void _glErrorLoopThroughAndLog(int lineNum, const char *fileName);

    unsigned int glSizeOf(unsigned int glEnumType);
}

#define xy_glRun(x) while (glGetError());x;xy::_glErrorLoopThroughAndLog(__LINE__, __FILE__)

#endif