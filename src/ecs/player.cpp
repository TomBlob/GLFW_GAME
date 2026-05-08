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
}

void Player::handleInput(const Input& input, const Camera& camera, float deltaTime) {
    // Camera-relative horizontal movement but flattened to world XZ plane.
    glm::vec3 flatFront = glm::vec3(camera.getFront().x, 0.0f, camera.getFront().z);
    if (glm::length(flatFront) > 0.0f) flatFront = glm::normalize(flatFront);

    glm::vec3 flatRight = glm::vec3(camera.getRight().x, 0.0f, camera.getRight().z);
    if (glm::length(flatRight) > 0.0f) flatRight = glm::normalize(flatRight);

    glm::vec3 horizontalDir(0.0f);
    if (input.isKeyPressed(GLFW_KEY_W)) horizontalDir += flatFront;
    if (input.isKeyPressed(GLFW_KEY_S)) horizontalDir -= flatFront;
    if (input.isKeyPressed(GLFW_KEY_A)) horizontalDir -= flatRight;
    if (input.isKeyPressed(GLFW_KEY_D)) horizontalDir += flatRight;

    // Apply sprint modifier
    float currentSpeed = moveSpeed;
    if (input.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        currentSpeed *= 1.8f;
    }

    if (glm::length(horizontalDir) > 0.0f) {
        horizontalDir = glm::normalize(horizontalDir);
        // Accelerate towards desired velocity
        glm::vec3 desiredVel(horizontalDir.x * currentSpeed, velocity.y, horizontalDir.z * currentSpeed);
        glm::vec3 accelDir = glm::normalize(desiredVel - velocity);
        velocity += accelDir * acceleration * deltaTime;

        // Clamp to max speed
        glm::vec3 horizVel(velocity.x, 0.0f, velocity.z);
        if (glm::length(horizVel) > currentSpeed) {
            horizVel = glm::normalize(horizVel) * currentSpeed;
            velocity.x = horizVel.x;
            velocity.z = horizVel.z;
        }
    } else {
        // Apply friction when no input (slide to stop)
        velocity.x *= FRICTION;
        velocity.z *= FRICTION;
    }

    // Vertical controls
    if (flying) {
        // Flying mode: space goes up, ctrl goes down (with acceleration)
        float verticalDir = 0.0f;
        if (input.isKeyPressed(GLFW_KEY_SPACE)) verticalDir = 1.0f;
        else if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) verticalDir = -1.0f;

        if (verticalDir != 0.0f) {
            velocity.y += verticalDir * acceleration * deltaTime;
            // Clamp vertical flying speed
            if (velocity.y > moveSpeed) velocity.y = moveSpeed;
            if (velocity.y < -moveSpeed) velocity.y = -moveSpeed;
        } else {
            velocity.y *= VERTICAL_FRICTION;  // Slide when no vertical input
        }
    } else {
        // Grounded mode: space triggers jump when on ground
        bool grounded = position.y <= groundY + 0.001f;
        if (input.isKeyPressed(GLFW_KEY_SPACE) && grounded) {
            velocity.y = jumpImpulse;
        }
        // Gravity will handle downward velocity in update()
    }
}

void Player::update(float deltaTime) noexcept {
    // Apply gravity if not flying
    if (!flying) {
        velocity.y += DEFAULT_GRAVITY * gravityScale * deltaTime;
        // Clamp terminal downward speed
        if (velocity.y < -terminalSpeed) velocity.y = -terminalSpeed;
    }

    // Integrate position
    position += velocity * deltaTime;

    // Simple ground collision: snap to ground and zero vertical velocity
    if (!flying && position.y < groundY) {
        position.y = groundY;
        velocity.y = 0.0f;
    }
}