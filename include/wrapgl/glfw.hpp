#ifndef WRAPGL_GLFW_HPP
#define WRAPGL_GLFW_HPP

enum class OpenGLProfile { CORE, COMPATABILITY, ES };

struct GLFWWrapper {
private:
  bool m_Initialized;

public:
  GLFWWrapper() : m_Initialized(false) {}
  inline ~GLFWWrapper() {
    if (m_Initialized)
      terminate();
  };
  void init();
  void terminate();
  inline bool isInitialized() const { return m_Initialized; };
};

struct GLFW {
private:
  static GLFWWrapper s_GLFW;

public:
  inline static bool isInitialized() { return s_GLFW.isInitialized(); }
  inline static void initialize() { s_GLFW.init(); }
  inline static void terminate() { s_GLFW.terminate(); }
};

#endif
