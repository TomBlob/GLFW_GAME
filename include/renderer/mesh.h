#pragma once
#include <vector>
#include <glad/glad.h>

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
};