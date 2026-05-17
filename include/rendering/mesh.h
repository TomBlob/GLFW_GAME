#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Mesh {
    unsigned int VAO = 0, VBO = 0;
	unsigned int vertexCount = 0;
    GLenum drawMode;

public:
    Mesh(const std::vector<float>& vertices, GLenum mode = GL_TRIANGLES);
    ~Mesh();

	// copying is not allowed
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

	// but moving is fine
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;

    const glm::vec3& getMinBounds() const;
    const glm::vec3& getMaxBounds() const;
    glm::vec3 getHalfSize() const;

    glm::vec3 minBounds;
    glm::vec3 maxBounds;
    glm::vec3 size;
};