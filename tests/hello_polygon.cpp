#include "wrapgl_core.hpp" // IWYU pragma: keep
#include <glm/ext/matrix_clip_space.hpp>

void updateBufferForNGon(std::vector<float> &buffer, const unsigned int n,
                         float initialAngle = 0.0F);
std::vector<float> getBufferForNGon(const unsigned int n,
                                    float initialAngle = 0.0F);

std::vector<float> getBufferForNGon(const unsigned int n, float initialAngle) {
  std::vector<float> buffer;
  updateBufferForNGon(buffer, n, initialAngle);
  return buffer;
}

float size = 1.0F;
int main() {
  Window win = Window::create(glm::uvec2(500, 500), "POLYGONS");

  GL::ShaderProgram program = GL::ShaderProgram::createSolidColorShader();
  GL::VertexArray va = GL::VertexArray::create();
  va.setFormat({GL::Attribute::create(GL::DataType::F32, 2)});

  GL::VertexBuffer vb = GL::VertexBuffer::createAndAllocate(
      getBufferForNGon(3), GL::BufferUpdateFrequency::STREAM);
  va.setBufferBindings({GL::Binding::create(vb, 0, 0, sizeof(float) * 2)});

  float initialAngle = 0.0F;
  unsigned int n = 3;
  char step = 1;
  bool reachedMax = false;

  program.setUniform("uProjection",
                     glm::ortho(0.0F, static_cast<float>(win.getCurrentWidth()),
                                0.0F,
                                static_cast<float>(win.getCurrentHeight())));
  size = std::min(win.getCurrentWidth(), win.getCurrentHeight()) * 0.8F;

  win.setFrameBufferSizeCallback([&program](glm::uvec2 dimension) {
    program.setUniform("uProjection",
                       glm::ortho(0.0F, static_cast<float>(dimension.x), 0.0F,
                                  static_cast<float>(dimension.y)));
    size = std::min(dimension.x, dimension.y) * 0.4F;
  });

  va.select();
  program.setUniform("uColor", glm::vec4(1.0F, 0.2F, 0.1F, 1.0F));
  GL::Renderer::setClearColor(glm::vec3(0.1F, 0.2F, 0.25F));
  while (!win.shouldClose()) {
    GL::Renderer::clear();

    if (win.isKeyPressed(Key::Escape)) {
      win.triggerClose();
    }

    if (initialAngle >= 360.0F / static_cast<float>(n)) {
      initialAngle = 0.0F;
      n += step;

      if (!reachedMax)
        vb.allocateBuffer(sizeof(float) * 2 * (n + 2),
                          GL::BufferUpdateFrequency::STREAM);

      if (n == 15) {
        step = -1;
        reachedMax = true;
      } else if (n == 3)
        step = 1;
    }

    initialAngle += 1.0F;
    vb.update(getBufferForNGon(n, glm::radians(initialAngle)));

    GL::Renderer::drawArrays(GL::RenderMode::TRIANGLE_FAN, n + 2);

    win.swapBuffers();
    Window::pollEvents();
  }
}

void updateBufferForNGon(std::vector<float> &buffer, unsigned int n,
                         float initialAngle) {
  buffer.resize(2 * (n + 2));
  buffer[0] = Window::getActiveWindow()->getCurrentWidth() / 2.0F;
  buffer[1] = Window::getActiveWindow()->getCurrentHeight() / 2.0F;

  const float ANGLE_DIFF = glm::radians(360.0F) / static_cast<float>(n);
  float angle = initialAngle;
  for (unsigned int i = 0; i < n + 1; i++, angle += ANGLE_DIFF) {
    glm::vec2 pos = glm::vec2(glm::cos(angle), glm::sin(angle));
    buffer[2 * i + 2] =
        Window::getActiveWindow()->getCurrentWidth() / 2.0F + pos.x * size;
    buffer[2 * i + 3] =
        Window::getActiveWindow()->getCurrentHeight() / 2.0F + pos.y * size;
  }
}
