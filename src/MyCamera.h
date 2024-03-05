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

enum class MoveDirection : char
{
    INVALID,
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class MyCamera
{
private:
    glm::vec3 mPosition, mRearDirection;
    // glm::vec3 mAbsoluteFrontDirection;
    inline static const glm::vec3 absoluteUpDirection{0.f, 1.f, 0.f};
    float mSpeed;

public:
    MyCamera();
    glm::mat4 GetViewMatrix(float) const;
    void OnMovement(MoveDirection);
    void LookAt(glm::vec3 targetPosition);
};