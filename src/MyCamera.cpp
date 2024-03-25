/*
 *
 * File:        src/MyCamera.cpp
 * Author:      TNTErick
 * Created:     2024-01-30
 * Modified:    2024-03-15
 * Description: The MyCamera handles input and ViewMatrix.
 *
 */

#include "MyCamera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <wx/wx.h>
#include "xy/openGLDebug.h"

MyCamera::MyCamera()
    : mPosition(-3.f, 0.f, 0.5f),
      mPitch7Yaw(0.f, 0.f)
{
}

glm::mat4 MyCamera::GetViewMatrix(float screenRatio) const
{

    return glm::perspective(glm::radians(80.0f), screenRatio, 0.f, 100.f) * glm::lookAt(mPosition, mPosition + GetFrontDirection(), glm::normalize(glm::cross(-GetFrontDirection(), glm::cross(GetFrontDirection(), absoluteUpDirection))));
}

void MyCamera::OnMovement(MoveDirection dxn)
{
    glm::vec3 direction{0.f}, frontDirection{GetFrontDirection()};
    frontDirection.y = 0.;
    frontDirection = glm::normalize(frontDirection);
    switch (dxn)
    {
    case MoveDirection::FRONT:
        direction = frontDirection;
        break;
    case MoveDirection::BACK:
        direction = frontDirection;
        break;
        break;
    case MoveDirection::LEFT:
        direction = glm::cross(absoluteUpDirection, frontDirection);
        break;
    case MoveDirection::RIGHT:
        direction = glm::cross(frontDirection, absoluteUpDirection);
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

const glm::vec3 MyCamera::GetFrontDirection() const
{
    glm::vec3 newCameraFront;
    newCameraFront.x = cos(mPitch7Yaw.y) * cos(mPitch7Yaw.x);
    newCameraFront.y = sin(mPitch7Yaw.x);
    newCameraFront.z = sin(mPitch7Yaw.y) * cos(mPitch7Yaw.x);
    return newCameraFront;
}

void MyCamera::LookAt(glm::vec3 targetPosition)
{
    // calculate the Pitch-Yaw and retarget.
}

void MyCamera::OnTurn(const wxPoint &upRight)
{
    mPitch7Yaw.x += upRight.x * mTurnSpeed;
    mPitch7Yaw.y += upRight.y * mTurnSpeed;

    mPitch7Yaw.y = glm::mod(mPitch7Yaw.y, static_cast<float>(xy::TAU));
    if (mPitch7Yaw.x >= xy::TE)
        mPitch7Yaw.x = xy::TE;
    if(mPitch7Yaw.x<=-xy::TE)
        mPitch7Yaw.x = -xy::TE;
}