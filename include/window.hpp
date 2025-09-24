#ifndef WRAPGL_WINDOW_HPP
#define WRAPGL_WINDOW_HPP
#include <glm/glm.hpp>
#include <string>
#include <string_view>

struct GLFWwindow; // Declared to remove GLFW include.
class Window {
private:
  GLFWwindow *m_WindowHandle;
  std::string m_Title;

private:
  Window(const glm::uvec2 dimensions, const std::string_view &title);

public:
  static Window create(const glm::uvec2 dimensions,
                       const std::string_view &title);
  static void pollEvents();

public:
  Window() = delete;
  Window(const Window &other) = delete;
  Window(const Window &&other) = delete;
  ~Window();

  bool shouldClose() const;
  void swapBuffers() const;
  void triggerClose() const;
  bool isKeyPressed(const int glfwKey) const;
  void select() const;
  bool isSelected() const;
  void clear(const glm::vec4 &color) const;
  std::string_view getTitle() const;
};
#endif
