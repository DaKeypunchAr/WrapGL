#define GLFW_INCLUDE_NONE
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glfw.hpp>
#include <iostream>
#include <stdexcept>

void opengl_error_callback(GLenum source, GLenum type, GLuint id,
                           GLenum severity, GLsizei length,
                           GLchar const *message, void const *user_param) {
  const char *const src_str = [source]() {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return "WINDOW SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return "SHADER COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return "THIRD PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
      return "APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
      return "OTHER";
    default:
      return "UNKNOWN";
    }
  }();

  const char *const type_str = [type]() {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      return "ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
      return "PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return "PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER:
      return "MARKER";
    case GL_DEBUG_TYPE_OTHER:
      return "OTHER";
    default:
      return "UNKNOWN";
    }
  }();

  const char *const severity_str = [severity]() {
    switch (severity) {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "NOTIFICATION";
    case GL_DEBUG_SEVERITY_LOW:
      return "LOW";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return "MEDIUM";
    case GL_DEBUG_SEVERITY_HIGH:
      return "HIGH";
    default:
      return "UNKNOWN";
    }
  }();
  std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id
            << ": " << message << '\n';
  if (user_param == nullptr)
    throw std::runtime_error("User Parameter that is the Window ptr is null!");
  else
    std::cout << "From window with title: "
              << ((Window *)user_param)->getTitle() << '\n';
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Static methods
Window Window::create(const glm::uvec2 dimensions,
                      const std::string_view &title) {
  if (!GLFW::isInitialized()) {
    std::runtime_error("GLFW is not initialized!");
  }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  return Window(dimensions, title);
}

// Non-static methods
Window::Window(const glm::uvec2 dimensions, const std::string_view &title)
    : m_WindowHandle(glfwCreateWindow(dimensions.x, dimensions.y, title.data(),
                                      nullptr, nullptr)),
      m_Title(title) {
  if (!m_WindowHandle) {
    glfwTerminate();
    throw std::runtime_error("GLFW failed to create a window!");
  }
  glfwSetFramebufferSizeCallback(m_WindowHandle, framebuffer_size_callback);
  glfwMakeContextCurrent(m_WindowHandle);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Unable to initialize GLAD!");
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, this);
}

Window::~Window() {
  if (GLFW::isInitialized() && m_WindowHandle) {
    // Don't know if necessary, but prevents any UB, ig...
    glDebugMessageCallback(opengl_error_callback, nullptr);
    glfwDestroyWindow(m_WindowHandle);
    m_WindowHandle = nullptr;
  }
}

void Window::select() const { glfwMakeContextCurrent(m_WindowHandle); }

bool Window::isSelected() const {
  return m_WindowHandle == glfwGetCurrentContext();
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(m_WindowHandle);
}

void Window::swapBuffers() const { glfwSwapBuffers(m_WindowHandle); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::triggerClose() const {
  glfwSetWindowShouldClose(m_WindowHandle, GLFW_TRUE);
}

bool Window::isKeyPressed(const int glfwKey) const {
  return glfwGetKey(m_WindowHandle, glfwKey) == GLFW_PRESS;
}

std::string_view Window::getTitle() const { return m_Title; }

void Window::clear(const glm::vec4 &color) const {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}
