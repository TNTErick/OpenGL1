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
#include <wx/wx.h>

enum class MoveDirection : char
{
    INVALID,
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class MyCamera
{
private:
    glm::vec3 mPosition;
    //glm::vec3 mFrontDirection;
    glm::vec2 mPitch7Yaw;

    inline static const glm::vec3 absoluteUpDirection{0.f, 1.f, 0.f};
    inline static const float mSpeed = .1f;
    inline static const float mTurnSpeed = .01f;
public:
    MyCamera();
    glm::mat4 GetViewMatrix(float) const;
    void OnMovement(MoveDirection);
    const glm::vec3 GetFrontDirection() const;
    void LookAt(glm::vec3 targetPosition);

    // yaw, -pitch
    void OnTurn(const wxPoint &UpRight);
};