/*
 *
 * File:        src/xy/VertexBufferLayout.h
 * Author:      TNTErick
 * Created:     2023-12-21
 * Modified:    2023-12-21
 * Description: This class is used in VertexArray to represent a layout for a vertex buffer.
 *
 */

#include <GL/glew.h>
#include "VertexBufferLayout.h"

template <typename T>
void xy::VertexBufferLayout::Push(unsigned int count, bool normalised) { static_assert(false); }

template <>
void xy::VertexBufferLayout::Push<float>(unsigned int count, bool normalised)
{
    mElements.push_back({GL_FLOAT, count, normalised});
}
// TODO: implement different types of Push that is defined in glEnumType.