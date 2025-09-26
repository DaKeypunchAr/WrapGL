#include "core.hpp"
#include <GLFW/glfw3.h>
int main() {
  GLFW::initialize();
  Window window = Window::create(glm::uvec2(600, 800), "Hello Window");

  glm::vec4 windowColor = glm::vec4(0.2f, 0.5f, 0.8f, 1.0f);
  while (!window.shouldClose()) {
    window.clear(windowColor);

    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
      window.triggerClose();
    }
    window.swapBuffers();
    window.pollEvents();
  }
}
