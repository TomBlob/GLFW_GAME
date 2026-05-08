#pragma once
#include <glm/glm.hpp>

class Shader;
class SceneObject;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init(const Shader& shader);
    void clear(float r, float g, float b);
    void renderObject(const SceneObject* obj, const glm::mat4& view, const glm::mat4& projection);
    void renderFloor(SceneObject* floor, const Shader& gridShader, 
                     const glm::mat4& view, const glm::mat4& projection);

private:
    int modelLoc;
    int colorLoc;
    int viewLoc;
    int projLoc;
};