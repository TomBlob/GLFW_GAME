#include "scenes/menu.h"

MenuScene::MenuScene() : Scene("MenuScene") {}

MenuScene::~MenuScene() = default;

void MenuScene::onEnter() {
    std::cout << "Entering MenuScene\n";
}

void MenuScene::onExit() {
    std::cout << "Exiting MenuScene\n";
}

void MenuScene::update(float deltaTime) {
    // Update menu logic
}

void MenuScene::render(const glm::mat4& view, const glm::mat4& projection) {
    // Render menu
}