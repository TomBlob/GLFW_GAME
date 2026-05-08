#pragma once

#include "ecs/entity.h"
#include <glm/glm.hpp>

class Input;
class Camera;

class Player : public Entity {
public:
    Player(const glm::vec3& startPos = glm::vec3(0.0f));

    // Process input and set desired velocity / jump requests
    void handleInput(const Input& input, const Camera& camera, float deltaTime);

    // Physics update (applies gravity, integrates, clamps terminal velocity, ground collision)
    void update(float deltaTime) noexcept override;

    // Configuration
    float moveSpeed;       // horizontal speed (m/s)
    float jumpImpulse;     // initial upward velocity when jumping
    float acceleration;     // horizontal acceleration (m/s²)
    float terminalSpeed;   // downward terminal velocity
};