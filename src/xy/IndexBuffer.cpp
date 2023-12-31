/*
 *
 * File:        src/xy/IndexBuffer.cpp
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-26
 * Description: This is the index buffer, also called GL_ELEMENT_ARRAY_BUFFER in OpenGL.
 *
 */

#include "IndexBuffer.h"

template <typename T>
xy::IndexBuffer<T>::IndexBuffer(const data_t *data, size_t count)
{
    IndexBuffer();
    Init(data, count);
}

template <typename T>
xy::IndexBuffer<T>::IndexBuffer()
{
    mID = mCount = 0;
}

template <typename T>
void xy::IndexBuffer<T>::Init(const data_t *data, size_t count)
{
    xy_glRun(glGenBuffers(1, &mID));
    mCount = count;
    Bind();
    // xy_glRun(
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(data_t), data, GL_STATIC_DRAW);
    //);
}

template <typename T>
xy::IndexBuffer<T>::~IndexBuffer()
{
    if (!IsValid())
        return;
    xy_glRun(glDeleteBuffers(1, &mID));
    mID = 0;
    mCount = 0;
}

void xy::generic::IndexBuffer::Bind() const
{
    xy_glRun(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
}

void xy::generic::IndexBuffer::Unbind() const
{
    xy_glRun(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

template <typename T>
GLenum xy::IndexBuffer<T>::getGLenumType() const
{
    wxASSERT_MSG(false, "You dumbass constructed an Index Buffer with wrong type.");
    return 0;
}

template <>
GLenum xy::IndexBuffer<unsigned int>::getGLenumType() const
{
    return GL_UNSIGNED_INT;
}

// Force Instantiation of templates.
template xy::IndexBuffer<unsigned int>::IndexBuffer();
template xy::IndexBuffer<unsigned int>::~IndexBuffer();
template void xy::IndexBuffer<unsigned int>::Init(const unsigned int *, size_t);