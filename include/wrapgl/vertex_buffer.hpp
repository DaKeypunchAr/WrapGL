#ifndef WRAPGL_VERTEX_BUFFER_HPP
#define WRAPGL_VERTEX_BUFFER_HPP
#include "buffer_commons.hpp"
#include <vector>

namespace GL {

class Binding;

class VertexBuffer {
private:
  unsigned int m_VertexBufferId;

private:
  VertexBuffer(const unsigned int rawId);

public:
  static VertexBuffer create();
  static VertexBuffer createAndAllocate(
      const std::vector<float> &data,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);
  static VertexBuffer createAndAllocate(
      const unsigned int bufferSizeInBytes,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);

public:
  VertexBuffer() = delete;
  ~VertexBuffer();

  void update(const std::vector<float> &data,
              const unsigned int offsetInBytes = 0) const;

  void allocateBuffer(
      const std::vector<float> &data,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW) const;

  void allocateBuffer(
      const unsigned int bufferSizeInBytes,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW) const;

  unsigned int getBufferSizeInBytes() const;

  friend Binding;
};

class Binding {
private:
  unsigned int m_VertexBufferId;
  unsigned int m_BindingIndex;
  unsigned int m_Offset;
  unsigned int m_Stride;

private:
  Binding(const unsigned int vbId, const unsigned int bindingIdx,
          const unsigned int offset, const unsigned int stride);

public:
  static Binding create(const VertexBuffer &vb, const unsigned int bindingIndex,
                        const unsigned int offset, const unsigned int stride);

public:
  Binding() = delete;

  unsigned int getBufferId() const;
  unsigned int getOffset() const;
  unsigned int getStride() const;
  unsigned int getBindingIndex() const;
};
} // namespace GL

#endif
