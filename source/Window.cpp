/*!
 * \file Window.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Window.h"
#include <iostream>

void errorCallback(int error, char const *description)
{
}

void frameBufferSizeCallback(GLFWwindow *pwin, int width, int height)
{
  // GraphicsManager::get().onWindowSizeChange(width, height);
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *pwin, int key, int scancode, int action, int mod)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(pwin, true);
  }
}

void mouseButtonCallback(GLFWwindow *pwin, int button, int action, int mod)
{
}

void mousePositionCallback(GLFWwindow *pwin, double xpos, double ypos)
{
}

void mouseScrollCallback(GLFWwindow *pwin, double xOffset, double yOffset)
{
}

void APIENTRY openGLDebug(GLenum source, GLenum type, GLuint id,
                          GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
  switch (severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
  case GL_DEBUG_SEVERITY_MEDIUM:
    std::cout << message << std::endl;
    break;
  default:
    break;
  }
}

void Window::initialize()
{
  initializeGLFW();
  initializeGLEW();
  initializeOpenGL();
}

void Window::shutdown()
{
  shutdownGLFW();
}

void Window::beginFrame()
{
  glfwSwapBuffers(m_window);
  glfwPollEvents();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glStencilMask(0xFF);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::endFrame()
{
}

void Window::initializeGLFW()
{
  if (!glfwInit())
  {
    std::cout << "Cannot initialize glfw." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  glfwSetErrorCallback(errorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  // glfwWindowHint(GLFW_SAMPLES, 4);

  // GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
  m_window = glfwCreateWindow(800, 600, "qsnake", nullptr, nullptr);

  if (m_window == nullptr)
  {
    std::cout << "GLFW is unable to create an opengl context." << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
  glfwSetKeyCallback(m_window, keyCallback);
  glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
  glfwSetCursorPosCallback(m_window, mousePositionCallback);
  glfwSetScrollCallback(m_window, mouseScrollCallback);
  glfwMakeContextCurrent(m_window);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::shutdownGLFW()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Window::initializeGLEW()
{
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << "unable to intialize GLEW, error: " << glewGetErrorString(err) << std::endl;
    std::exit(EXIT_FAILURE);
  }
  if (GLEW_VERSION_4_5)
  {
    std::cout << "Using Glew: " << glewGetString(GLEW_VERSION) << std::endl;
  }
}

void Window::initializeOpenGL()
{
  glLineWidth(3.0f);
  glPointSize(8.0f);

  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);

  // glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifndef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(openGLDebug, this);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool Window::shouldClose() const
{
  return bool(glfwWindowShouldClose(m_window));
}

double Window::getTime()
{
  return glfwGetTime();
}
