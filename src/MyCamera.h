/*
 *
 * File:        src/MyCamera.h
 * Author:      TNTErick
 * Created:     2024-01-30
 * Modified:    2024-01-30
 * Description: The MyCamera handles input and ViewMatrix.
 *
 */

#pragma once
#include <glm/glm.hpp>
class MyCamera
{
private:
    glm::vec3 mPosition;

public:
    MyCamera();
    glm::mat4 GetViewMatrix() const;
};