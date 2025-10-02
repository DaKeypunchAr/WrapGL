#ifndef WRAPGL_GLFW_HPP
#define WRAPGL_GLFW_HPP

enum class OpenGLProfile { CORE, COMPATABILITY, ES };

struct GLFW {
private:
  static bool s_Initialized;

public:
  static bool isInitialized();
  static void initialize();
  static void terminate();
};

#endif
