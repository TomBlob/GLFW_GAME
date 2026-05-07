#pragma once
# include <glfw/glfw3.h>

class Input {
public:
	Input();
	~Input();

    // Keyboard input
    void updateKeyState(int key, int action);
    bool isKeyPressed(int key) const;

    // Mouse input
    void updateMousePosition(double xpos, double ypos);
    float getMouseDeltaX();
    float getMouseDeltaY();

    void resetMouseFirstFrame();

private:
    bool keys[1024];
    double lastMouseX;
    double lastMouseY;
    float mouseDeltaX;
    float mouseDeltaY;
    bool firstMouseFrame;
};

