#include "scenes/sceneobject.h"
#include "rendering/mesh.h"
#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(Mesh* mesh, const glm::vec3& position,
    const glm::vec3& rotation, const glm::vec3& scale,
    const glm::vec3& color)
    : mesh(mesh), position(position), rotation(rotation), scale(scale), color(color) {
}

Mesh* SceneObject::getMesh() const {
    return mesh;
}

const glm::vec3& SceneObject::getPosition() const {
    return position;
}

const glm::vec3& SceneObject::getRotation() const {
    return rotation;
}

const glm::vec3& SceneObject::getScale() const {
    return scale;
}

const glm::vec3& SceneObject::getColor() const {
    return color;
}

void SceneObject::setPosition(const glm::vec3& pos) {
    position = pos;
}

void SceneObject::setRotation(const glm::vec3& rot) {
    rotation = rot;
}

void SceneObject::setScale(const glm::vec3& scl) {
    scale = scl;
}

void SceneObject::setColor(const glm::vec3& col) {
    color = col;
}

glm::mat4 SceneObject::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}