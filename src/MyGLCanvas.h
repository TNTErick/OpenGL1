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
#include "xy/openGLDebug.h"
#include "xy/VertexBuffer.h"
#include "xy/IndexBuffer.h"
#include "xy/VertexArray.h"
#include "xy/Shader.h"
#include "xy/Renderer.h"

// will be included in the cpp file.
class MyWindow;
class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(MyWindow *, const wxGLAttributes &);
    ~MyGLCanvas();

    // bool Destroy() override;

    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void OnSize(wxSizeEvent &event);
    void OnTimer(wxTimerEvent &WXUNUSED(event));

private:
    bool InitOpenGL();
    bool InitGLEW();
    bool isOpenGLInitialised;

    wxGLContext *_context;
    xy::VertexBuffer vb;
    xy::IndexBuffer<> ib; // default type is unsigned int
    xy::VertexArray va;
    xy::Shader shader;
    xy::Renderer renderer;
    float r, incr;
    wxTimer timer;
};

#endif

// finished?