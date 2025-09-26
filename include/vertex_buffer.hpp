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
  VertexBuffer(unsigned int rawId);

public:
  static VertexBuffer create();

public:
  VertexBuffer() = delete;
  ~VertexBuffer();

  void update(
      const std::vector<float> &data,
      GL::BufferFrequencyHint freq = GL::BufferFrequencyHint::STATIC,
      GL::BufferAccessNatureHint acc = GL::BufferAccessNatureHint::DRAW) const;

  friend Binding;
};

class Binding {
private:
  unsigned int m_VertexBufferId;
  unsigned int m_BindingIndex;
  unsigned int m_Offset;
  unsigned int m_Stride;

private:
  Binding(unsigned int vbId, unsigned int bindingIdx, unsigned int offset,
          unsigned int stride);

public:
  static Binding create(const VertexBuffer &vb, unsigned int bindingIndex,
                        unsigned int offset, unsigned int stride);

public:
  Binding() = delete;

  unsigned int getBufferId() const;
  unsigned int getOffset() const;
  unsigned int getStride() const;
  unsigned int getBindingIndex() const;
};
} // namespace GL

#endif
