#include "wrapgl/vertex_array.hpp"
#include "glad/glad.h"
#include "wrapgl/vertex_buffer.hpp"

GL::VertexArray::VertexArray(const unsigned int rawId)
    : m_VertexArrayId(rawId) {}

GL::VertexArray GL::VertexArray::create() {
  unsigned int rawId;
  glCreateVertexArrays(1, &rawId);
  return VertexArray(rawId);
}

GL::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_VertexArrayId); }

void GL::VertexArray::select() const { glBindVertexArray(m_VertexArrayId); }

constexpr unsigned int glType(const GL::DataType type) {
  switch (type) {
  case GL::DataType::F32:
    return GL_FLOAT;
  }
}

constexpr unsigned int glBool(const bool b) { return b ? GL_TRUE : GL_FALSE; }

void GL::VertexArray::setFormat(
    const std::vector<GL::Attribute> &attributes) const {
  unsigned int attribIndex = 0;
  for (std::size_t i = 0; i < attributes.size(); i++) {
    auto &attribute = attributes.at(i);
    glEnableVertexArrayAttrib(m_VertexArrayId, attribIndex);
    glVertexArrayAttribBinding(m_VertexArrayId, attribIndex,
                               attribute.bindingIndex);
    glVertexArrayAttribFormat(
        m_VertexArrayId, attribIndex, attribute.count, glType(attribute.type),
        glBool(attribute.isNormalized), attribute.relativeOffset);
    attribIndex++;
  }
}

void GL::VertexArray::setBufferBindings(
    const std::vector<Binding> &bindings) const {
  for (std::size_t i = 0; i < bindings.size(); i++) {
    auto &binding = bindings.at(i);
    glVertexArrayVertexBuffer(m_VertexArrayId, binding.getBindingIndex(),
                              binding.getBufferId(), binding.getOffset(),
                              binding.getStride());
  }
}
