/*
 *
 * File:        src/VertexBuffer.cpp
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-26
 * Description: This class provides wrapping for vertex buffers in opengl.
 *
 */

#include "VertexBuffer.h"
using namespace xy;

VertexBuffer::VertexBuffer() : mID(0) {}

VertexBuffer::VertexBuffer(const void *data, size_t bytes)
{
    VertexBuffer();
    Init(data, bytes);
}

VertexBuffer::~VertexBuffer()
{
    if (!IsValid())
        return;
    xy_glRun(glDeleteBuffers(1, &mID));
    mID = 0;
}

void VertexBuffer::Init(const void *data, size_t bytes)
{
    xy_glRun(glGenBuffers(1, &mID));
    Bind();
    xy_glRun(glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    xy_glRun(glBindBuffer(GL_ARRAY_BUFFER, mID));
}

void VertexBuffer::Unbind() const
{
    xy_glRun(glBindBuffer(GL_ARRAY_BUFFER, 0));
}