#pragma once
#include "ecs/worldobject.h"
#include <glm/glm.hpp>

class Mesh;

class SceneObject : public WorldObject {
public:
    SceneObject(Mesh* mesh,
        const glm::vec3& position,
        const glm::vec3& rotation,
        const glm::vec3& scale,
        const glm::vec3& color);

    Mesh* getMesh() const;
    const glm::vec3& getColor() const;

    void setColor(const glm::vec3& col);

private:
    Mesh* mesh;
    glm::vec3 color;
};