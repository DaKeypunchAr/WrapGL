#ifndef WRAPGL_DATA_TYPES_HPP
#define WRAPGL_DATA_TYPES_HPP
#include "glad/glad.h"
#include <stdexcept>

namespace GL {

enum class DataType {
  F32,
  U8,
  U16,
  U32,
};

inline constexpr unsigned int glType(const GL::DataType type) {
  switch (type) {
  case GL::DataType::F32:
    return GL_FLOAT;
  case GL::DataType::U8:
    return GL_UNSIGNED_BYTE;
  case GL::DataType::U16:
    return GL_UNSIGNED_SHORT;
  case GL::DataType::U32:
    return GL_UNSIGNED_INT;
  default:
    throw std::runtime_error("Unknown Type");
  }
}

inline constexpr unsigned char glBool(const bool b) {
  return b ? GL_TRUE : GL_FALSE;
}

} // namespace GL

#endif
