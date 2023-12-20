/*
 *
 * File:        src/OpenGL/IndexBuffer.h
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-21
 * Description: This is the class wrapper for Element Array Buffer.
 *
 */

#pragma once
#ifndef __XY_INDEX_BUFFER_H
#define __XY_INDEX_BUFFER_H

#include "openGLDebug.h"

class IndexBuffer
{
private:
    GLid_t mID;
    size_t mCount;

public:
    IndexBuffer();
    IndexBuffer(const unsigned int *data, size_t count);
    ~IndexBuffer();

    void Init(const unsigned int *data, size_t count);
    void Bind() const;
    void Unbind() const;

    inline const bool IsValid() const { return mID != 0; }
    inline const size_t getSize() const { return mCount; }
};

#endif //__XY_INDEX_BUFFER_H