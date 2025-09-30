#include "core.hpp" // IWYU pragma: keep
#include "vertex_array.hpp"

const std::filesystem::path pathToProject =
    "/home/dakeypunchar/documents/cpp-projects/wrapgl";

int main() {
  GLFW::initialize();
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

  const glm::vec4 clearColor = glm::vec4(0.2f, 0.5f, 0.8f, 1.0f);
  while (!window.shouldClose()) {
    window.clear(clearColor);

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }

    GL::Renderer::drawArrays(va, redShaderProgram, GL::RenderMode::TRIANGLES, 0,
                             3);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
