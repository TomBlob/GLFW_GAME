#include "scenes/sceneobject.h"
#include "rendering/mesh.h"

SceneObject::SceneObject(Mesh* mesh,
    const glm::vec3& position,
    const glm::vec3& rotation,
    const glm::vec3& scale,
    const glm::vec3& color)
    : WorldObject(position, rotation, scale),
    mesh(mesh),
    color(color)
{
}

Mesh* SceneObject::getMesh() const {
    return mesh;
}

const glm::vec3& SceneObject::getColor() const {
    return color;
}

void SceneObject::setColor(const glm::vec3& col) {
    color = col;
}