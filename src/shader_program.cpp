#include "wrapgl/shader_program.hpp"
#include "glad/glad.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

GL::ShaderProgram::ShaderProgram(const unsigned int linkedShaderProgramId)
    : m_ShaderProgramId(linkedShaderProgramId) {}

void GL::ShaderProgram::compileShader(const unsigned int shaderId) {
  glCompileShader(shaderId);

  int compilationStatus;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);

  if (!compilationStatus) {
    int logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(logLength);
    glGetShaderInfoLog(shaderId, logLength, nullptr, log.data());
    std::cout << "Failed to compile shader (id: " << shaderId
              << ")\nLog: " << log.data() << '\n';
    throw std::runtime_error("Failed to compile shader!");
  }
}

void GL::ShaderProgram::linkProgram(const unsigned int programId) {
  glLinkProgram(programId);

  int linkingStatus;
  glGetProgramiv(programId, GL_LINK_STATUS, &linkingStatus);

  if (!linkingStatus) {
    int logLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(logLength);
    glGetProgramInfoLog(programId, logLength, nullptr, log.data());
    std::cout << "Failed to link program (id: " << programId
              << ")\nLog: " << log.data() << '\n';
    throw std::runtime_error("Failed to link program!");
  }
}

GL::ShaderProgram
GL::ShaderProgram::createFromSource(const std::string_view &vsSource,
                                    const std::string_view &fsSource) {
  unsigned int programId = glCreateProgram();
  unsigned int vsId = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fsId = glCreateShader(GL_FRAGMENT_SHADER);

  const char *vsSrcCstr = vsSource.data();
  const char *fsSrcCstr = fsSource.data();
  glShaderSource(vsId, 1, &vsSrcCstr, nullptr);
  glShaderSource(fsId, 1, &fsSrcCstr, nullptr);

  try {
    compileShader(vsId);
  } catch (const std::runtime_error &err) {
    std::string str = "Failed to compile vertex shader with id: ";
    str += vsId;
    throw std::runtime_error(str.data());
  }

  try {
    compileShader(fsId);
  } catch (const std::runtime_error &err) {
    std::string str = "Failed to compile fragment shader with id: ";
    str += fsId;
    throw std::runtime_error(str.data());
  }

  glAttachShader(programId, vsId);
  glAttachShader(programId, fsId);

  try {
    linkProgram(programId);
  } catch (const std::runtime_error &err) {
    std::string str = "Failed to link program with id: ";
    str += programId;
    throw std::runtime_error(str.data());
  }

  glDetachShader(programId, vsId);
  glDetachShader(programId, fsId);

  glDeleteShader(vsId);
  glDeleteShader(fsId);

  return GL::ShaderProgram(programId);
}

GL::ShaderProgram
GL::ShaderProgram::createFromFilePath(const std::filesystem::path &vsPath,
                                      const std::filesystem::path &fsPath) {
  std::string vsSrc, fsSrc;
  std::ifstream fileReader(vsPath);
  if (!fileReader.is_open()) {
    std::string errMsg = "Failed to open file: ";
    errMsg += vsPath.string();
    errMsg += "\nThe file was passed to be used as vertex shader!";
    throw std::runtime_error(errMsg);
  }
  for (std::string line; std::getline(fileReader, line); vsSrc += '\n')
    vsSrc += line;

  fileReader.close();
  fileReader.open(fsPath);

  if (!fileReader.is_open()) {
    std::string errMsg = "Failed to open file: ";
    errMsg += vsPath.string();
    errMsg += "\nThe file was passed to be used as fragment shader!";
    throw std::runtime_error(errMsg);
  }

  for (std::string line; std::getline(fileReader, line); fsSrc += '\n')
    fsSrc += line;

  return ShaderProgram::createFromSource(vsSrc, fsSrc);
}

GL::ShaderProgram
GL::ShaderProgram::createFromFolder(const std::filesystem::path &folderPath) {
  return createFromFilePath(folderPath / "vertex.glsl",
                            folderPath / "fragment.glsl");
}

GL::ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ShaderProgramId); }

void GL::ShaderProgram::select() const { glUseProgram(m_ShaderProgramId); }

int GL::ShaderProgram::getUniformLocation(
    const std::string_view &uniformName) const {
  return glGetUniformLocation(m_ShaderProgramId, uniformName.data());
}

void GL::ShaderProgram::setUniform(const int uniformLocation,
                                   const int value) const {
  glUniform1i(uniformLocation, value);
}

void GL::ShaderProgram::setUniform(const std::string_view &uniformName,
                                   const int value) const {
  setUniform(getUniformLocation(uniformName), value);
}
