#include "core.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main() {
  GLFW::initialize();
  Window window = Window::create({1000, 700}, "Hello Triangle");

  GL::VertexArray va = GL::VertexArray::create();

  std::vector<float> vertices = {
      -0.5f, -0.5f, +0.5f, -0.5f, +0.0f, +0.5f,
  };
  GL::VertexBuffer vb = GL::VertexBuffer::create();

  GL::Attribute attrib;
  attrib.bindingIndex = 0;
  attrib.relativeOffset = 0;
  attrib.type = GL::DataType::F32;
  attrib.count = 2;
  attrib.isNormalized = false;
  va.setFormat({attrib});
  va.setBufferBindings({GL::Binding::create(vb, 0, 0, sizeof(float) * 2)});

  vb.update(vertices);

  va.select();

  const char *vsSourceCstr = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
      gl_Position = vec4(aPos, 0.0, 1.0);
    }
  )";

  const char *fsSourceCstr = R"(
    #version 330 core
    out vec4 color;
    void main() {
      color = vec4(0.8, 0.5, 0.2, 1.0);
    }
  )";

  GL::ShaderProgram redShaderProgram =
      GL::ShaderProgram::createFromSource(vsSourceCstr, fsSourceCstr);
  redShaderProgram.select();

  glm::vec4 clearColor = glm::vec4(0.2f, 0.5f, 0.8f, 1.0f);
  while (!window.shouldClose()) {
    window.clear(clearColor);

    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
      window.triggerClose();
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
