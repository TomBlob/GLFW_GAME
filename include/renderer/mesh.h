#pragma once
#include <vector>

class Mesh {
public:
    unsigned int VAO, VBO;
    int vertexCount;

    Mesh(const std::vector<float>& vertices);
    ~Mesh();

	// copying is not allowed
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

	// but moving is fine
    Mesh(Mesh&&) = default;
    Mesh& operator=(Mesh&&) = default;

    void draw() const;
};