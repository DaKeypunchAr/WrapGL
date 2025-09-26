#ifndef WRAPGL_SHADER_PROGRAM_HPP
#define WRAPGL_SHADER_PROGRAM_HPP
#include <string_view>

namespace GL {
class ShaderProgram {
private:
  unsigned int m_ShaderProgramId;

private:
  ShaderProgram(unsigned int linkedShaderProgramId);

private:
  static void compileShader(unsigned int shaderId);
  static void linkProgram(unsigned int programId);

public:
  static ShaderProgram createFromSource(const std::string_view &vsSource,
                                        const std::string_view &fsSource);
  // TODO: Add more

public:
  ShaderProgram() = delete;
  ~ShaderProgram();

  void select() const;
};
} // namespace GL

#endif
