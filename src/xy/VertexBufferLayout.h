/*
 *
 * File:        src/xy/VertexBufferLayout.h
 * Author:      TNTErick
 * Created:     2023-12-21
 * Modified:    2023-12-26
 * Description: This class is used in VertexArray to represent a layout for a vertex buffer.
 *
 */
#pragma once
#include <vector>
#include "openGLDebug.h"

namespace xy

{
    struct VertexBufferElement
    {
        GLid_t glEnumType;
        unsigned int count;
        bool normalised;
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferElement> mElements;
        unsigned int mStride;

    public:
        VertexBufferLayout() : mElements(), mStride(0) {}

        template <typename T>
        void Push(unsigned int count, bool normalised = false);

        inline const std::vector<VertexBufferElement> &GetElements() const { return mElements; }
        inline unsigned int GetStride() const { return mStride; }
    };
}