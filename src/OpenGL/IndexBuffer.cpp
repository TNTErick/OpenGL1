/*
 *
 * File:        src/OpenGL/IndexBuffer.cpp
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-21
 * Description: This is the index buffer, also called GL_ELEMENT_ARRAY_BUFFER in OpenGL.
 *
 */

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, size_t count)
{
    IndexBuffer();
    Init(data, count);
}

IndexBuffer::IndexBuffer() : mID(0),
                             mCount(0)
{
}

void IndexBuffer::Init(const unsigned int *data, size_t count)
{
    xy_glRun(glGenBuffers(1, &mID));
    Bind();
    // xy_glRun(
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    //);
}

IndexBuffer::~IndexBuffer()
{
    if (!IsValid())
        return;
    xy_glRun(glDeleteBuffers(1, &mID));
    mID = 0;
    mCount = 0;
}

void IndexBuffer::Bind() const
{
    xy_glRun(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
}

void IndexBuffer::Unbind() const
{
    xy_glRun(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}