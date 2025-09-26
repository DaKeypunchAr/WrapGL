#include "shader_program.hpp"
#include "glad/glad.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

GL::ShaderProgram::ShaderProgram(unsigned int linkedShaderProgramId)
    : m_ShaderProgramId(linkedShaderProgramId) {}

void GL::ShaderProgram::compileShader(unsigned int shaderId) {
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

void GL::ShaderProgram::linkProgram(unsigned int programId) {
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

GL::ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ShaderProgramId); }

void GL::ShaderProgram::select() const { glUseProgram(m_ShaderProgramId); }
