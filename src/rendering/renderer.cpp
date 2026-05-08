#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "scenes/sceneobject.h"
#include "rendering/mesh.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

Renderer::Renderer() : modelLoc(-1), colorLoc(-1), viewLoc(-1), projLoc(-1) {}

Renderer::~Renderer() = default;

void Renderer::init(const Shader& shader) {
    shader.use();
    modelLoc = glGetUniformLocation(shader.ID, "model");
    colorLoc = glGetUniformLocation(shader.ID, "color");
    viewLoc = glGetUniformLocation(shader.ID, "view");
    projLoc = glGetUniformLocation(shader.ID, "projection");
}

void Renderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderObject(const SceneObject* obj, const glm::mat4& view,
                            const glm::mat4& projection) {
    glm::mat4 model = obj->getModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glUniform3fv(colorLoc, 1, &obj->getColor()[0]);
    obj->getMesh()->draw();
}

void Renderer::renderFloor(SceneObject* floor, const Shader& gridShader, 
                           const glm::mat4& view, const glm::mat4& projection) {
    gridShader.use();
    
    int gridModelLoc = glGetUniformLocation(gridShader.ID, "model");
    int gridViewLoc = glGetUniformLocation(gridShader.ID, "view");
    int gridProjLoc = glGetUniformLocation(gridShader.ID, "projection");

    glUniformMatrix4fv(gridViewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(gridProjLoc, 1, GL_FALSE, &projection[0][0]);

    glm::mat4 model = floor->getModelMatrix();
    glUniformMatrix4fv(gridModelLoc, 1, GL_FALSE, &model[0][0]);
    floor->getMesh()->draw();
}