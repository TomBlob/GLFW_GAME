#include "ecs/entity.h"

namespace {
    constexpr float DEFAULT_GRAVITY = -9.81f;
}

Entity::Entity(const glm::vec3& startPos)
    : position(startPos),
      velocity(0.0f),
      gravityScale(1.0f),
      flying(false),
      groundY(-2.5f)
{
}

void Entity::update(float /*deltaTime*/) noexcept {
    // Base Entity does nothing. Derived classes (Player, Enemy) implement physics/logic.
}