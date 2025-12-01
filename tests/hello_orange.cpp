#include "wrapgl_core.hpp" // IWYU pragma: keep
#include <glm/ext/matrix_clip_space.hpp>

int main() {
  const Window window = Window::create({300, 300}, "Hello Orange");
  const GL::VertexArray va = GL::VertexArray::create();

  STB::setFlipVerticallyOnLoad(true);
  GL::Texture2D orange = GL::Texture2D::loadFromFile(
      "/home/dakeypunchar/documents/cpp-projects/wrapgl/tests/orange.png");

  constexpr float size = 1.5F;
  const std::vector<float> vertices = {
      (window.getCurrentWidth() - orange.getWidth() * size) / 2.0F,
      (window.getCurrentHeight() - orange.getHeight() * size) / 2.0F, // P1
      (window.getCurrentWidth() + orange.getWidth() * size) / 2.0F,
      (window.getCurrentHeight() - orange.getHeight() * size) / 2.0F, // P2
      (window.getCurrentWidth() - orange.getWidth() * size) / 2.0F,
      (window.getCurrentHeight() + orange.getHeight() * size) / 2.0F, // P3
      (window.getCurrentWidth() + orange.getWidth() * size) / 2.0F,
      (window.getCurrentHeight() + orange.getHeight() * size) / 2.0F, // P4
  };

  const std::vector<float> texCoords = {
      0.0f, 0.0f, // P1
      1.0f, 0.0f, // P2
      0.0f, 1.0f, // P3
      1.0f, 1.0f, // P4
  };

  const GL::VertexBuffer posBuffer =
      GL::VertexBuffer::createAndAllocate(vertices);

  const GL::VertexBuffer texCoordBuffer =
      GL::VertexBuffer::createAndAllocate(texCoords);

  const GL::Attribute posAttrib =
      GL::Attribute::create(GL::DataType::F32, 2, 0);
  const GL::Attribute texCoordAttrib =
      GL::Attribute::create(GL::DataType::F32, 2, 1);

  va.setFormat({posAttrib, texCoordAttrib});
  va.setBufferBindings(
      {GL::Binding::create(posBuffer, 0, 0, sizeof(float) * 2),
       GL::Binding::create(texCoordBuffer, 1, 0, sizeof(float) * 2)});

  const GL::ShaderProgram textureProgram =
      GL::ShaderProgram::createTextureShader();

  glm::uvec2 orange_dim = orange.getDimension();
  window.setFrameBufferSizeCallback(
      [&textureProgram, orange_dim, &posBuffer](glm::uvec2 dimension) {
        const std::vector<float> vertices = {
            (dimension.x - orange_dim.x * size) / 2.0F,
            (dimension.y - orange_dim.y * size) / 2.0F, // P1
            (dimension.x + orange_dim.x * size) / 2.0F,
            (dimension.y - orange_dim.y * size) / 2.0F, // P2
            (dimension.x - orange_dim.x * size) / 2.0F,
            (dimension.y + orange_dim.y * size) / 2.0F, // P3
            (dimension.x + orange_dim.x * size) / 2.0F,
            (dimension.y + orange_dim.y * size) / 2.0F, // P4
        };
        posBuffer.update(vertices);
        textureProgram.setUniform(
            "uProjection", glm::ortho(0.0F, static_cast<float>(dimension.x),
                                      0.0F, static_cast<float>(dimension.y)));
      });
  orange.generateMipmaps();
  orange.bind(0);
  va.select();
  textureProgram.setUniform("uTexture", 0);

  GL::Renderer::setClearColor(glm::vec3(0.1F, 0.2F, 0.25F));
  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }

    GL::Renderer::drawArrays(GL::RenderMode::TRIANGLE_STRIP, 4);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
