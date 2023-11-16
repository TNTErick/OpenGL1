/*
 *
 * File:        src/MyGLCanvas.h
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-11-12
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#pragma once
#ifndef __XY_MY_GL_CANVAS_H__
#define __XY_MY_GL_CANVAS_H__

#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include "utils.h"

class MyWindow;
class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(MyWindow *parent, const wxGLAttributes &canvasAttributes);
    ~MyGLCanvas();

    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);

private:
    bool InitOpenGL();
    bool InitOpenGLFunctions();
    bool isOpenGLInitialised;

    wxGLContext *_context;
    GLid_t vao, vbo, shader;
};

#endif

// finished?