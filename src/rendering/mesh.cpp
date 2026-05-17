#include "rendering/mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<float>& vertices, GLenum mode) : drawMode(mode) {
    minBounds = glm::vec3(vertices[0], vertices[1], vertices[2]);
    maxBounds = minBounds;

    for (size_t i = 0; i < vertices.size(); i += 3) {
        glm::vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

        minBounds.x = std::min(minBounds.x, v.x);
        minBounds.y = std::min(minBounds.y, v.y);
        minBounds.z = std::min(minBounds.z, v.z);

        maxBounds.x = std::max(maxBounds.x, v.x);
        maxBounds.y = std::max(maxBounds.y, v.y);
        maxBounds.z = std::max(maxBounds.z, v.z);
    }

    size = maxBounds - minBounds;

    vertexCount = vertices.size() / 3;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

Mesh::Mesh(Mesh&& other) noexcept {
    VAO = other.VAO;
    VBO = other.VBO;
    drawMode = other.drawMode;

    other.VAO = 0;
    other.VBO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        VAO = other.VAO;
        VBO = other.VBO;
        drawMode = other.drawMode;

        other.VAO = 0;
        other.VBO = 0;
    }
    return *this;
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(drawMode, 0, vertexCount);
}

const glm::vec3& Mesh::getMinBounds() const {
	return minBounds;
}

const glm::vec3& Mesh::getMaxBounds() const {
    return maxBounds;
}

glm::vec3 Mesh::getHalfSize() const {
    return size * 0.5f;
}