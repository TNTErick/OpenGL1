/*
 *
 * File:        src/xy/IndexBuffer.h
 * Author:      TNTErick
 * Created:     2023-12-20
 * Modified:    2023-12-26
 * Description: This is the class wrapper for Element Array Buffer.
 *
 */

#pragma once
#include "openGLDebug.h"

namespace xy
{
    namespace generic
    {
        class IndexBuffer
        {
        protected:
            GLid_t mID;
            size_t mCount;

        public:
            virtual GLenum getGLenumType() const = 0;
            void Bind() const;
            void Unbind() const;

            inline const bool IsValid() const { return mID != 0; }
            inline const size_t getSize() const { return mCount; }
        };
    }
    
    template <typename T = unsigned int>
    class IndexBuffer : public generic::IndexBuffer
    {
    public:
        typedef T data_t;

        IndexBuffer();
        IndexBuffer(const data_t *data, size_t count);
        ~IndexBuffer();

        GLenum getGLenumType() const;
        void operator=(const IndexBuffer<data_t> &) = delete;
        void operator=(IndexBuffer<data_t> &&) = delete;

        void Init(const data_t *data, size_t count);
    };
} //
