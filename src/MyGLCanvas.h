/*
 *
 * File:        src/MyGLCanvas.h
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2024-02-12
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#pragma once

#include <wx/wx.h>
#include <GL/glew.h>
#include <wx/glcanvas.h>
#include "xy/openGLDebug.h"
#include "xy/VertexBuffer.h"
#include "xy/IndexBuffer.h"
#include "xy/VertexArray.h"
#include "xy/Shader.h"
#include "xy/Renderer.h"
#include "xy/Texture.h"
#include "MyCamera.h"

// will be included in the cpp file.
class MyWindow;
class MyGLCanvas : public wxGLCanvas
{
private:
    bool isOpenGLInitialised;
    bool InitOpenGL();
    bool InitGLEW();
    void NextFrame();

    wxGLContext *_context;
    xy::VertexBuffer vb;
    xy::IndexBuffer<> ib; // default type is unsigned int
    xy::VertexArray va;
    xy::Shader shader;
    xy::Renderer renderer;
    xy::Texture tex;
    float WoverH;
    wxTimer timer;
    wxLongLong mLastFrameMicroseconds;
    glm::mat4 mPortProjectionMatrix, mRotation;
    MyCamera mCamera;

public:
    MyGLCanvas(MyWindow *, const wxGLAttributes &);
    ~MyGLCanvas();

    void OnKeyHeld(MoveDirection);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void OnSize(wxSizeEvent &event);
    void OnTimer(wxTimerEvent &WXUNUSED(event));
    void OnIdle(wxIdleEvent &WXUNUSED(event));
    inline void OnMouseMove(wxPoint const &mvt) { mCamera.OnTurn(mvt); };
};

// finished?