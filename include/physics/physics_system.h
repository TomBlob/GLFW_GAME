#pragma once

#include "ecs/entity.h"
#include "scenes/sceneobject.h"
#include <vector>

class PhysicsSystem {
public:
    void update(std::vector<WorldObject*>& entities, float dt);

private:
    void resolveCollision(WorldObject& a, WorldObject& b);
    bool checkBox(const WorldObject& a, const WorldObject& b);
};