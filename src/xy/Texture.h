/*
 *
 * File:        src/xy/Texture.h
 * Author:      TNTErick
 * Created:     2023-12-29
 * Modified:    2023-12-30
 * Description: `Texture` is a class managing textures.
 *
 */

#pragma once
#include "openGLDebug.h"
#include <string>

namespace xy
{
    class Texture
    {
    private:
        GLid_t mID;
        wxString mFilePath;
        wxImage *mpImage;
        wxSize mSize;

    public:
        Texture();
        Texture(const char *filename);
        ~Texture();

        void Init(const char *filename);
        void Bind(GLid_t slot = 0) const;
        void Unbind() const;

        inline bool IsValid() const { return mpImage != nullptr; }
        inline wxSize GetDimension() const { return mpImage ? mpImage->GetSize() : wxSize(0, 0); }
        inline const unsigned int GetPixelDepth() const { return mpImage ? 32 : 0; }
    };
}