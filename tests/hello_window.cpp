#include "wrapgl_core.hpp" // IWYU pragma: keep

int main() {
  GLFW::initialize();
  Window window = Window::create(glm::uvec2(200, 200), "Hello Window");

  glm::vec4 windowColor = glm::vec4(0.2f, 0.5f, 0.8f, 1.0f);
  while (!window.shouldClose()) {
    window.clear(windowColor);

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }
    window.swapBuffers();
    window.pollEvents();
  }
}
