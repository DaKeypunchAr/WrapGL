#ifndef WRAPGL_BUFFER_COMMONS_HPP
#define WRAPGL_BUFFER_COMMONS_HPP
#include "glad/glad.h"
#include <stdexcept>

namespace GL {

// How often the buffer is updated
enum class BufferUpdateFrequency {
  STREAM, // Updated almost every frame
  STATIC, // Set once, used many times
  DYNAMIC // Updated occasionally, used many times
};

// Intended usage direction / access pattern
enum class BufferAccessPattern {
  DRAW, // GPU reads the buffer for drawing (most common)
  READ, // CPU reads back from GPU (rare for index buffers)
  COPY  // GPU writes to buffer (rare, e.g., transform feedback)
};

inline constexpr unsigned int glHintFromEnums(const GL::BufferUpdateFrequency f,
                                              const GL::BufferAccessPattern a) {
  switch (f) {
  case GL::BufferUpdateFrequency::STREAM:
    switch (a) {
    case GL::BufferAccessPattern::DRAW:
      return GL_STREAM_DRAW;
    case GL::BufferAccessPattern::COPY:
      return GL_STREAM_COPY;
    case GL::BufferAccessPattern::READ:
      return GL_STREAM_READ;
    default:
      throw std::runtime_error("Unknown Access Nature Hint");
    }
  case GL::BufferUpdateFrequency::STATIC:
    switch (a) {
    case GL::BufferAccessPattern::DRAW:
      return GL_STATIC_DRAW;
    case GL::BufferAccessPattern::COPY:
      return GL_STATIC_COPY;
    case GL::BufferAccessPattern::READ:
      return GL_STATIC_READ;
    default:
      throw std::runtime_error("Unknown Access Nature Hint");
    }
  case GL::BufferUpdateFrequency::DYNAMIC:
    switch (a) {
    case GL::BufferAccessPattern::DRAW:
      return GL_DYNAMIC_DRAW;
    case GL::BufferAccessPattern::COPY:
      return GL_DYNAMIC_COPY;
    case GL::BufferAccessPattern::READ:
      return GL_DYNAMIC_READ;
    default:
      throw std::runtime_error("Unknown Access Nature Hint");
    }
  default:
    throw std::runtime_error("Unknown Frequency Hint");
  }
}
} // namespace GL

#endif
