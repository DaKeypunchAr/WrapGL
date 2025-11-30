#include "wrapgl_core.hpp" // IWYU pragma: keep
#include <iostream>

int main() {
  Window window = Window::create(glm::uvec2(200, 200), "Hello Window");
  window.setFrameBufferSizeCallback([](glm::uvec2 dim) {
    std::cout << "Dimensions: " << dim.x << ", " << dim.y << '\n';
  });

  const glm::vec3 windowColor = glm::vec3(0.2f, 0.5f, 0.8f);
  GL::Renderer::setClearColor(windowColor);

  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }
    window.swapBuffers();
    window.pollEvents();
  }
}
