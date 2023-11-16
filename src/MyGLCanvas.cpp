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
#include "utils.h"

// init the canvas with the wxGLContext.
MyGLCanvas::MyGLCanvas(MyWindow *parent, const wxGLAttributes &attrs)
    : wxGLCanvas(parent, attrs, wxID_ANY),
      isOpenGLInitialised(false),
      _context(nullptr)
{
    wxGLContextAttrs oglattrs;
    oglattrs.PlatformDefaults().CoreProfile().OGLVersion(XY_GLVMA, XY_GLVMIN).EndList();
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

    Bind(wxEVT_PAINT, &MyGLCanvas::OnPaint, this);
    Bind(wxEVT_SIZE, &MyGLCanvas::OnSize, this);
}

// deconstruct the object by deleting context
MyGLCanvas::~MyGLCanvas()
{
    delete _context;
}

bool MyGLCanvas::InitOpenGL()
{
    // set context; if it is nullptr, then construction failed.
    if (!_context)
        return false;
    SetCurrent(*_context);

    // init opengl functions
    if (!InitOpenGLFunctions())
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

    // add the shaders.
    constexpr const GLchar *srcshVertex = R"(
        #version 330 core
        layout (location = 0) in vec3 pos;
        void main()
        {
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        }
    )";

    GLid_t shVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shVertex, 1, &srcshVertex, nullptr);
    glCompileShader(shVertex);

    int success;
    char infoLog[512];
    glGetShaderiv(shVertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shVertex, sizeof infoLog, nullptr, infoLog);
        wxLogDebug("Shader of Vertices is Compiled with Failure:%s", infoLog);
    }

    constexpr const GLchar *srcshFragment = R"(
        #version 330 core
        out vec4 fragColor;
        uniform vec4 triangleColor;
        void main()
        {
            fragColor = triangleColor;
        }
    )";

    GLid_t shFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shFragment, 1, &srcshFragment, nullptr);
    glCompileShader(shFragment);

    glGetShaderiv(shFragment, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shFragment, sizeof infoLog, nullptr, infoLog);
        wxLogDebug("Shader of Fragments is Compiled with Failure: %s", infoLog);
    }

    // create the shader, and delete the shaders for they are no longer needed.
    shader = glCreateProgram();
    glAttachShader(shader, shVertex);
    glAttachShader(shader, shFragment);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        wxLogDebug("Shader Program Linking Failed: %s", infoLog);
    }

    glDeleteShader(shVertex), glDeleteShader(shFragment);

    // create VAO and VBO; put the id to this->VAO and this->VBO

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // draw the triangle
    float vertices[] =
        {
            -.5f, -.5f, 0.f,
            .5f, -.5f, 0.f,
            0.f, .5f, 0.f};

    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(0);

    isOpenGLInitialised = true;
    return true;
}

bool MyGLCanvas::InitOpenGLFunctions()
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
    wxPaintDC dc(this);

    if (!isOpenGLInitialised)
        return;

    SetCurrent(*_context);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    // set the color
    int colorLocation = glGetUniformLocation(shader, "triangleColor");
    glUniform4f(colorLocation, 1.f, 0.f, 0.f, 1.f);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
    }

    event.Skip();
}
