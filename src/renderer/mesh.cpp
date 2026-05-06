#include "renderer/Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<float>& vertices, GLenum mode) : drawMode(mode) {
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