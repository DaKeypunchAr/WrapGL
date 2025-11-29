#include "wrapgl/index_buffer.hpp"
#include "wrapgl/data_types.hpp"
#include <iostream>
#include <stdexcept>

GL::IndexBuffer::IndexBuffer(const unsigned int rawId, const GL::DataType type)
    : m_IndexBufferId(rawId), m_UnitType(type) {}

GL::IndexBuffer GL::IndexBuffer::create() {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  return GL::IndexBuffer(rawId);
}

GL::IndexBuffer
GL::IndexBuffer::createAndAllocate(const std::vector<unsigned char> &data,
                                   const GL::BufferUpdateFrequency freq,
                                   const GL::BufferAccessPattern acc) {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  glNamedBufferData(rawId,
                    static_cast<long>(sizeof(unsigned char) * data.size()),
                    data.data(), glHintFromEnums(freq, acc));
  return GL::IndexBuffer(rawId, GL::DataType::U8);
}
GL::IndexBuffer GL::IndexBuffer::createAndAllocate(
    const unsigned int bufferSizeInBytes, const GL::DataType unitType,
    const GL::BufferUpdateFrequency freq, const GL::BufferAccessPattern acc) {
  unsigned int rawId;
  glCreateBuffers(1, &rawId);
  glNamedBufferData(rawId, bufferSizeInBytes, nullptr,
                    glHintFromEnums(freq, acc));
  return GL::IndexBuffer(rawId, unitType);
}

GL::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_IndexBufferId); }

void GL::IndexBuffer::update(const std::vector<unsigned char> &data,
                             const unsigned int offsetInBytes) const {
  if (m_UnitType != GL::DataType::U8) {
    throw std::runtime_error("Index unit type mismatched: it's not u8");
  }
  if ((offsetInBytes + data.size() * sizeof(float)) > getBufferSizeInBytes()) {
    std::cerr << "You should not update the buffer past it's boundary. "
                 "Reallocated buffer for your ease. But fix it.\n";
    int usage_hint;
    glGetNamedBufferParameteriv(m_IndexBufferId, GL_BUFFER_USAGE, &usage_hint);
    glNamedBufferData(m_IndexBufferId,
                      static_cast<long>(sizeof(unsigned char) * data.size()),
                      data.data(), usage_hint);
    return;
  }

  glNamedBufferSubData(m_IndexBufferId, offsetInBytes,
                       static_cast<long>(sizeof(unsigned char) * data.size()),
                       data.data());
}

void GL::IndexBuffer::allocateBuffer(const std::vector<unsigned char> &data,
                                     const GL::BufferUpdateFrequency freq,
                                     const GL::BufferAccessPattern acc) {
  m_UnitType = GL::DataType::U8;
  glNamedBufferData(m_IndexBufferId,
                    static_cast<long>(sizeof(unsigned char) * data.size()),
                    data.data(), glHintFromEnums(freq, acc));
}

void GL::IndexBuffer::allocateBuffer(const unsigned int bufferSizeInBytes,
                                     const GL::DataType type,
                                     const GL::BufferUpdateFrequency freq,
                                     const GL::BufferAccessPattern acc) {
  m_UnitType = type;
  glNamedBufferData(m_IndexBufferId, bufferSizeInBytes, nullptr,
                    glHintFromEnums(freq, acc));
}

unsigned int GL::IndexBuffer::getBufferSizeInBytes() const {
  int size;
  glGetNamedBufferParameteriv(m_IndexBufferId, GL_BUFFER_SIZE, &size);
  return static_cast<unsigned int>(size);
}
