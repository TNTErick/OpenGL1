/*
 *
 * File:        src/MyGLCanvas.cpp
 * Author:      TNTErick
 * Created:     2023-11-12
 * Modified:    2023-12-25
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#include <wx/log.h>
#include "MyGLCanvas.h"
#include "MyWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// init the canvas with the wxGLContext.
MyGLCanvas::MyGLCanvas(MyWindow *parent, const wxGLAttributes &attrs)
    : wxGLCanvas(parent, attrs, wxID_ANY),
      isOpenGLInitialised(false),
      _context(nullptr),
      r(0.f),
      incr(.05f),
      timer(this),
      vb(),
      ib(),
      va(),
      shader(),
      renderer(),
      tex()
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
        wxASSERT_MSG(false, "OpenGL context is not initialized.");
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
    vb.~VertexBuffer();
    ib.~IndexBuffer();
    va.~VertexArray();
    tex.~Texture();
    shader.~Shader();
    delete _context;
}

bool MyGLCanvas::InitOpenGL()
{
    // set OpenGL context; if it is nullptr, then construction failed.
    if (!_context)
        return false;
    SetCurrent(*_context);

    xy_glRun(glEnable(GL_DEBUG_OUTPUT));
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

    float vertices[] = {
        //  x,y in space; x,y in texture coordinates
        .5f, .5f, 1.f, 1.f,
        .5f, -.5f, 1.f, 0.f,
        -.5f, -.5f, 0.f, 0.f,
        -.5f, .5f, 0.f, 1.f};

    vb.Init(vertices, sizeof(vertices));

    unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0,
        };
    ib.Init(indices, 6);

    va.Init();
    xy::VertexBufferLayout layout;
    layout.Push<float>(2); // x y
    layout.Push<float>(2); // texture pos
    va.AddBuffer(vb, layout);

    // compile shader.
    shader.Init();
    shader.Bind();

    // texture
    tex.Init("uv-test.png");
    tex.Bind(0);
    shader.SetUniform<int>("uTexture", 0);

    // Blend.
    xy_glRun(glEnable(GL_BLEND));
    xy_glRun(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // unbind everything and return.
    vb.Unbind();
    ib.Unbind();
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

// Event Handling.

void MyGLCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    // wxPaintDC dc(this);

    SetCurrent(*_context);
    if (!isOpenGLInitialised || !vb.IsValid() || !ib.IsValid() || !shader.IsValid() || !va.IsValid() || !tex.IsValid())
        return;

    tex.Bind();
    va.Bind();
    vb.Bind();
    ib.Bind();

    //  draw the void at the back.
    xy_glRun(glClearColor(0.f, 0.f, 0.f, 1.f));
    xy_glRun(glClear(GL_COLOR_BUFFER_BIT));
    shader.Bind();

    // TODO: change this to draw the thingies in the cherno vid.
    // shader.SetUniform4f("uColor", glm::vec4(r, .5f, .7f, 1.f));

    renderer.Draw(va, ib, shader);

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

    // re-sync the uniform variable to openGL.
    if (firstApperance)
    {
        InitOpenGL();
    }

    if (isOpenGLInitialised)
    {
        auto size = event.GetSize() * GetContentScaleFactor();
        glViewport(0, 0, size.x, size.y);
        
        auto viewProjectionMatrix = glm::ortho(
            -((float)size.x / size.y),
            ((float)size.x / size.y),
            -1.f,
            1.f,
            -1.f,
            1.f);

        shader.Bind();
        shader.SetUniform<glm::mat4>("uMVP", viewProjectionMatrix);

    }

    event.Skip();
}

void MyGLCanvas::OnTimer(wxTimerEvent &WXUNUSED(evt))
{
    // wxPostEvent(this, wxPaintEvent());
    //  wxPaintEvent is no longer constructable.

    Refresh();
}
