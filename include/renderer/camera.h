#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position;

    float yaw;
    float pitch;

    float yawVelocity = 0.0f;
    float pitchVelocity = 0.0f;

    float mouseAcceleration = 12.0f;
    float mouseDamping = 15.0f;
	float friction; //damping factor for velocity
    glm::vec3 velocity = glm::vec3(0.0f);
    float maxSpeed;
	float shiftModif = 1.8f; // speed multiplier when shift is held
    float sensitivity = 0.08f;
    float fov;

    Camera(glm::vec3 startPos);

    glm::mat4 getViewMatrix() const;

    void processKeyboard(bool* keys, float deltaTime);
    void processMouse(float xoffset, float yoffset);

    void update(float deltaTime);

private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    void updateVectors();
};