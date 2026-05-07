#include "renderer/Camera.h"
#include <glm/gtc/constants.hpp>

Camera::Camera(glm::vec3 startPos)
    : position(startPos),
    yaw(-90.0f),
	mouseAcceleration(8.0f),
    friction(1.0f),
    pitch(0.0f),
    maxSpeed(4.0f),
    sensitivity(0.06f),
    fov(45.0f),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(bool* keys, float deltaTime) {
    glm::vec3 inputDir(0.0f);

    if (keys[GLFW_KEY_W]) inputDir += front;
    if (keys[GLFW_KEY_S]) inputDir -= front;
    if (keys[GLFW_KEY_A]) inputDir -= right;
    if (keys[GLFW_KEY_D]) inputDir += right;
    if (keys[GLFW_KEY_SPACE]) inputDir += up;
    if (keys[GLFW_KEY_LEFT_CONTROL]) inputDir -= up;

    if (glm::length(inputDir) > 0.0f)
        inputDir = glm::normalize(inputDir);

    float currentSpeed = maxSpeed;

    if (keys[GLFW_KEY_LEFT_SHIFT])
        currentSpeed *= shiftModif; // sprint

    position += inputDir * currentSpeed * deltaTime;
}

void Camera::processMouse(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yawVelocity += xoffset * mouseAcceleration;
    pitchVelocity += yoffset * mouseAcceleration;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

void Camera::update(float deltaTime)
{
    yaw += yawVelocity * deltaTime;
    pitch += pitchVelocity * deltaTime;

    yawVelocity -= yawVelocity * mouseDamping * deltaTime;
    pitchVelocity -= pitchVelocity * mouseDamping * deltaTime;

    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}