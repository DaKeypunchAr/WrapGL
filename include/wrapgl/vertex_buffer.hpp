#ifndef WRAPGL_VERTEX_BUFFER_HPP
#define WRAPGL_VERTEX_BUFFER_HPP
#include <vector>

namespace GL {

// TODO: Come with better names
enum class BufferFrequencyHint { STREAM, STATIC, DYNAMIC };

// TODO: Come with better names
enum class BufferAccessNatureHint { DRAW, READ, COPY };

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
      const GL::BufferFrequencyHint freq = GL::BufferFrequencyHint::STATIC,
      const GL::BufferAccessNatureHint acc = GL::BufferAccessNatureHint::DRAW);
  static VertexBuffer createAndAllocate(
      const unsigned int bufferSizeInBytes,
      const GL::BufferFrequencyHint freq = GL::BufferFrequencyHint::STATIC,
      const GL::BufferAccessNatureHint acc = GL::BufferAccessNatureHint::DRAW);

public:
  VertexBuffer() = delete;
  ~VertexBuffer();

  void update(const std::vector<float> &data,
              const unsigned int offsetInBytes = 0) const;

  void allocateBuffer(
      const std::vector<float> &data,
      const GL::BufferFrequencyHint freq = GL::BufferFrequencyHint::STATIC,
      const GL::BufferAccessNatureHint acc =
          GL::BufferAccessNatureHint::DRAW) const;

  void allocateBuffer(
      const unsigned int bufferSizeInBytes,
      const GL::BufferFrequencyHint freq = GL::BufferFrequencyHint::STATIC,
      const GL::BufferAccessNatureHint acc =
          GL::BufferAccessNatureHint::DRAW) const;

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
