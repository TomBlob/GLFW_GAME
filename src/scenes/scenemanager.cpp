#include "scenes/scenemanager.h"
#include "scenes/scene.h"
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