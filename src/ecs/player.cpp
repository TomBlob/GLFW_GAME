#include "ecs/player.h"
#include "core/input.h"
#include "rendering/camera.h"
#include <glm/gtc/constants.hpp>

namespace {
    constexpr float DEFAULT_GRAVITY = -9.81f;
    constexpr float FRICTION = 0.92f;        // Slide longer before stopping
    constexpr float VERTICAL_FRICTION = 0.95f; // Slightly more damping for flying vertical
}

Player::Player(const glm::vec3& startPos)
    : Entity(startPos),
      moveSpeed(4.0f),
      acceleration(15.0f),
      jumpImpulse(5.0f),
      terminalSpeed(50.0f)
{
    collider = new Collider();
	collider->type = ColliderType::Box;
	collider->box.halfSize = glm::vec3(0.3f, 0.75f, 0.3f);
}

void Player::handleInput(const Input& input, const Camera& camera, float deltaTime) {
    // Camera-relative horizontal movement flattened to XZ
    glm::vec3 flatFront = glm::vec3(camera.getFront().x, 0.0f, camera.getFront().z);
    if (glm::length(flatFront) > 0.0f) flatFront = glm::normalize(flatFront);
    glm::vec3 flatRight = glm::vec3(camera.getRight().x, 0.0f, camera.getRight().z);
    if (glm::length(flatRight) > 0.0f) flatRight = glm::normalize(flatRight);

    glm::vec3 horizontalDir(0.0f);
    if (input.isKeyPressed(GLFW_KEY_W)) horizontalDir += flatFront;
    if (input.isKeyPressed(GLFW_KEY_S)) horizontalDir -= flatFront;
    if (input.isKeyPressed(GLFW_KEY_A)) horizontalDir -= flatRight;
    if (input.isKeyPressed(GLFW_KEY_D)) horizontalDir += flatRight;

    float currentSpeed = moveSpeed;
    if (input.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) currentSpeed *= 1.8f;

    if (glm::length(horizontalDir) > 0.0f) {
        horizontalDir = glm::normalize(horizontalDir);
        glm::vec3 desiredVel(horizontalDir.x * currentSpeed, velocity.y, horizontalDir.z * currentSpeed);
        glm::vec3 accelDir = glm::normalize(desiredVel - velocity);
        velocity += accelDir * acceleration * deltaTime;

        glm::vec3 horizVel(velocity.x, 0.0f, velocity.z);
        if (glm::length(horizVel) > currentSpeed) {
            horizVel = glm::normalize(horizVel) * currentSpeed;
            velocity.x = horizVel.x;
            velocity.z = horizVel.z;
        }
    }
    else {
        velocity.x *= FRICTION;
        velocity.z *= FRICTION;
    }

    if (flying) {
        // Fly mode: Space = up, Ctrl = down, no gravity
        float verticalDir = 0.0f;
        if (input.isKeyPressed(GLFW_KEY_SPACE))        verticalDir = 1.0f;
        else if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) verticalDir = -1.0f;

        if (verticalDir != 0.0f) {
            velocity.y += verticalDir * acceleration * deltaTime;
            velocity.y = glm::clamp(velocity.y, -moveSpeed, moveSpeed);
        }
        else {
            velocity.y *= VERTICAL_FRICTION;
        }
    }
    else {
        // Normal mode: jump only when grounded, physics handles gravity
        if (input.isKeyPressed(GLFW_KEY_SPACE) && isGrounded) {
            velocity.y = jumpImpulse;
        }
    }
}

void Player::update(float deltaTime) noexcept {
   
}