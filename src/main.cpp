#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/Camera.h"
#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = 400, lastY = 300;
bool firstMouse = true;

float aspect = 1500.0f / 1000.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool keys[1024];

struct Object {
    Mesh* mesh;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 color;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glm::mat4 buildModelMatrix(const Object& obj) {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, obj.position);

    model = glm::rotate(model, glm::radians(obj.rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(obj.rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(obj.rotation.z), glm::vec3(0, 0, 1));

    model = glm::scale(model, obj.scale);

    return model;
}

int main() {
    std::cout << "Starting game...\n";

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

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::cout << "Window created\n";

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cout << "GLAD initialized\n";

    // Debug: print OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";


	// -------------------------------------------------------


    // Triangle data
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

    std::vector<float> cube = {
        // back face
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,

        // front face
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,-0.5f, 0.5f,

        // left face
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,

        // right face
        0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,

        // bottom face
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,

        // top face
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f
    };

    std::vector<float> cubeEdges = {
        // bottom square
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,

        // top square
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f,

        // vertical lines
        -0.5f,-0.5f,-0.5f, -0.5f, 0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f
    };

    // -------------------------------------------------------



    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    Mesh mesh_triangle(triangle);
	Mesh mesh_square(square);
	Mesh mesh_cube(cube);
    Mesh mesh_cube_edges(cubeEdges, GL_LINES);

    std::vector<Object> triangles = {
    { &mesh_triangle, {0,0,-2}, {0,0,0}, {1,1,1}, {1,0,0} }, // red
    { &mesh_triangle, {2,0,-5}, {0,0,0}, {1,1,1}, {0,1,0} }, // green
    { &mesh_triangle, {-1,1,-3}, {0,0,0}, {1,1,1}, {0,0,1} } // blue
    };

    std::vector<Object> cubes = {
    { &mesh_cube, {0,0,-3}, {0,0,0}, {1,1,1}, {1,0,0} },
    { &mesh_cube, {2,0,-5}, {0,0,0}, {1,1,1}, {0,1,0} },
    { &mesh_cube, {-2,0,-4}, {0,0,0}, {1,1,1}, {0,0,1} }
    };

	Object floor = { &mesh_square, {0,-3,0}, {90,0,0}, {50,50,1}, {0.4f, 0.4f, 0.4f} };

    std::cout << "Buffers ready\n";

    // Load shaders from files
    Shader shader("shaders/basic.vert", "shaders/basic.frag");
    Shader gridShader("shaders/basic.vert", "shaders/grid.frag");

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    int colorLoc = glGetUniformLocation(shader.ID, "color");

    std::cout << "Shader loaded\n";

    Renderer renderer;

	// cache uniform locations
    shader.use();
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    int projLoc = glGetUniformLocation(shader.ID, "projection");

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processKeyboard(keys, deltaTime);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), aspect, 0.1f, 100.0f);

        renderer.clear(0.1f, 0.1f, 0.1f);

        int gridModelLoc = glGetUniformLocation(gridShader.ID, "model");
        int gridViewLoc = glGetUniformLocation(gridShader.ID, "view");
        int gridProjLoc = glGetUniformLocation(gridShader.ID, "projection");

        gridShader.use();

        glUniformMatrix4fv(gridViewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(gridProjLoc, 1, GL_FALSE, &projection[0][0]);

        glm::mat4 model = buildModelMatrix(floor);
        glUniformMatrix4fv(gridModelLoc, 1, GL_FALSE, &model[0][0]);
        floor.mesh->draw();

        shader.use();

		// set view and projection matrices once per frame
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

        for (auto& triangle : triangles) {
            
            glm::mat4 model = buildModelMatrix(triangle);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            glUniform3fv(colorLoc, 1, &triangle.color[0]);
            triangle.mesh->draw();
        }
        
        for (auto& cube : cubes) {
            
            glm::mat4 model = buildModelMatrix(cube);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            glUniform3fv(colorLoc, 1, &cube.color[0]);
            cube.mesh->draw();

            glLineWidth(2.0f);
            glUniform3f(colorLoc, 0.05f, 0.05f, 0.05f);
            mesh_cube_edges.draw();
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    std::cout << "Program closed cleanly\n";

    return 0;
}