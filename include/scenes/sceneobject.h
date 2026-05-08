#pragma once
#include <glm/glm.hpp>

class Mesh;

class SceneObject {
public:
    SceneObject(Mesh* mesh, const glm::vec3& position, const glm::vec3& rotation,
        const glm::vec3& scale, const glm::vec3& color);

    // Getters
    Mesh* getMesh() const;
    const glm::vec3& getPosition() const;
    const glm::vec3& getRotation() const;
    const glm::vec3& getScale() const;
    const glm::vec3& getColor() const;

    // Setters
    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);
    void setColor(const glm::vec3& color);

    // Transform utilities
    glm::mat4 getModelMatrix() const;

private:
    Mesh* mesh;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 color;
};