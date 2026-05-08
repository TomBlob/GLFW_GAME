#pragma once
#include "scenes/scene.h"
#include <iostream>

class MenuScene : public Scene {
public:
    MenuScene();
    ~MenuScene() override;

    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) override;
    void render(const glm::mat4& view, const glm::mat4& projection) override;
};
