#ifndef WRAPGL_VERTEX_ARRAY_HPP
#define WRAPGL_VERTEX_ARRAY_HPP
#include "vertex_buffer.hpp"

namespace GL {
enum class DataType {
  F32,
};

struct Attribute {
  DataType type;
  bool isNormalized;
  unsigned int count;
  unsigned int bindingIndex;
  unsigned int relativeOffset;
};

class VertexArray {
private:
  unsigned int m_VertexArrayId;

private:
  VertexArray(unsigned int rawId);

public:
  static VertexArray create();

public:
  VertexArray() = delete;
  ~VertexArray();

  void setFormat(const std::vector<Attribute> &attributes) const;
  void setBufferBindings(const std::vector<Binding> &bindings) const;
  void select() const;
};
} // namespace GL

#endif
