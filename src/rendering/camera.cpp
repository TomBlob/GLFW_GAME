#include "rendering/camera.h"
#include "core/input.h" // implementation needs Input

Camera::Camera(glm::vec3 startPos)
    : position(startPos),
      yaw(-90.0f),
      pitch(0.0f),
      fov(45.0f),
      front(glm::vec3(0.0f, 0.0f, -1.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f))
{
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::clampPitch() {
    if (pitch > PITCH_MAX) pitch = PITCH_MAX;
    if (pitch < PITCH_MIN) pitch = PITCH_MIN;
}

void Camera::processKeyboard(bool* keys, float deltaTime) {
    // existing compatibility path: convert bool* to the Input-like checks
    glm::vec3 inputDir(0.0f);

    const glm::vec3 WORLD_FORWARD(0.0f, 0.0f, -1.0f);
    const glm::vec3 WORLD_RIGHT(1.0f, 0.0f, 0.0f);
    const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

    if (keys[GLFW_KEY_W]) inputDir += WORLD_FORWARD;
    if (keys[GLFW_KEY_S]) inputDir -= WORLD_FORWARD;
    if (keys[GLFW_KEY_A]) inputDir -= WORLD_RIGHT;
    if (keys[GLFW_KEY_D]) inputDir += WORLD_RIGHT;
    if (keys[GLFW_KEY_SPACE]) inputDir += WORLD_UP;
    if (keys[GLFW_KEY_LEFT_CONTROL]) inputDir -= WORLD_UP;

    if (glm::length(inputDir) > 0.0f) {
        inputDir = glm::normalize(inputDir);
        const float currentSpeed = maxSpeed * (keys[GLFW_KEY_LEFT_SHIFT] ? shiftModif : 1.0f);
        position += inputDir * currentSpeed * deltaTime;
    }
}

void Camera::processKeyboard(const Input& input, float deltaTime) {
    // Camera-relative horizontal movement:
    // - forward/back use camera forward but flattened to world XZ (y = 0)
    // - right/left use camera right but flattened to world XZ (y = 0)
    // - space/ctrl move strictly along world Y
    glm::vec3 inputDir(0.0f);

    const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);

    // flatten front and right to remove vertical component introduced by pitch
    glm::vec3 flatFront = glm::vec3(front.x, 0.0f, front.z);
    if (glm::length(flatFront) > 0.0f) flatFront = glm::normalize(flatFront);

    glm::vec3 flatRight = glm::vec3(right.x, 0.0f, right.z);
    if (glm::length(flatRight) > 0.0f) flatRight = glm::normalize(flatRight);

    if (input.isKeyPressed(GLFW_KEY_W)) inputDir += flatFront;
    if (input.isKeyPressed(GLFW_KEY_S)) inputDir -= flatFront;
    if (input.isKeyPressed(GLFW_KEY_A)) inputDir -= flatRight;
    if (input.isKeyPressed(GLFW_KEY_D)) inputDir += flatRight;
    if (input.isKeyPressed(GLFW_KEY_SPACE)) inputDir += WORLD_UP;
    if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) inputDir -= WORLD_UP;

    if (glm::length(inputDir) > 0.0f) {
        inputDir = glm::normalize(inputDir);
        const float currentSpeed = maxSpeed * (input.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? shiftModif : 1.0f);
        position += inputDir * currentSpeed * deltaTime;
    }
}

void Camera::processMouse(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yawVelocity += xoffset * mouseAcceleration;
    pitchVelocity += yoffset * mouseAcceleration;

    clampPitch();
    updateVectors();
}

void Camera::update(float deltaTime)
{
    yaw += yawVelocity * deltaTime;
    pitch += pitchVelocity * deltaTime;

    // simple damping
    yawVelocity -= yawVelocity * mouseDamping * deltaTime;
    pitchVelocity -= pitchVelocity * mouseDamping * deltaTime;

    clampPitch();
    updateVectors();
}

void Camera::updateVectors() {
    const float cy = glm::cos(glm::radians(yaw));
    const float sy = glm::sin(glm::radians(yaw));
    const float cp = glm::cos(glm::radians(pitch));
    const float sp = glm::sin(glm::radians(pitch));

    glm::vec3 direction;
    direction.x = cy * cp;
    direction.y = sp;
    direction.z = sy * cp;

    front = glm::normalize(direction);

    // compute orthonormal basis using world up (0,1,0)
    const glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}