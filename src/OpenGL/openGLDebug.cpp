/*
 *
 * File:        src/openGLDebug.h
 * Author:      TNTErick
 * Created:     2023-11-24
 * Modified:    2023-11-24
 * Description: `MyGLCanvas` is a descendant of `wxGLCanvas` in which OpenGL can draw.
 *
 */

#include "openGLDebug.h"
void _glErrorLoopThroughAndLog(int lineNum, const char *fileName)
{
    for (GLenum error; (error = glGetError()) != GL_NO_ERROR;)
        wxLogDebug("OpenGL Error in %s, line %d: (%04X) %s", fileName, lineNum, error, gluErrorString(error));
}