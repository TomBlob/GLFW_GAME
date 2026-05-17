#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendering/camera.h"
#include "rendering/shader.h"
#include "rendering/renderer.h"
#include "rendering/mesh.h"

#include "core/input.h"

#include "scenes/scene.h"
#include "scenes/sceneobject.h"
#include "scenes/scenemanager.h"
#include "scenes/gamescene.h"
#include "scenes/menu.h"

#include "physics/physics_system.h"

#include "ecs/player.h"

#include <iostream>

Camera* g_camera = nullptr;
Input* g_input = nullptr;
SceneManager* g_sceneManager = nullptr;

// callback functions
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (g_input) {
        g_input->updateKeyState(key, action);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (g_input && g_camera) {
        g_input->updateMousePosition(xpos, ypos);
        g_camera->processMouse(g_input->getMouseDeltaX(), g_input->getMouseDeltaY());
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


std::vector<float> createCubeVertices() {
    return {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f
    };
}

std::vector<float> createCubeEdges() {
    return {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f, 0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f
    };
}

int main() {
    std::cout << "Starting game...\n";

    Input input;
    g_input = &input;

    SceneManager sceneManager;
    g_sceneManager = &sceneManager;

    float aspect = 1500.0f / 1000.0f;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Init GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(1500, 1000, "test", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    // Register callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    std::cout << "Window created\n";

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cout << "GLAD initialized\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    // -------------------------------------------------------
    // MESH DATA
    // -------------------------------------------------------

    std::vector<float> triangle = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    std::vector<float> square = {
        // first triangle
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,

        // second triangle
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };


    // -------------------------------------------------------
    // CREATE MESHES
    // -------------------------------------------------------

    Mesh mesh_triangle(triangle);
    Mesh mesh_square(square);
    Mesh mesh_cube(createCubeVertices());
    Mesh mesh_cube_edges(createCubeEdges(), GL_LINES);

    std::cout << "Buffers created\n";

    // Load shaders from files
    Shader shader("shaders/basic.vert", "shaders/basic.frag");
    Shader gridShader("shaders/basic.vert", "shaders/grid.frag");

    std::cout << "Shaders loaded\n";

    Renderer renderer;
    renderer.init(shader);

    // Register and load scene
    sceneManager.registerScene<GameScene>("game");
    sceneManager.loadScene("game");

    Scene* currentScene = sceneManager.getCurrentScene();
    if (!currentScene) {
        std::cout << "Failed to load game scene\n";
        glfwTerminate();
        return -1;
    }

    g_camera = currentScene->getCamera();

	PhysicsSystem physicsSystem;
    sceneManager.setPhysicsSystem(&physicsSystem);


    // -------------------------------------------------------
    // ADD PLAYER
    // -------------------------------------------------------

    // create near top (after g_camera assigned)
    Player player(g_camera->position);   // start camera/player at same place
    player.setGroundY(-2.5f);            // match your floor y
	//player.flying = true;              // enable gravity for player

    // Cast to GameScene and set shared resources
    GameScene* gameScene = dynamic_cast<GameScene*>(currentScene);
    if (gameScene) {
        gameScene->setSharedResources(&mesh_triangle, &mesh_square, &mesh_cube,
            &mesh_cube_edges, &shader, &gridShader);
    }

    // Setup scene objects (supposed to be in onEnter, but we need to set shared resources first)
    gameScene->setupSceneObjects();

    // Cache uniform locations for main shader
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    int projLoc = glGetUniformLocation(shader.ID, "projection");
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    int colorLoc = glGetUniformLocation(shader.ID, "color");

    shader.use();

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input only — no update() call here anymore
        player.handleInput(input, *g_camera, deltaTime);

        // Build combined physics list: player + all scene statics
        std::vector<WorldObject*> physicsObjects = gameScene->getPhysicsObjects();
        physicsObjects.push_back(&player);

        // Physics owns gravity, integration, and collision resolution
        physicsSystem.update(physicsObjects, deltaTime);

        // Camera follows player's resolved position
        g_camera->position = player.position;
        g_camera->update(deltaTime);

        glm::mat4 view = g_camera->getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(g_camera->fov), aspect, 0.1f, 100.0f);

        renderer.clear(0.1f, 0.1f, 0.1f);

        currentScene->update(deltaTime);
        currentScene->render(view, projection);

        glfwSwapBuffers(window);
    }

    // Cleanup
    g_input = nullptr;
    g_camera = nullptr;
    g_sceneManager = nullptr;

    glfwTerminate();
    std::cout << "Program closed cleanly\n";

    return 0;
}