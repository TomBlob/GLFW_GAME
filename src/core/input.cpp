#include "core/input.h"

Input::Input() : lastMouseX(0.0), lastMouseY(0.0), mouseDeltaX(0.0f), mouseDeltaY(0.0f), firstMouseFrame(true) {
    for (int i = 0; i < 1024; ++i) {
        keys[i] = false;
    }
}

Input::~Input() = default;

void Input::updateKeyState(int key, int action) {
    if (key >= 0 && key < 1024) {
        // Treat GLFW_REPEAT as a pressed state so holding a key keeps it active.
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

bool Input::isKeyPressed(int key) const {
    if (key < 0 || key >= 1024) return false;
    return keys[key];
}

void Input::updateMousePosition(double xpos, double ypos) {
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

float Input::getMouseDeltaX() {
    return mouseDeltaX;
}

float Input::getMouseDeltaY() {
    return mouseDeltaY;
}

void Input::resetMouseFirstFrame() {
    firstMouseFrame = true;
}