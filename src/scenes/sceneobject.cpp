#include "scenes/sceneobject.h"
#include "rendering/mesh.h"

SceneObject::SceneObject(Mesh* mesh, const glm::vec3& position,
    const glm::vec3& rotation, const glm::vec3& scale,
    const glm::vec3& color, ColliderType colliderType)
    : WorldObject(position, rotation, scale), mesh(mesh), color(color)
{
    if (colliderType != ColliderType::None) {
        collider = new Collider();
        collider->type = colliderType;
        collider->box.halfSize = scale * 0.5f;
    }
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