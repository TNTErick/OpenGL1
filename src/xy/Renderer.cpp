/*
 *
 * File:        src/xy/Renderer.h
 * Author:      TNTErick
 * Created:     2023-12-21
 * Modified:    2024-02-08
 * Description: This class is responsible for call drawings to openGL, so that
 *              the code in `MyGLCanvas` can be clean.
 */

#include "Renderer.h"

void xy::Renderer::Draw(const xy::VertexArray &vertexArray, const xy::generic::IndexBuffer &indices, const xy::Shader &shader) const
{
    shader.Bind();
    vertexArray.Bind();
    indices.Bind();
    xy_glRun(glDrawElements(GL_TRIANGLES, indices.getSize(), indices.getGLenumType(), (void *)0));
}