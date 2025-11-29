#ifndef WRAPGL_INDEX_BUFFER_HPP
#define WRAPGL_INDEX_BUFFER_HPP
#include "buffer_commons.hpp"
#include "data_types.hpp"
#include <vector>

namespace GL {
class VertexArray;

class IndexBuffer {
private:
  unsigned int m_IndexBufferId;
  GL::DataType m_UnitType;

private:
  IndexBuffer(const unsigned int rawId,
              const GL::DataType unitType = GL::DataType::U8);

public:
  static IndexBuffer create();
  static IndexBuffer createAndAllocate(
      const std::vector<unsigned char> &data,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);
  static IndexBuffer createAndAllocate(
      const unsigned int bufferSizeInBytes,
      const GL::DataType type = GL::DataType::U8,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);

public:
  IndexBuffer() = delete;
  ~IndexBuffer();

  void update(const std::vector<unsigned char> &data,
              const unsigned int offsetInBytes = 0) const;

  void allocateBuffer(
      const std::vector<unsigned char> &data,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);

  void allocateBuffer(
      const unsigned int bufferSizeInBytes,
      const GL::DataType type = GL::DataType::U8,
      const GL::BufferUpdateFrequency freq = GL::BufferUpdateFrequency::STATIC,
      const GL::BufferAccessPattern acc = GL::BufferAccessPattern::DRAW);

  unsigned int getBufferSizeInBytes() const;

  inline GL::DataType getUnitType() const { return m_UnitType; }

  friend VertexArray;
};

} // namespace GL
#endif
