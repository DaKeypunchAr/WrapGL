#include "core.hpp"
#include <GLFW/glfw3.h>
int main() {
  GLFW::initialize();
  Window demoWindow = Window::create(glm::uvec2(600, 800), "Blue window...");
  demoWindow.select();

  glm::vec4 windowColor = glm::vec4(0.2f, 0.5f, 0.8f, 1.0f);
  while (!demoWindow.shouldClose()) {
    demoWindow.clear(windowColor);

    if (demoWindow.isKeyPressed(GLFW_KEY_ESCAPE)) {
      demoWindow.triggerClose();
    }
    demoWindow.swapBuffers();
    demoWindow.pollEvents();
  }
}
