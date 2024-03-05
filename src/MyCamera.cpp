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

MyCamera::MyCamera()
    : mPosition(0.f, 0.f, -3.0f),
      mRearDirection(0.f, 0.f, -1.0f),
      mSpeed(0.05f)
{
}

glm::mat4 MyCamera::GetViewMatrix(float screenRatio) const
{
    return glm::perspective(glm::radians(45.0f), screenRatio, 0.1f, 100.f) * glm::translate(glm::mat4(1.0f), mPosition);
}

void MyCamera::OnMovement(MoveDirection dxn)
{
    glm::vec3 direction{0.f},
        front = -mRearDirection; // glm::normalize(glm::vec3(-mRearDirection.x, 0, -mRearDirection.z));
    switch (dxn)

    {
    case MoveDirection::FRONT:
        direction = front;
        break;
    case MoveDirection::BACK:
        direction = mRearDirection;
        break;
        break;
    case MoveDirection::LEFT:
        direction = glm::cross(absoluteUpDirection, front);
        break;
    case MoveDirection::RIGHT:
        direction = glm::cross(absoluteUpDirection, -front);
        break;
    case MoveDirection::UP:
        direction = absoluteUpDirection;
        break;
    case MoveDirection::DOWN:
        direction = -absoluteUpDirection;
        break;
    }

    mPosition += direction * mSpeed;
}

void MyCamera::LookAt(glm::vec3 targetPosition)
{
    mRearDirection = glm::normalize(targetPosition - mPosition);
}
