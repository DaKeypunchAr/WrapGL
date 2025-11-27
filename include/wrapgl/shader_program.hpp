#ifndef WRAPGL_SHADER_PROGRAM_HPP
#define WRAPGL_SHADER_PROGRAM_HPP
#include <filesystem>
#include <glm/glm.hpp>
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

  // Uniform setting ones
#define UNIFORM_DECL(type)                                                     \
  void setUniform(const int uniformLocation, const type value) const;          \
  void setUniform(const std::string_view &uniformName, const type value) const;

  UNIFORM_DECL(float)
  UNIFORM_DECL(glm::vec2)
  UNIFORM_DECL(glm::vec3)
  UNIFORM_DECL(glm::vec4)

  UNIFORM_DECL(int)
  UNIFORM_DECL(glm::ivec2)
  UNIFORM_DECL(glm::ivec3)
  UNIFORM_DECL(glm::ivec4)

  UNIFORM_DECL(unsigned int)
  UNIFORM_DECL(glm::uvec2)
  UNIFORM_DECL(glm::uvec3)
  UNIFORM_DECL(glm::uvec4)
};
} // namespace GL

#endif
