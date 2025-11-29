#include "wrapgl/renderer.hpp"
#include "wrapgl_core.hpp" // IWYU pragma: keep

const std::filesystem::path pathToProject =
    "/home/dakeypunchar/documents/cpp-projects/wrapgl";

int main() {
  const Window window = Window::create({300, 300}, "Hello Triangle");

  const GL::VertexArray va = GL::VertexArray::create();

  const std::vector<float> vertices = {
      -0.5f, -0.5f, +0.5f, -0.5f, +0.0f, +0.5f,
  };
  const GL::VertexBuffer vb = GL::VertexBuffer::createAndAllocate(vertices);

  const GL::Attribute attrib = GL::Attribute::create(GL::DataType::F32, 2);
  va.setFormat({attrib});
  va.setBufferBindings({GL::Binding::create(vb, 0, 0, sizeof(float) * 2)});

  va.select();

  const GL::ShaderProgram redShaderProgram =
      GL::ShaderProgram::createFromFolder(pathToProject /
                                          "tests/shaders/red-color");
  redShaderProgram.select();

  const glm::vec3 clearColor = glm::vec3(0.2f, 0.5f, 0.8f);
  GL::Renderer::setClearColor(clearColor);

  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }

    GL::Renderer::drawArrays(va, redShaderProgram, GL::RenderMode::TRIANGLES,
                             3);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
