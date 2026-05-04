#include "renderer/Camera.h"
#include <glm/gtc/constants.hpp>

Camera::Camera(glm::vec3 startPos)
    : position(startPos),
    yaw(-90.0f),
    pitch(0.0f),
    speed(3.0f),
    sensitivity(0.1f),
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
    float velocity = speed * deltaTime;

    if (keys[GLFW_KEY_W]) position += front * velocity;
    if (keys[GLFW_KEY_S]) position -= front * velocity;
    if (keys[GLFW_KEY_A]) position -= right * velocity;
    if (keys[GLFW_KEY_D]) position += right * velocity;
}

void Camera::processMouse(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

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