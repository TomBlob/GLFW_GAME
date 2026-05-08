#pragma once
#include "scenes/scene.h"
#include <vector>
#include <memory>
#include <iostream>

class Mesh;
class SceneObject;
class Input;

class GameScene : public Scene {
public:
    GameScene();
    ~GameScene() override;

    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) override;
    void render(const glm::mat4& view,
        const glm::mat4& projection) override;

    void setSharedResources(Mesh* tri, Mesh* sq, Mesh* cube, Mesh* edges, const Shader* shader, const Shader* gridShader);
    void setupSceneObjects();
    SceneObject* addGameObject(Mesh* mesh, const glm::vec3& position,
        const glm::vec3& rotation, const glm::vec3& scale,
        const glm::vec3& color);

private:
    std::vector<std::unique_ptr<SceneObject>> gameObjects;
    std::unique_ptr<SceneObject> floorObject;

    // References to shared resources
    Mesh* meshTriangle;
    Mesh* meshSquare;
    Mesh* meshCube;
    Mesh* meshCubeEdges;
    const Shader* shader;
    const Shader* gridShader;
};