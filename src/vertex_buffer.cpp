#include "wrapgl/vertex_buffer.hpp"
#include "glad/glad.h"
#include <iostream>

GL::VertexBuffer::VertexBuffer(const unsigned int rawId)
    : m_VertexBufferId(rawId) {}

GL::VertexBuffer GL::VertexBuffer::create() {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  return GL::VertexBuffer(rawId);
}

GL::VertexBuffer
GL::VertexBuffer::createAndAllocate(const std::vector<float> &data,
                                    const GL::BufferUpdateFrequency freq,
                                    const GL::BufferAccessPattern acc) {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  glNamedBufferData(rawId, static_cast<long>(sizeof(float) * data.size()),
                    data.data(), glHintFromEnums(freq, acc));
  return GL::VertexBuffer(rawId);
}
GL::VertexBuffer
GL::VertexBuffer::createAndAllocate(const unsigned int bufferSizeInBytes,
                                    const GL::BufferUpdateFrequency freq,
                                    const GL::BufferAccessPattern acc) {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  glNamedBufferData(rawId, bufferSizeInBytes, nullptr,
                    glHintFromEnums(freq, acc));
  return GL::VertexBuffer(rawId);
}

GL::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferId); }

void GL::VertexBuffer::update(const std::vector<float> &data,
                              const unsigned int offsetInBytes) const {
  if ((offsetInBytes + data.size() * sizeof(float)) > getBufferSizeInBytes()) {
    std::cerr << "You should not update the buffer past it's boundary. "
                 "Reallocated buffer for your ease. But fix it.\n";
    int usage_hint;
    glGetNamedBufferParameteriv(m_VertexBufferId, GL_BUFFER_USAGE, &usage_hint);
    glNamedBufferData(m_VertexBufferId,
                      static_cast<long>(sizeof(float) * data.size()),
                      data.data(), usage_hint);
    return;
  }

  glNamedBufferSubData(m_VertexBufferId, offsetInBytes,
                       static_cast<long>(sizeof(float) * data.size()),
                       data.data());
}

void GL::VertexBuffer::allocateBuffer(const std::vector<float> &data,
                                      const GL::BufferUpdateFrequency freq,
                                      const GL::BufferAccessPattern acc) const {
  glNamedBufferData(m_VertexBufferId,
                    static_cast<long>(sizeof(float) * data.size()), data.data(),
                    glHintFromEnums(freq, acc));
}

void GL::VertexBuffer::allocateBuffer(const unsigned int bufferSizeInBytes,
                                      const GL::BufferUpdateFrequency freq,
                                      const GL::BufferAccessPattern acc) const {
  glNamedBufferData(m_VertexBufferId, bufferSizeInBytes, nullptr,
                    glHintFromEnums(freq, acc));
}

unsigned int GL::VertexBuffer::getBufferSizeInBytes() const {
  int size;
  glGetNamedBufferParameteriv(m_VertexBufferId, GL_BUFFER_SIZE, &size);
  return static_cast<unsigned int>(size);
}

GL::Binding::Binding(const unsigned int vbIdx, const unsigned int bindingIdx,
                     const unsigned int offset, const unsigned int stride)
    : m_VertexBufferId(vbIdx), m_BindingIndex(bindingIdx), m_Offset(offset),
      m_Stride(stride) {}

GL::Binding GL::Binding::create(const VertexBuffer &vb,
                                const unsigned int bindingIndex,
                                const unsigned int offset,
                                const unsigned int stride) {
  return Binding(vb.m_VertexBufferId, bindingIndex, offset, stride);
}

unsigned int GL::Binding::getBindingIndex() const { return m_BindingIndex; }

unsigned int GL::Binding::getBufferId() const { return m_VertexBufferId; }

unsigned int GL::Binding::getOffset() const { return m_Offset; }

unsigned int GL::Binding::getStride() const { return m_Stride; }
