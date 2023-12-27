/*
 *
 * File:        src/xy/Renderer.h
 * Author:      TNTErick
 * Created:     2023-12-21
 * Modified:    2023-12-26
 * Description: This class is responsible for call drawings to openGL, so that
 *              the code in `MyGLCanvas` can be clean.
 */

#pragma once
#include "openGLDebug.h"
#include <GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace xy
{
    class Renderer
    {
    private:
    public:
        void Draw(const VertexArray &va, generic::IndexBuffer const &indices, const Shader &shader) const;
    };
}