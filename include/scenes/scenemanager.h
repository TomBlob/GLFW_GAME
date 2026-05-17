#pragma once
#include <memory>
#include <unordered_map>
#include <string>

#include "scenes/scenemanager.h"
#include "scenes/gamescene.h"
#include "physics/physics_system.h"
#include "scenes/scene.h"

class Scene;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    template<typename T>
    void registerScene(const std::string& name) {
        scenes[name] = std::make_unique<T>();
    }

    void loadScene(const std::string& name);
    Scene* getCurrentScene();
    const Scene* getCurrentScene() const;
	void setPhysicsSystem(PhysicsSystem* physicsSystem);

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* currentScene;
};