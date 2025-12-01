#include "wrapgl_core.hpp"              // IWYU pragma: keep
#include <glm/gtc/matrix_transform.hpp> // IWYU pragma: keep

int main() {
  const Window window = Window::create({300, 300}, "Hello Triangle");

  const GL::VertexArray va = GL::VertexArray::create();

  float size = (window.getCurrentWidth() + window.getCurrentHeight()) / 5.0F;
  glm::vec2 mid = glm::vec2(window.getCurrentDimension()) / 2.0F;
  const std::vector<float> vertices = {
      mid.x - size, mid.y - 0.34f * size, // P1
      mid.x + size, mid.y - 0.34f * size, // P2
      mid.x,        mid.y + 0.66f * size, // P3
  };
  const GL::VertexBuffer vb = GL::VertexBuffer::createAndAllocate(vertices);

  const GL::Attribute attrib = GL::Attribute::create(GL::DataType::F32, 2);
  va.setFormat({attrib});
  va.setBufferBindings({GL::Binding::create(vb, 0, 0, sizeof(float) * 2)});

  const GL::ShaderProgram program = GL::ShaderProgram::createSolidColorShader();
  window.setFrameBufferSizeCallback([&program, &vb](glm::uvec2 dimension) {
    program.setUniform("uProjection",
                       glm::ortho(0.0F, static_cast<float>(dimension.x), 0.0F,
                                  static_cast<float>(dimension.y)));

    glm::vec2 mid = glm::vec2(dimension) / 2.0F;
    float size = (dimension.x + dimension.y) / 5.0F;
    const std::vector<float> vertices = {
        mid.x - size, mid.y - 0.34f * size, // P1
        mid.x + size, mid.y - 0.34f * size, // P2
        mid.x,        mid.y + 0.66f * size, // P3
    };
    vb.update(vertices);
  });
  program.setUniform("uColor", glm::vec4(1.0F, 0.2F, 0.1F, 1.0F));
  va.select();

  GL::Renderer::setClearColor(glm::vec3(0.1F, 0.2F, 0.25F));
  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }

    GL::Renderer::drawArrays(GL::RenderMode::TRIANGLES, 3);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
