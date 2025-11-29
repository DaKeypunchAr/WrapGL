#include "wrapgl/vertex_buffer.hpp"
#include "wrapgl_core.hpp" // IWYU pragma: keep

void updateBufferForNGon(std::vector<float> &buffer, const unsigned int n,
                         float initialAngle = 0.0F);
std::vector<float> getBufferForNGon(const unsigned int n,
                                    float initialAngle = 0.0F);

std::vector<float> getBufferForNGon(const unsigned int n, float initialAngle) {
  std::vector<float> buffer;
  updateBufferForNGon(buffer, n, initialAngle);
  return buffer;
}

int main() {
  Window win = Window::create(glm::uvec2(500, 500), "POLYGONS");

  GL::ShaderProgram program = GL::ShaderProgram::createFromFolder(

      "/home/dakeypunchar/documents/cpp-projects/wrapgl/tests/shaders/"
      "red-color/");

  GL::VertexArray va = GL::VertexArray::create();
  va.setFormat({GL::Attribute::create(GL::DataType::F32, 2)});

  GL::VertexBuffer vb = GL::VertexBuffer::createAndAllocate(
      getBufferForNGon(3), GL::BufferUpdateFrequency::STREAM);
  va.setBufferBindings({GL::Binding::create(vb, 0, 0, sizeof(float) * 2)});

  float initialAngle = 0.0F;
  unsigned int n = 3;
  char step = 1;

  GL::Renderer::setClearColor(glm::vec3(0.1, 0.2, 0.25));
  while (!win.shouldClose()) {
    GL::Renderer::clear();

    if (win.isKeyPressed(Key::Escape)) {
      win.triggerClose();
    }

    GL::Renderer::drawArrays(va, program, GL::RenderMode::TRIANGLE_FAN, n + 2);

    initialAngle += 1.0F;
    vb.update(getBufferForNGon(n, glm::radians(initialAngle)));

    if (initialAngle >= 360.0F / static_cast<float>(n)) {
      initialAngle = 0.0F;
      n += step;
      vb.allocateBuffer(sizeof(float) * 2 * (n + 2),
                        GL::BufferUpdateFrequency::STREAM);

      if (n == 15)
        step = -1;
      else if (n == 3)
        step = 1;
    }

    win.swapBuffers();
    Window::pollEvents();
  }
}

void updateBufferForNGon(std::vector<float> &buffer, unsigned int n,
                         float initialAngle) {
  buffer.resize(2 * (n + 2));
  buffer[0] = 0.0F;
  buffer[1] = 0.0F;

  const float ANGLE_DIFF = glm::radians(360.0F) / static_cast<float>(n);
  float angle = initialAngle;
  for (unsigned int i = 0; i < n + 1; i++, angle += ANGLE_DIFF) {
    glm::vec2 pos = glm::vec2(glm::cos(angle), glm::sin(angle));
    buffer[2 * i + 2] = pos.x;
    buffer[2 * i + 3] = pos.y;
  }
}
