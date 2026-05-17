#include "ecs/entity.h"

namespace {
    constexpr float DEFAULT_GRAVITY = -9.81f;
}

Entity::Entity(const glm::vec3& startPos)
    : WorldObject(startPos, glm::vec3(0.0f), glm::vec3(1.0f)),
    groundY(-2.5f) 
{}
