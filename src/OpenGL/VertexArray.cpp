/*
 *
 * File:        src/VertexArray.cpp
 * Author:      TNTErick
 * Created:     2023-12-25
 * Modified:    2023-12-25
 * Description: This class provides wrapping for vertex attrib arrays in opengl.
 *
 */
#include "VertexArray.h"
#include <vector>
#include "openGLDebug.h"

VertexArray::VertexArray() : mID(0) {}

VertexArray::~VertexArray()
{
    if (!isValid())
        return;

    xy_glRun(glDeleteVertexArrays(1, &mID));
    mID = 0;
}

bool VertexArray::Init()
{
    xy_glRun(glGenVertexArrays(1, &mID));
    return isValid();
}

void VertexArray::Bind() const
{
    xy_glRun(glBindVertexArray(mID));
}

void VertexArray::Unbind() const
{
    xy_glRun(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
{
    Bind();
    buffer.Bind();
    const std::vector<VertexBufferElement> &elements = layout.GetElements();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const VertexBufferElement &elem = elements[i];
        xy_glRun(glEnableVertexAttribArray(i));
        xy_glRun(glVertexAttribPointer(
            i,
            elem.count,
            elem.glEnumType,
            elem.normalised ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void *)offset));
        offset += elem.count * xy::glSizeOf(elem.glEnumType);
    }

    Unbind();
}