/*
 *
 * File:        src/xy/openGLDebug.h
 * Author:      TNTErick
 * Created:     2023-11-24
 * Modified:    2023-12-26
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#include "openGLDebug.h"
#include <wx/debug.h>
#include <GL/glew.h>
void xy::_glErrorLoopThroughAndLog(int lineNum, const char *fileName)
{
    GLenum error = glGetError();
    if (error == GL_NO_ERROR)
        return;
    do
    {
        wxLogDebug("OpenGL Error in %s, line %d: (0X%04X) %s", fileName, lineNum, error, wxString::FromAscii(gluErrorString(error)));
    } while ((error = glGetError()) != GL_NO_ERROR);

    wxASSERT_MSG(false, "OpenGL Error");
}

unsigned int xy::glSizeOf(unsigned int glEnumType)
{
    switch (glEnumType)
    {
    case GL_UNSIGNED_BYTE:
        return sizeof(GLbyte);
    case GL_UNSIGNED_SHORT:
        return sizeof(GLushort);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    case GL_FLOAT:
        return sizeof(GLfloat);
    }

    wxASSERT_MSG(false, wxT("glSizeOf encounter an unknown type."));
}

template <typename T>
static constexpr GLenum glEnumTypeOf()
{
    wxASSERT_MSG(false, wxT("Unknown Type Encountered. Please add the type down below this page."));
}

template <>
static constexpr GLenum glEnumTypeOf<GLuint>()
{
    return GL_UNSIGNED_INT;
}
