#ifndef WRAPGL_RENDERER_HPP
#define WRAPGL_RENDERER_HPP
#include "wrapgl/data_types.hpp"
#include <glm/glm.hpp>

namespace GL {

enum class RenderMode {
  TRIANGLES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
};

enum class Capability { BLENDING };

enum class BlendFactor {
  ZERO,
  ONE,
  SOURCE_COLOR,
  ONE_MINUS_SOURCE_COLOR,
  DESTINATION_COLOR,
  ONE_MINUS_DESTINATION_COLOR,
  SOURCE_ALPHA,
  ONE_MINUS_SOURCE_ALPHA,
  DESTINATION_ALPHA,
  ONE_MINUS_DESTINATION_ALPHA,
  CONSTANT_COLOR,
  ONE_MINUS_CONSTANT_COLOR,
  CONSTANT_ALPHA,
  ONE_MINUS_CONSTANT_ALPHA,
  SOURCE_ALPHA_SATURATE
};

enum class BlendOperator { ADD, SUBTRACT, REVERSE_SUBTRACT, MIN, MAX };

struct Renderer {
  static void setClearColor(const glm::vec4 color);
  inline static void setClearColor(const glm::vec3 color) {
    setClearColor(glm::vec4(color.r, color.g, color.b, 1.0F));
  }
  static void clear();

  static void enableCapability(const Capability cap);
  static void disableCapability(const Capability cap);

  static void setBlendColor(const glm::vec4 color);
  static void setBlendFactors(const BlendFactor sfactor,
                              const BlendFactor dfactor);
  static void setBlendEquation(const BlendOperator op);

  static void drawArrays(const RenderMode mode,
                         const unsigned int verticesCount,
                         const unsigned int firstVertexIndex = 0);

  static void drawElements(const RenderMode mode,
                           const unsigned int elementCount,
                           const unsigned int offset = 0,
                           const GL::DataType elementType = GL::DataType::U8);

}; // namespace Renderer

} // namespace GL

#endif
