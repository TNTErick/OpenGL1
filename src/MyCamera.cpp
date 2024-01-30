/*
 *
 * File:        src/MyCamera.cpp
 * Author:      TNTErick
 * Created:     2024-01-30
 * Modified:    2024-01-30
 * Description: The MyCamera handles input and ViewMatrix.
 *
 */

#include "MyCamera.h"
#include "glm/gtc/matrix_transform.hpp"

MyCamera::MyCamera() : mPosition(glm::vec3(0.f))
{
}

glm::mat4 MyCamera::GetViewMatrix() const
{
    return glm::translate(glm::mat4(1.0f), -mPosition);
}