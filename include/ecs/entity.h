#pragma once

#include "physics/collider.h"
#include "ecs/worldobject.h"
#include <glm/glm.hpp>

class Entity : public WorldObject {
public:
    Entity(const glm::vec3& startPos = glm::vec3(0.0f));
    virtual ~Entity() = default;

    void setGroundY(float y) noexcept { groundY = y; }
    float getGroundY() const noexcept { return groundY; }

	void setCollider(Collider* col) noexcept { collider = col; }
	Collider* getCollider() const noexcept { return collider; }

    virtual void update(float deltaTime) noexcept {}

protected:
    // Default ground plane Y (used by simple grounded checks)
    float groundY;
};