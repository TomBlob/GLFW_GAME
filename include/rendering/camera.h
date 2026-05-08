#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

class Camera {
public:
    Camera(glm::vec3 startPos);

    glm::mat4 getViewMatrix() const;

    void processKeyboard(bool* keys, float deltaTime);
    void processMouse(float xoffset, float yoffset);
    void update(float deltaTime);

    // Public properties
    glm::vec3 position;
    float yaw;
    float pitch;
    float fov;

    // Configuration
    float mouseAcceleration = 12.0f;
    float mouseDamping = 15.0f;
    float maxSpeed = 4.0f;
    float shiftModif = 1.8f;
    float sensitivity = 0.08f;

private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float yawVelocity = 0.0f;
    float pitchVelocity = 0.0f;

    static constexpr float PITCH_MAX = 89.0f;
    static constexpr float PITCH_MIN = -89.0f;

    void updateVectors();
    void clampPitch();
};