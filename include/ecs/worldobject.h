#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "physics/collider.h"

class Mesh;

class WorldObject {
public:
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{ 1.0f };

    Collider* collider = nullptr;

    bool isStatic = false;

    glm::vec3 velocity{ 0.0f };
    float gravityScale = 1.0f;
    bool flying = false;

    WorldObject(const glm::vec3& pos,
        const glm::vec3& rot,
        const glm::vec3& scl)
        : position(pos), rotation(rot), scale(scl) {
    }

    Collider* getCollider() const { return collider; }

    virtual ~WorldObject() = default;

    glm::mat4 getModelMatrix() const {
        glm::mat4 model(1.0f);

        model = glm::translate(model, position);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        model = glm::scale(model, scale);

        return model;
    }
};