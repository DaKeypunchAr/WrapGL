#ifndef WRAPGL_WINDOW_HPP
#define WRAPGL_WINDOW_HPP
#include <forward_list>
#include <functional>
#include <glm/glm.hpp>
#include <string>
#include <string_view>

struct GLFWwindow; // Declared to remove GLFW include.

enum class Key {
  Unknown,
  Space,
  Apostrophe,
  Comma,
  Minus,
  Period,
  Slash,
  D0,
  D1,
  D2,
  D3,
  D4,
  D5,
  D6,
  D7,
  D8,
  D9,
  Semicolon,
  Equal,
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  LeftBracket,
  Backslash,
  RightBracket,
  GraveAccent,
  World1,
  World2,

  Escape,
  Enter,
  Tab,
  Backspace,
  Insert,
  Delete,
  Right,
  Left,
  Down,
  Up,
  PageUp,
  PageDown,
  Home,
  End,
  CapsLock,
  ScrollLock,
  NumLock,
  PrintScreen,
  Pause,

  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  F13,
  F14,
  F15,
  F16,
  F17,
  F18,
  F19,
  F20,
  F21,
  F22,
  F23,
  F24,
  F25,

  KP0,
  KP1,
  KP2,
  KP3,
  KP4,
  KP5,
  KP6,
  KP7,
  KP8,
  KP9,
  KP_Decimal,
  KP_Divide,
  KP_Multiply,
  KP_Subtract,
  KP_Add,
  KP_Enter,
  KP_Equal,

  LeftShift,
  LeftControl,
  LeftAlt,
  LeftSuper,
  RightShift,
  RightControl,
  RightAlt,
  RightSuper,
  Menu
};

class Window {
private:
  Window(const glm::uvec2 dimensions, const std::string_view &title,
         const std::function<void(glm::uvec2)> &framebuffer_size_callback = {});

public:
  static Window
  create(const glm::uvec2 dimensions, const std::string_view &title,
         const std::function<void(glm::uvec2)> &framebufferSizeCallback = {});
  static void pollEvents();
  static const Window *getActiveWindow();

public:
  Window() = delete;
  Window(const Window &other) = delete;
  Window &operator=(const Window &) = delete;
  ~Window();

  bool shouldClose() const;
  void swapBuffers() const;
  void triggerClose() const;
  bool isKeyPressed(const Key key) const;
  void select() const;
  bool isSelected() const;
  inline std::string_view getTitle() const { return m_Title; }
  glm::uvec2 getCurrentDimension() const;
  inline unsigned int getCurrentWidth() const {
    return getCurrentDimension().x;
  }
  inline unsigned int getCurrentHeight() const {
    return getCurrentDimension().y;
  }
  inline glm::uvec2 getInitialDimension() const { return m_InitialDimension; }

  inline GLFWwindow *getRawPointer() const { return m_WindowHandle; }

  inline void
  setFrameBufferSizeCallback(const std::function<void(glm::uvec2)> &f) const {
    m_FrameBufferSizeCallback = f;
  }

  friend void framebuffer_size_callback(GLFWwindow *, int, int);

private:
  static void callFramebufferSizeCallback(const GLFWwindow *const ptr,
                                          const glm::uvec2 dimension);

private:
  GLFWwindow *m_WindowHandle;
  std::string m_Title;
  glm::uvec2 m_InitialDimension;
  mutable std::function<void(glm::uvec2)> m_FrameBufferSizeCallback;

private:
  struct WindowInst {
    const GLFWwindow *glfwPtr;
    const Window *wrapglPtr;
    WindowInst(const GLFWwindow *const glfwPtr, const Window *const wrapglPtr)
        : glfwPtr(glfwPtr), wrapglPtr(wrapglPtr) {}
  };
  inline static std::forward_list<WindowInst> s_Instances = {};
  inline static const Window *s_ActiveInstance = nullptr;
};

#endif
