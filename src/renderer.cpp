#include "wrapgl/renderer.hpp"
#include "glad/glad.h"

constexpr unsigned int glMode(const GL::RenderMode mode) {
  switch (mode) {
  case GL::RenderMode::TRIANGLES:
    return GL_TRIANGLES;
  case GL::RenderMode::TRIANGLE_STRIP:
    return GL_TRIANGLE_STRIP;
  }
  throw std::runtime_error("Unknown Mode");
}

void GL::Renderer::setClearColor(const glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void GL::Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void GL::Renderer::drawArrays(const VertexArray &va,
                              const ShaderProgram &shader,
                              const RenderMode mode,
                              const unsigned int firstVertex,
                              const unsigned int verticesCount) {
  va.select();
  shader.select();
  glDrawArrays(glMode(mode), firstVertex, verticesCount);
}
