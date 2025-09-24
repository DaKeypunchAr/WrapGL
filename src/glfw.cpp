#include "glfw.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

void glfwErrorCallback(int errorCode, const char *description) {
  std::cout << "GLFW Error (" << errorCode << "): " << description << '\n';
}
bool GLFW::s_Initialized = false;

bool GLFW::isInitialized() { return s_Initialized; }

void GLFW::initialize() {
  glfwSetErrorCallback(glfwErrorCallback);
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("GLFW failed to initialize!");
  }
  s_Initialized = true;
}

void GLFW::terminate() {
  glfwTerminate();
  s_Initialized = false;
}
