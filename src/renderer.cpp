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

constexpr unsigned int glCapability(const GL::Capability mode) {
  switch (mode) {
  case GL::Capability::BLENDING:
    return GL_BLEND;
  }
  throw std::runtime_error("Unknown Capability");
}

constexpr unsigned int glBlendFactor(const GL::BlendFactor f) {
  switch (f) {
  case GL::BlendFactor::ZERO:
    return GL_ZERO;
  case GL::BlendFactor::ONE:
    return GL_ONE;
  case GL::BlendFactor::SOURCE_COLOR:
    return GL_SRC_COLOR;
  case GL::BlendFactor::ONE_MINUS_SOURCE_COLOR:
    return GL_ONE_MINUS_SRC_COLOR;
  case GL::BlendFactor::DESTINATION_COLOR:
    return GL_DST_COLOR;
  case GL::BlendFactor::ONE_MINUS_DESTINATION_COLOR:
    return GL_ONE_MINUS_DST_COLOR;
  case GL::BlendFactor::SOURCE_ALPHA:
    return GL_SRC_ALPHA;
  case GL::BlendFactor::ONE_MINUS_SOURCE_ALPHA:
    return GL_ONE_MINUS_SRC_ALPHA;
  case GL::BlendFactor::DESTINATION_ALPHA:
    return GL_DST_ALPHA;
  case GL::BlendFactor::ONE_MINUS_DESTINATION_ALPHA:
    return GL_ONE_MINUS_DST_ALPHA;
  case GL::BlendFactor::CONSTANT_COLOR:
    return GL_CONSTANT_COLOR;
  case GL::BlendFactor::ONE_MINUS_CONSTANT_COLOR:
    return GL_ONE_MINUS_CONSTANT_COLOR;
  case GL::BlendFactor::CONSTANT_ALPHA:
    return GL_CONSTANT_ALPHA;
  case GL::BlendFactor::ONE_MINUS_CONSTANT_ALPHA:
    return GL_ONE_MINUS_CONSTANT_ALPHA;
  case GL::BlendFactor::SOURCE_ALPHA_SATURATE:
    return GL_SRC_ALPHA_SATURATE;
  }
  throw std::runtime_error("Unknown Blend Factor");
}

constexpr unsigned int glBlendOperator(const GL::BlendOperator op) {
  switch (op) {
  case GL::BlendOperator::ADD:
    return GL_FUNC_ADD;
  case GL::BlendOperator::SUBTRACT:
    return GL_FUNC_SUBTRACT;
  case GL::BlendOperator::REVERSE_SUBTRACT:
    return GL_FUNC_REVERSE_SUBTRACT;
  case GL::BlendOperator::MIN:
    return GL_MIN;
  case GL::BlendOperator::MAX:
    return GL_MAX;
  }
  throw std::runtime_error("Unknown Blend Operator");
}

void GL::Renderer::setClearColor(const glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void GL::Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }

void GL::Renderer::enableCapability(const Capability cap) {
  glEnable(glCapability(cap));
}

void GL::Renderer::disableCapability(const Capability cap) {
  glDisable(glCapability(cap));
}

void GL::Renderer::setBlendColor(const glm::vec4 color) {
  glBlendColor(color.r, color.g, color.b, color.a);
}

void GL::Renderer::setBlendFactors(const BlendFactor sFactor,
                                   const BlendFactor dFactor) {
  glBlendFunc(glBlendFactor(sFactor), glBlendFactor(dFactor));
}

void GL::Renderer::setBlendEquation(const BlendOperator op) {
  glBlendEquation(glBlendOperator(op));
}

void GL::Renderer::drawArrays(const VertexArray &va,
                              const ShaderProgram &shader,
                              const RenderMode mode,
                              const unsigned int firstVertex,
                              const unsigned int verticesCount) {
  va.select();
  shader.select();
  glDrawArrays(glMode(mode), firstVertex, verticesCount);
}
