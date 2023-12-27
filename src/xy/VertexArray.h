/*
 *
 * File:        src/xy/VertexArray.h
 * Author:      TNTErick
 * Created:     2023-12-21
 * Modified:    2023-12-26
 * Description: This class provides wrapping for vertex attrib arrays in opengl.
 *
 */

#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
namespace xy
{
    class VertexArray
    {
    private:
        GLid_t mID;

    public:
        VertexArray();
        ~VertexArray();

        bool Init();
        inline bool isValid() const { return mID != 0; }

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);
    };
}