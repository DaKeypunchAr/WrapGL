#ifndef WRAPGL_RENDERER_HPP
#define WRAPGL_RENDERER_HPP
#include "shader_program.hpp"
#include "vertex_array.hpp"
#include <glm/glm.hpp>

namespace GL {

enum class RenderMode {
  TRIANGLES,
  TRIANGLE_STRIP,
};

struct Renderer {
  static void setClearColor(const glm::vec4 color);
  inline static void setClearColor(const glm::vec3 color) {
    setClearColor(glm::vec4(color.r, color.g, color.b, 1.0F));
  }
  static void clear();

  static void drawArrays(const VertexArray &va, const ShaderProgram &shader,
                         const RenderMode mode,
                         const unsigned int firstVertexIndex,
                         const unsigned int verticesCount);

}; // namespace Renderer

} // namespace GL

#endif
