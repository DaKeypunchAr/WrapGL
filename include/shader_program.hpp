#ifndef WRAPGL_SHADER_PROGRAM_HPP
#define WRAPGL_SHADER_PROGRAM_HPP
#include <filesystem>
#include <string_view>

namespace GL {
class ShaderProgram {
private:
  unsigned int m_ShaderProgramId;

private:
  ShaderProgram(const unsigned int linkedShaderProgramId);

private:
  static void compileShader(const unsigned int shaderId);
  static void linkProgram(const unsigned int programId);

public:
  static ShaderProgram
  createFromFolder(const std::filesystem::path &folderPath);

  static ShaderProgram createFromFilePath(const std::filesystem::path &vsPath,
                                          const std::filesystem::path &fsPath);
  static ShaderProgram createFromSource(const std::string_view &vsSource,
                                        const std::string_view &fsSource);
  // TODO: Add more

public:
  ShaderProgram() = delete;
  ~ShaderProgram();

  void select() const;
  int getUniformLocation(const std::string_view &uniformName) const;
  void setUniform(const int uniformLocation, const int value) const;
  void setUniform(const std::string_view &uniformName, const int value) const;
};
} // namespace GL

#endif
