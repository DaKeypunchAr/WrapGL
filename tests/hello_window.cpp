#include "wrapgl_core.hpp" // IWYU pragma: keep
#include <iostream>

int main() {
  Window window = Window::create(glm::uvec2(200, 200), "Hello Window");
  window.setFrameBufferSizeCallback([](glm::uvec2 dim) {
    std::cout << "Dimensions: " << dim.x << ", " << dim.y << '\n';
  });

  GL::Renderer::setClearColor(glm::vec3(0.1F, 0.2F, 0.25F));
  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }
    window.swapBuffers();
    window.pollEvents();
  }
}
