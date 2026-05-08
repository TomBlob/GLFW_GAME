#include "scenes/scene.h"
#include "rendering/camera.h"

Scene::Scene(const std::string& name)
    : name(name), camera(std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f))) {
}

const std::string& Scene::getName() const {
    return name;
}

Camera* Scene::getCamera() {
    return camera.get();
}

const Camera* Scene::getCamera() const {
    return camera.get();
}