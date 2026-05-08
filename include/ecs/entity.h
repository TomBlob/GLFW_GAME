#pragma once

#include <glm/glm.hpp>

class Entity {
public:
    Entity(const glm::vec3& startPos = glm::vec3(0.0f));
    virtual ~Entity() = default;

    // Per-frame update (physics / logic). Override in derived classes.
    virtual void update(float deltaTime) noexcept;

    // World-space state
    glm::vec3 position;
    glm::vec3 velocity;

    // Per-entity gravity multiplier (1.0 = normal gravity)
    float gravityScale;

    // If true the entity ignores gravity and can move freely (flying)
    bool flying;

    void setGroundY(float y) noexcept { groundY = y; }
    float getGroundY() const noexcept { return groundY; }

protected:
    // Default ground plane Y (used by simple grounded checks)
    float groundY;
};