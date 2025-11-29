#ifndef WRAPGL_VERTEX_ARRAY_HPP
#define WRAPGL_VERTEX_ARRAY_HPP
#include "data_types.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

namespace GL {

struct Attribute {
  unsigned int count = 0;
  unsigned int bindingIndex = 0;
  unsigned int relativeOffset = 0;
  DataType type;
  bool isNormalized = false;

  constexpr static Attribute create(DataType type, unsigned int count,
                                    unsigned int bindingIndex = 0,
                                    unsigned int relativeOffset = 0,
                                    bool isNormalized = false) {
    return Attribute{.count = count,
                     .bindingIndex = bindingIndex,
                     .relativeOffset = relativeOffset,
                     .type = type,
                     .isNormalized = isNormalized};
  }
};

class VertexArray {
private:
  unsigned int m_VertexArrayId;

private:
  VertexArray(const unsigned int rawId);

public:
  static VertexArray create();

public:
  VertexArray() = delete;
  ~VertexArray();

  void setFormat(const std::vector<Attribute> &attributes) const;
  void setBufferBindings(const std::vector<Binding> &bindings) const;
  void linkIndexBuffer(const IndexBuffer &buffer) const;
  void select() const;
};
} // namespace GL

#endif
