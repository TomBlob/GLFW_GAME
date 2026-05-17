#include "scenes/scenemanager.h"
#include <iostream>

SceneManager::SceneManager() : currentScene(nullptr) {}

SceneManager::~SceneManager() = default;

void SceneManager::loadScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it == scenes.end()) {
        std::cout << "Scene '" << name << "' not found\n";
        return;
    }

    if (currentScene) {
        currentScene->onExit();
    }

    currentScene = it->second.get();
    currentScene->onEnter();
    std::cout << "Loaded scene: " << name << "\n";
}

Scene* SceneManager::getCurrentScene() {
    return currentScene;
}

const Scene* SceneManager::getCurrentScene() const {
    return currentScene;
}

void SceneManager::setPhysicsSystem(PhysicsSystem* physicsSystem) {
    // Pass the physics system to all registered scenes that need it
    for (auto& pair : scenes) {
        Scene* scene = pair.second.get();
        scene->setPhysicsSystem(physicsSystem);
	}
}
