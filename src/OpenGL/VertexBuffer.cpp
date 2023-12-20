/*
 *
 * File:        src/VertexBuffer.cpp
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-21
 * Description: This class provides wrapping for vertex buffers in opengl.
 *
 */

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() : mID(0) {}

VertexBuffer::VertexBuffer(const void *data, size_t bytes)
{
    VertexBuffer();
    Init(data, bytes);
}

VertexBuffer::~VertexBuffer()
{
    xy_glError(glDeleteBuffers(1, &mID));
}

void VertexBuffer::Init(const void *data, size_t bytes)
{
    xy_glError(glGenBuffers(1, &mID));
    Bind();
    xy_glError(glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    xy_glError(glBindBuffer(GL_ARRAY_BUFFER, mID));
}

void VertexBuffer::Unbind() const
{
    xy_glError(glBindBuffer(GL_ARRAY_BUFFER, 0));
}