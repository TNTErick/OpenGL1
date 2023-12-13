/*
 *
 * File:        src/MyGLCanvas.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-11-15
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#include <wx/log.h>
#include "MyGLCanvas.h"
#include "MyWindow.h"
#include "OpenGL/shaders.h"

// init the canvas with the wxGLContext.
MyGLCanvas::MyGLCanvas(MyWindow *parent, const wxGLAttributes &attrs)
    : wxGLCanvas(parent, attrs, wxID_ANY),
      isOpenGLInitialised(false),
      _context(nullptr),
      r(0.f),
      incr(.05f),
      timer(this)
{
    // context.
    wxGLContextAttrs oglattrs;
    oglattrs.PlatformDefaults().CompatibilityProfile().OGLVersion(XY_GLVMA, XY_GLVMIN).EndList(); // TODO
    _context = new wxGLContext(this, nullptr, &oglattrs);

    if (!_context->IsOK())
    {
        wxMessageBox(
            "Your OpenGL version is Older than 3.3 and is incompatible with the program. Please update your graphic driver.",
            "OpenGL Init Error",
            wxOK | wxICON_ERROR,
            this);
        delete _context;
        _context = nullptr;
    }

    // timer.
    if (!timer.Start(30))
    {
        wxLogDebug("Cannot start timer");
    }

    // bind events.
    Bind(wxEVT_PAINT, &MyGLCanvas::OnPaint, this);
    Bind(wxEVT_SIZE, &MyGLCanvas::OnSize, this);
    Bind(wxEVT_TIMER, &MyGLCanvas::OnTimer, this);
}

// deconstruct the object by deleting context
MyGLCanvas::~MyGLCanvas()
{
    delete _context;
}

bool MyGLCanvas::InitOpenGL()
{
    // set OpenGL context; if it is nullptr, then construction failed.
    if (!_context)
        return false;
    SetCurrent(*_context);

    // init opengl functions
    if (!InitGLEW())
    {
        wxMessageBox(
            "Could not initialize OpenGL function pointers.",
            "OpenGL Initialisation Error",
            wxOK | wxICON_ERROR,
            this);
        return false;
    }

    // log the infos of OpenGL versions. copied from tutorials.
    wxLogDebug("OpenGL version: %s", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    wxLogDebug("OpenGL vendor: %s", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));

    // initialise data used for rendering.

    // vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float vertices[] = {
        -.5f, -.5f, 0.f,
        .5f, -.5f, 0.f,
        .5f, .5f, 0.f,
        -.5f, .5f, 0.f};
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    // ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    // attrib array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // shader program
    shadingProgram = getGLShadingProgram();

    // unbind everything and return.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    _glErrorLoopThroughAndLog(__LINE__, __FILE__);

    isOpenGLInitialised = true;
    return true;
}

bool MyGLCanvas::InitGLEW()
{
    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        wxLogError("OpenGL GLEW Initialisation Failed: %s", reinterpret_cast<const char *>(glewGetErrorString(status)));
        return false;
    }

    wxLogDebug("Status: Using GLEW %s", reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));

    return true;
}

void MyGLCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    _glErrorLoopThroughAndLog(__LINE__, __FILE__);
    wxPaintDC dc(this);

    if (!isOpenGLInitialised)
        return;

    _c(SetCurrent(*_context));

    _c(glClearColor(0.f, 0.f, 0.f, 1.f));
    _c(glClear(GL_COLOR_BUFFER_BIT));

    _c(glUseProgram(shadingProgram));
    _c(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    _c(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    _c(glBindVertexArray(vao));

    // TODO: change this to draw the thingies in the cherno vid.
    //  set the color
    int colorLocation = glGetUniformLocation(shadingProgram, "u_Color");
    _c(glUniform4f(colorLocation, r, 0.f, .5f, 1.f));

    _c(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0));

    r += incr;
    if (r >= 1.f)
        incr = -.05f;
    else if (r <= 0.f)
        incr = .05f;

    SwapBuffers();
}

// Resize the canvas (or initial OpenGL of the canvas if not yet)
void MyGLCanvas::OnSize(wxSizeEvent &event)
{
    bool firstApperance = IsShownOnScreen() && !isOpenGLInitialised;

    if (firstApperance)
    {
        InitOpenGL();
    }

    if (isOpenGLInitialised)
    {
        auto viewPortSize = event.GetSize() * GetContentScaleFactor();
        // TODO: change the code here. Resizing the glViewport may result in too high framerate.
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
    }

    event.Skip();
}

void MyGLCanvas::OnTimer(wxTimerEvent &WXUNUSED(evt))
{
    // wxPostEvent(this, wxPaintEvent());
    //  wxPaintEvent is no longer constructable.

    Refresh();
}