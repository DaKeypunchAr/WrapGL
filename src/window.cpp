#define GLFW_INCLUDE_NONE
#include "wrapgl/window.hpp"
#include "wrapgl/glfw.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>

int glfwKey(const Key k);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void opengl_error_callback(GLenum source, GLenum type, GLuint id,
                           GLenum severity, GLsizei length,
                           GLchar const *message, void const *user_param);

int glfwKey(const Key k) {
  switch (k) {
  case Key::Unknown:
    return GLFW_KEY_UNKNOWN;
  case Key::Space:
    return GLFW_KEY_SPACE;
  case Key::Apostrophe:
    return GLFW_KEY_APOSTROPHE;
  case Key::Comma:
    return GLFW_KEY_COMMA;
  case Key::Minus:
    return GLFW_KEY_MINUS;
  case Key::Period:
    return GLFW_KEY_PERIOD;
  case Key::Slash:
    return GLFW_KEY_SLASH;
  case Key::D0:
    return GLFW_KEY_0;
  case Key::D1:
    return GLFW_KEY_1;
  case Key::D2:
    return GLFW_KEY_2;
  case Key::D3:
    return GLFW_KEY_3;
  case Key::D4:
    return GLFW_KEY_4;
  case Key::D5:
    return GLFW_KEY_5;
  case Key::D6:
    return GLFW_KEY_6;
  case Key::D7:
    return GLFW_KEY_7;
  case Key::D8:
    return GLFW_KEY_8;
  case Key::D9:
    return GLFW_KEY_9;
  case Key::Semicolon:
    return GLFW_KEY_SEMICOLON;
  case Key::Equal:
    return GLFW_KEY_EQUAL;
  case Key::A:
    return GLFW_KEY_A;
  case Key::B:
    return GLFW_KEY_B;
  case Key::C:
    return GLFW_KEY_C;
  case Key::D:
    return GLFW_KEY_D;
  case Key::E:
    return GLFW_KEY_E;
  case Key::F:
    return GLFW_KEY_F;
  case Key::G:
    return GLFW_KEY_G;
  case Key::H:
    return GLFW_KEY_H;
  case Key::I:
    return GLFW_KEY_I;
  case Key::J:
    return GLFW_KEY_J;
  case Key::K:
    return GLFW_KEY_K;
  case Key::L:
    return GLFW_KEY_L;
  case Key::M:
    return GLFW_KEY_M;
  case Key::N:
    return GLFW_KEY_N;
  case Key::O:
    return GLFW_KEY_O;
  case Key::P:
    return GLFW_KEY_P;
  case Key::Q:
    return GLFW_KEY_Q;
  case Key::R:
    return GLFW_KEY_R;
  case Key::S:
    return GLFW_KEY_S;
  case Key::T:
    return GLFW_KEY_T;
  case Key::U:
    return GLFW_KEY_U;
  case Key::V:
    return GLFW_KEY_V;
  case Key::W:
    return GLFW_KEY_W;
  case Key::X:
    return GLFW_KEY_X;
  case Key::Y:
    return GLFW_KEY_Y;
  case Key::Z:
    return GLFW_KEY_Z;
  case Key::LeftBracket:
    return GLFW_KEY_LEFT_BRACKET;
  case Key::Backslash:
    return GLFW_KEY_BACKSLASH;
  case Key::RightBracket:
    return GLFW_KEY_RIGHT_BRACKET;
  case Key::GraveAccent:
    return GLFW_KEY_GRAVE_ACCENT;
  case Key::World1:
    return GLFW_KEY_WORLD_1;
  case Key::World2:
    return GLFW_KEY_WORLD_2;

  case Key::Escape:
    return GLFW_KEY_ESCAPE;
  case Key::Enter:
    return GLFW_KEY_ENTER;
  case Key::Tab:
    return GLFW_KEY_TAB;
  case Key::Backspace:
    return GLFW_KEY_BACKSPACE;
  case Key::Insert:
    return GLFW_KEY_INSERT;
  case Key::Delete:
    return GLFW_KEY_DELETE;
  case Key::Right:
    return GLFW_KEY_RIGHT;
  case Key::Left:
    return GLFW_KEY_LEFT;
  case Key::Down:
    return GLFW_KEY_DOWN;
  case Key::Up:
    return GLFW_KEY_UP;
  case Key::PageUp:
    return GLFW_KEY_PAGE_UP;
  case Key::PageDown:
    return GLFW_KEY_PAGE_DOWN;
  case Key::Home:
    return GLFW_KEY_HOME;
  case Key::End:
    return GLFW_KEY_END;
  case Key::CapsLock:
    return GLFW_KEY_CAPS_LOCK;
  case Key::ScrollLock:
    return GLFW_KEY_SCROLL_LOCK;
  case Key::NumLock:
    return GLFW_KEY_NUM_LOCK;
  case Key::PrintScreen:
    return GLFW_KEY_PRINT_SCREEN;
  case Key::Pause:
    return GLFW_KEY_PAUSE;

  case Key::F1:
    return GLFW_KEY_F1;
  case Key::F2:
    return GLFW_KEY_F2;
  case Key::F3:
    return GLFW_KEY_F3;
  case Key::F4:
    return GLFW_KEY_F4;
  case Key::F5:
    return GLFW_KEY_F5;
  case Key::F6:
    return GLFW_KEY_F6;
  case Key::F7:
    return GLFW_KEY_F7;
  case Key::F8:
    return GLFW_KEY_F8;
  case Key::F9:
    return GLFW_KEY_F9;
  case Key::F10:
    return GLFW_KEY_F10;
  case Key::F11:
    return GLFW_KEY_F11;
  case Key::F12:
    return GLFW_KEY_F12;
  case Key::F13:
    return GLFW_KEY_F13;
  case Key::F14:
    return GLFW_KEY_F14;
  case Key::F15:
    return GLFW_KEY_F15;
  case Key::F16:
    return GLFW_KEY_F16;
  case Key::F17:
    return GLFW_KEY_F17;
  case Key::F18:
    return GLFW_KEY_F18;
  case Key::F19:
    return GLFW_KEY_F19;
  case Key::F20:
    return GLFW_KEY_F20;
  case Key::F21:
    return GLFW_KEY_F21;
  case Key::F22:
    return GLFW_KEY_F22;
  case Key::F23:
    return GLFW_KEY_F23;
  case Key::F24:
    return GLFW_KEY_F24;
  case Key::F25:
    return GLFW_KEY_F25;

  case Key::KP0:
    return GLFW_KEY_KP_0;
  case Key::KP1:
    return GLFW_KEY_KP_1;
  case Key::KP2:
    return GLFW_KEY_KP_2;
  case Key::KP3:
    return GLFW_KEY_KP_3;
  case Key::KP4:
    return GLFW_KEY_KP_4;
  case Key::KP5:
    return GLFW_KEY_KP_5;
  case Key::KP6:
    return GLFW_KEY_KP_6;
  case Key::KP7:
    return GLFW_KEY_KP_7;
  case Key::KP8:
    return GLFW_KEY_KP_8;
  case Key::KP9:
    return GLFW_KEY_KP_9;
  case Key::KP_Decimal:
    return GLFW_KEY_KP_DECIMAL;
  case Key::KP_Divide:
    return GLFW_KEY_KP_DIVIDE;
  case Key::KP_Multiply:
    return GLFW_KEY_KP_MULTIPLY;
  case Key::KP_Subtract:
    return GLFW_KEY_KP_SUBTRACT;
  case Key::KP_Add:
    return GLFW_KEY_KP_ADD;
  case Key::KP_Enter:
    return GLFW_KEY_KP_ENTER;
  case Key::KP_Equal:
    return GLFW_KEY_KP_EQUAL;

  case Key::LeftShift:
    return GLFW_KEY_LEFT_SHIFT;
  case Key::LeftControl:
    return GLFW_KEY_LEFT_CONTROL;
  case Key::LeftAlt:
    return GLFW_KEY_LEFT_ALT;
  case Key::LeftSuper:
    return GLFW_KEY_LEFT_SUPER;
  case Key::RightShift:
    return GLFW_KEY_RIGHT_SHIFT;
  case Key::RightControl:
    return GLFW_KEY_RIGHT_CONTROL;
  case Key::RightAlt:
    return GLFW_KEY_RIGHT_ALT;
  case Key::RightSuper:
    return GLFW_KEY_RIGHT_SUPER;
  case Key::Menu:
    return GLFW_KEY_MENU;
  default:
    return GLFW_KEY_UNKNOWN;
  }
}

void opengl_error_callback(GLenum source, GLenum type, GLuint id,
                           GLenum severity, GLsizei length [[maybe_unused]],
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
              << (reinterpret_cast<const Window *>(user_param))->getTitle()
              << '\n';
}

void framebuffer_size_callback(GLFWwindow *window [[maybe_unused]], int width,
                               int height) {
  glViewport(0, 0, width, height);
}

// Static methods
Window Window::create(const glm::uvec2 dimensions,
                      const std::string_view &title) {
  if (!GLFW::isInitialized()) {
    GLFW::initialize();
  }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  return Window(dimensions, title);
}

// Non-static methods
Window::Window(const glm::uvec2 dimensions, const std::string_view &title)
    : m_WindowHandle(glfwCreateWindow(static_cast<int>(dimensions.x),
                                      static_cast<int>(dimensions.y),
                                      title.data(), nullptr, nullptr)),
      m_Title(title), m_InitialDimension(dimensions) {
  if (!m_WindowHandle) {
    GLFW::terminate();
    throw std::runtime_error("GLFW failed to create a window!");
  }
  glfwSetFramebufferSizeCallback(m_WindowHandle, framebuffer_size_callback);
  glfwMakeContextCurrent(m_WindowHandle);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
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

bool Window::isKeyPressed(const Key key) const {
  return glfwGetKey(m_WindowHandle, glfwKey(key)) == GLFW_PRESS;
}

glm::uvec2 Window::getCurrentDimension() const {
  int w, h;
  glfwGetWindowSize(m_WindowHandle, &w, &h);
  return glm::uvec2(w, h);
}
