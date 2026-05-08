#pragma once
#include <glfw/glfw3.h>
#include <array>

class Input {
public:
    Input();
    ~Input();

    // Keyboard input
    void updateKeyState(int key, int action) noexcept;
    bool isKeyPressed(int key) const noexcept;

    // Mouse input
    void updateMousePosition(double xpos, double ypos) noexcept;
    float getMouseDeltaX() const noexcept;
    float getMouseDeltaY() const noexcept;

    void resetMouseFirstFrame() noexcept;

private:
    std::array<bool, 1024> keys;
    double lastMouseX;
    double lastMouseY;
    float mouseDeltaX;
    float mouseDeltaY;
    bool firstMouseFrame;
};

