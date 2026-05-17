#pragma once

#include <glm/glm.hpp>

enum class ColliderType {
    None,
    Box,
    Sphere
};

struct Box {
    glm::vec3 halfSize;
};

struct Sphere {
    float radius;
};

class Collider {
public:
    bool enabled = true;

    ColliderType type = ColliderType::None;

    Box box;
    Sphere sphere;
};