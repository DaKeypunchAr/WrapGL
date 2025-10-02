#ifndef WRAPGL_RENDERER_HPP
#define WRAPGL_RENDERER_HPP
#include "shader_program.hpp"
#include "vertex_array.hpp"

namespace GL {

enum class RenderMode {
  TRIANGLES,
  TRIANGLE_STRIP,
};

namespace Renderer {

void drawArrays(const VertexArray &va, const ShaderProgram &shader,
                const RenderMode mode, const unsigned int firstVertexIndex,
                const unsigned int verticesCount);

} // namespace Renderer
} // namespace GL

#endif
