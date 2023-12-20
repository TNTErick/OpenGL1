/*
 *
 * File:        src/OpenGL/VertexBuffer.h
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-21
 * Description: This class wraps up the vertex buffer.
 *
 */

#pragma once
#ifndef __XY_VERTEX_BUFFER_H
#define __XY_VERTEX_BUFFER_H

#include "openGLDebug.h"

class VertexBuffer
{
private:
    GLid_t mID;

public:
    VertexBuffer();
    VertexBuffer(const void *data, size_t bytes);
    ~VertexBuffer();

    void Init(const void *data, size_t bytes);
    inline const bool IsValid() const { return mID != 0; }

    void Bind() const;
    void Unbind() const;
};

#endif //__XY_VERTEX_BUFFER_H