#include "wrapgl/glfw.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

void glfwErrorCallback(int errorCode, const char *description);

void glfwErrorCallback(int errorCode, const char *description) {
  std::cout << "GLFW Error (" << errorCode << "): " << description << '\n';
}

GLFWWrapper GLFW::s_GLFW;

void GLFWWrapper::init() {
  if (m_Initialized) {
    throw std::runtime_error(
        "GLFW is already initialized! Only initialize after terminating!");
  }
  glfwSetErrorCallback(glfwErrorCallback);
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("GLFW failed to initialize!");
  }
  m_Initialized = true;
}

void GLFWWrapper::terminate() {
  glfwTerminate();
  m_Initialized = false;
}
