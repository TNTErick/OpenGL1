/*
 *
 * File:        src/shaders.h
 * Author:      TNTErick
 * Created:     2023-11-16
 * Modified:    2023-11-25
 * Description: This file implements the shaders that the program needs.
 *
 */

#pragma once
#ifndef __XY_SHADER_H__
#define __XY_SHADER_H__

#include <GL/glew.h>
#include <wx/glcanvas.h>
#include <glm/glm.hpp>
// #include <glm/ext.hpp>
#include "openGLDebug.h"

GLid_t getGLShadingProgram();

#endif