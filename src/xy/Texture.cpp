/*
 *
 * File:        src/xy/Texture.cpp
 * Author:      TNTErick
 * Created:     2023-12-29
 * Modified:    2023-12-30
 * Description: `Texture` is a class managing textures.
 *
 */
#include "Texture.h"

xy::Texture::Texture() : mID(0),
                         mFilePath(),
                         mpImage(nullptr),
                         mSize(0, 0)
{
}

xy::Texture::Texture(const char *filename)
{
    Texture();
    Init(filename);
}

void xy::Texture::Init(const char *filename)
{
    // load the png from wxImage; OpenGL loads the texture upside-down.
    wxString filepath = wxGetCwd() + "\\resource\\" + filename;
    mpImage = new wxImage(filepath, wxBITMAP_TYPE_ANY);
    wxImage img = mpImage->Mirror(false);

    if (!img.Ok())
        return;

    if (!img.HasAlpha())
        img.InitAlpha();

    wxASSERT_MSG(img.HasAlpha(), "Fuck you");

    unsigned char
        *rgb = img.GetData(),
        *a = img.GetAlpha(),
        *rgba = new unsigned char[img.GetWidth() * img.GetHeight() * 4];

    for (int iA = 0, iRgb = 0, iRgba = 0; iA < img.GetWidth() * img.GetHeight();)
    {
        rgba[iRgba++] = rgb[iRgb++];
        rgba[iRgba++] = rgb[iRgb++];
        rgba[iRgba++] = rgb[iRgb++];
        rgba[iRgba++] = a[iA++];
    }
    // setting the texture to OpenGL.

    xy_glRun(glGenTextures(1, &mID));
    Bind();
    // texture parameters, I have not looked into it yet but it seems to be critical for rendering.
    xy_glRun(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // horizontal repetition.
    xy_glRun(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // vertical repetition.
    xy_glRun(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));    // minification.
    xy_glRun(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));    // magnification.

    //                           target, level,  internal format, width, height,                      border, format,             type,            pixels
    xy_glRun(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GetDimension().GetWidth(), GetDimension().GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba));

    // xy_glRun(glGenerateMipmap(GL_TEXTURE_2D));
    Unbind();
    // we can
}

xy::Texture::~Texture()
{
    if (!IsValid())
        return;
    xy_glRun(glDeleteTextures(1, &mID));
    delete mpImage;
    mpImage = nullptr;
}

void xy::Texture::Bind(int slot) const
{
    // int i;
    // xy_glRun(glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &i));
    //
    // if (slot >= i)
    //     wxLogWarning("xy::Texture::Bind failed. slot (%d) is larger than maximum allowed (%d).", slot, i);
    // else
    //     wxLogDebug("slot (%d) is in the range of maximum allowed (%d).", slot, i);

    xy_glRun(glActiveTexture(GL_TEXTURE0 + slot)); // if it is not consecutive fuck it.
    xy_glRun(glBindTexture(GL_TEXTURE_2D, mID));
}

void xy::Texture::Unbind() const
{
    xy_glRun(glBindTexture(GL_TEXTURE_2D, 0));
}