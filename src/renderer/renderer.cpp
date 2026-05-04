#include "renderer/renderer.h"
#include <glad/glad.h>

void Renderer::clear(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}