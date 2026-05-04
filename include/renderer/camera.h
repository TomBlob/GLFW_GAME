#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position;

    float yaw;
    float pitch;

    float speed;
    float sensitivity;
    float fov;

    Camera(glm::vec3 startPos);

    glm::mat4 getViewMatrix() const;

    void processKeyboard(bool* keys, float deltaTime);
    void processMouse(float xoffset, float yoffset);

private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    void updateVectors();
};