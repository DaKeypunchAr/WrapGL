#include "vertex_buffer.hpp"
#include "glad/glad.h"

GL::VertexBuffer::VertexBuffer(unsigned int rawId) : m_VertexBufferId(rawId) {}

GL::VertexBuffer GL::VertexBuffer::create() {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  return GL::VertexBuffer(rawId);
}

GL::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferId); }

constexpr unsigned int glHintFromEnums(GL::BufferFrequencyHint f,
                                       GL::BufferAccessNatureHint a) {
  switch (f) {
  case GL::BufferFrequencyHint::STREAM:
    switch (a) {
    case GL::BufferAccessNatureHint::DRAW:
      return GL_STREAM_DRAW;
    case GL::BufferAccessNatureHint::COPY:
      return GL_STREAM_COPY;
    case GL::BufferAccessNatureHint::READ:
      return GL_STREAM_READ;
    }
  case GL::BufferFrequencyHint::STATIC:
    switch (a) {
    case GL::BufferAccessNatureHint::DRAW:
      return GL_STATIC_DRAW;
    case GL::BufferAccessNatureHint::COPY:
      return GL_STATIC_COPY;
    case GL::BufferAccessNatureHint::READ:
      return GL_STATIC_READ;
    }
  case GL::BufferFrequencyHint::DYNAMIC:
    switch (a) {
    case GL::BufferAccessNatureHint::DRAW:
      return GL_DYNAMIC_DRAW;
    case GL::BufferAccessNatureHint::COPY:
      return GL_DYNAMIC_COPY;
    case GL::BufferAccessNatureHint::READ:
      return GL_DYNAMIC_READ;
    }
  }
}

void GL::VertexBuffer::update(const std::vector<float> &data,
                              GL::BufferFrequencyHint freq,
                              GL::BufferAccessNatureHint acc) const {
  glNamedBufferData(m_VertexBufferId, sizeof(float) * data.size(), data.data(),
                    glHintFromEnums(freq, acc));
}

GL::Binding::Binding(unsigned int vbIdx, unsigned int bindingIdx,
                     unsigned int offset, unsigned int stride)
    : m_VertexBufferId(vbIdx), m_BindingIndex(bindingIdx), m_Offset(offset),
      m_Stride(stride) {}

GL::Binding GL::Binding::create(const VertexBuffer &vb,
                                unsigned int bindingIndex, unsigned int offset,
                                unsigned int stride) {
  return Binding(vb.m_VertexBufferId, bindingIndex, offset, stride);
}

unsigned int GL::Binding::getBindingIndex() const { return m_BindingIndex; }

unsigned int GL::Binding::getBufferId() const { return m_VertexBufferId; }

unsigned int GL::Binding::getOffset() const { return m_Offset; }

unsigned int GL::Binding::getStride() const { return m_Stride; }
