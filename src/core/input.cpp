#include "core/input.h"

Input::Input()
    : lastMouseX(0.0),
      lastMouseY(0.0),
      mouseDeltaX(0.0f),
      mouseDeltaY(0.0f),
      firstMouseFrame(true) {
    keys.fill(false);
}

Input::~Input() = default;

void Input::updateKeyState(int key, int action) noexcept {
    if (key >= 0 && key < static_cast<int>(keys.size())) {
        // Treat GLFW_REPEAT as a pressed state so holding a key keeps it active.
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            keys[static_cast<size_t>(key)] = true;
        } else if (action == GLFW_RELEASE) {
            keys[static_cast<size_t>(key)] = false;
        }
    }
}

bool Input::isKeyPressed(int key) const noexcept {
    if (key < 0 || key >= static_cast<int>(keys.size())) return false;
    return keys[static_cast<size_t>(key)];
}

void Input::updateMousePosition(double xpos, double ypos) noexcept {
    if (firstMouseFrame) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouseFrame = false;
        mouseDeltaX = 0.0f;
        mouseDeltaY = 0.0f;
        return;
    }

    mouseDeltaX = static_cast<float>(xpos - lastMouseX);
    mouseDeltaY = static_cast<float>(lastMouseY - ypos);

    lastMouseX = xpos;
    lastMouseY = ypos;
}

float Input::getMouseDeltaX() const noexcept {
    return mouseDeltaX;
}

float Input::getMouseDeltaY() const noexcept {
    return mouseDeltaY;
}

void Input::resetMouseFirstFrame() noexcept {
    firstMouseFrame = true;
}