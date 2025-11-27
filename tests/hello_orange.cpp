#include "wrapgl/renderer.hpp"
#include "wrapgl_core.hpp" // IWYU pragma: keep

const std::filesystem::path pathToProject =
    "/home/dakeypunchar/documents/cpp-projects/wrapgl";
int main() {
  const Window window = Window::create({300, 300}, "Hello Orange");
  const GL::VertexArray va = GL::VertexArray::create();

  const std::vector<float> vertices = {
      -0.5f, -0.5f, // P1
      +0.5f, -0.5f, // P2
      -0.5f, +0.5f, // P3
      +0.5f, +0.5f, // P4
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

  va.select();

  STB::setFlipVerticallyOnLoad(true);
  const GL::ShaderProgram textureProgram = GL::ShaderProgram::createFromFolder(
      pathToProject / "tests/shaders/texture");
  textureProgram.select();

  GL::Texture2D orange = GL::Texture2D::loadFromFile(
      "/home/dakeypunchar/documents/cpp-projects/wrapgl/tests/orange.png");
  orange.generateMipmaps();
  orange.bind(0);
  textureProgram.setUniform("tex", 0);

  const glm::vec3 clearColor = glm::vec3(0.2f, 0.5f, 0.8f);
  GL::Renderer::setClearColor(clearColor);
  while (!window.shouldClose()) {
    GL::Renderer::clear();

    if (window.isKeyPressed(Key::Escape)) {
      window.triggerClose();
    }

    orange.bind(0);
    GL::Renderer::drawArrays(va, textureProgram, GL::RenderMode::TRIANGLE_STRIP,
                             0, 4);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
