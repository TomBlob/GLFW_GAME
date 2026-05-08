#pragma once
#include <memory>
#include <string>

#include "rendering/mesh.h"
#include "rendering/shader.h"
#include "scenes/sceneobject.h"


#include "rendering/camera.h"

class Camera;
class Scene {
public:
    Scene(const std::string& name);
    virtual ~Scene() = default;

    const std::string& getName() const;

    virtual void onEnter() = 0;    // Called when scene becomes active
    virtual void onExit() = 0;     // Called when scene becomes inactive
    virtual void update(float deltaTime) = 0;
    virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;

    Camera* getCamera();
    const Camera* getCamera() const;

protected:
    std::string name;
    std::unique_ptr<Camera> camera;
};