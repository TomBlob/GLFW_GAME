#include "scenes/gamescene.h"

GameScene::GameScene()
    : Scene("GameScene"),
    meshTriangle(nullptr), meshSquare(nullptr),
    meshCube(nullptr), meshCubeEdges(nullptr),
    shader(nullptr), gridShader(nullptr)
{}

GameScene::~GameScene() = default;

void GameScene::onEnter() {
    std::cout << "Entering GameScene\n";
	// removed setupSceneObjects() from here because we need to set shared resources first in main.cpp
}

void GameScene::onExit() {
    std::cout << "Exiting GameScene\n";
    objects.clear();
    floorObject.reset();
}

void GameScene::update(float deltaTime) {
    std::cout << "Physics update: " << physicsObjects.size() << " objects\n";
    if (!physicsSystem) {
        std::cerr << "PhysicsSystem is null!\n";
        return;
    }
    physicsSystem->update(physicsObjects, deltaTime);
}

void GameScene::render(const glm::mat4& view, const glm::mat4& projection) {
    // Render floor
    if (floorObject) {
        // Set shader uniforms for floor
        gridShader->use();
        glm::mat4 model = floorObject->getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniform3fv(glGetUniformLocation(gridShader->ID, "color"), 1, &floorObject->getColor()[0]);
        floorObject->getMesh()->draw();
    }
    // Render game objects
    for (const auto& obj : objects) {
        shader->use();
        glm::mat4 model = obj->getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, &obj->getColor()[0]);
        obj->getMesh()->draw();
	}
}

void GameScene::setSharedResources(Mesh* tri, Mesh* sq, Mesh* cube, Mesh* edges,
                                   const Shader* sh, const Shader* gridSh) {
    meshTriangle = tri;
    meshSquare = sq;
    meshCube = cube;
    meshCubeEdges = edges;
    shader = sh;
    gridShader = gridSh;
}

void GameScene::setupSceneObjects() {
    if (!meshTriangle || !meshSquare || !meshCube) {
        std::cerr << "Error: Shared resources not set before setupSceneObjects\n";
        return;
    }

    // Add triangles
    addGameObject(meshTriangle, glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), ColliderType::Box)->isStatic = true;
    addGameObject(meshTriangle, glm::vec3(-1, 1, -3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), ColliderType::Box)->isStatic = true;

    // Add cubes
    addGameObject(meshCube, glm::vec3(0, -3, -3), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), ColliderType::Box)->isStatic = true;
    addGameObject(meshCube, glm::vec3(2, -2, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), ColliderType::Box)->isStatic = true;
    addGameObject(meshCube, glm::vec3(-2, -1, -4), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), ColliderType::Box)->isStatic = true;

	// Add cube edges
    addGameObject(meshCubeEdges, glm::vec3(0, -3, -3), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0), ColliderType::Box)->isStatic = true;
    addGameObject(meshCubeEdges, glm::vec3(2, -2, -5), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0), ColliderType::Box)->isStatic = true;
	addGameObject(meshCubeEdges, glm::vec3(-2, -1, -4), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0), ColliderType::Box)->isStatic = true;

	// Add floor
    floorObject = std::make_unique<SceneObject>(meshSquare, glm::vec3(0, -3, 0),
                                                glm::vec3(90, 0, 0), glm::vec3(50, 50, 1),
                                                glm::vec3(0.4f, 0.4f, 0.4f), ColliderType::Box);
    floorObject->isStatic = true;
    floorObject->collider->box.halfSize = glm::vec3(25.0f, 0.1f, 25.0f);

	rebuildPhysicsObjects();
}

SceneObject* GameScene::addGameObject(Mesh* mesh, const glm::vec3& position,
                                     const glm::vec3& rotation, const glm::vec3& scale,
                                     const glm::vec3& color, ColliderType colliderType) {
    auto obj = std::make_unique<SceneObject>(mesh, position, rotation, scale, color, colliderType);
    SceneObject* ptr = obj.get();
    objects.push_back(std::move(obj));
    return ptr;
}

void GameScene::registerEntity(Entity* entity) {
	entities.push_back(entity);
	rebuildPhysicsObjects();
}

void GameScene::rebuildPhysicsObjects() {
    physicsObjects.clear();
    physicsObjects.reserve(objects.size() + entities.size() + 1);
    for (auto& obj : objects)  physicsObjects.push_back(obj.get());
    if (floorObject)           physicsObjects.push_back(floorObject.get());
    for (auto* e : entities)   physicsObjects.push_back(e);
}