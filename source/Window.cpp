/*!
 * \file Window.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Window.h"
#include "EngineSettings.h"
#include <iostream>
#include "GraphicsManager.h"
#include "PropertyInspector.h"
#include "GameObjectManager.h"

void errorCallback(int error, char const *description)
{
}

void frameBufferSizeCallback(GLFWwindow *pwin, int width, int height)
{
  GraphicsManager::onWindowSizeChange(width, height);
  // GraphicsManager::get().onWindowSizeChange(width, height);
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *pwin, int key, int scancode, int action, int mod)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(pwin, true);
  }

  GameObjectManager::get().onKeyPress(key, action);
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

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  const char *glsl_version = "#version 410 core";
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGuiIO *io = &ImGui::GetIO();
  io->IniFilename = nullptr;
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::GetStyle().FrameRounding = 0.0f;
  ImGui::GetStyle().ScrollbarRounding = 0.0f;
  ImGui::GetStyle().TabRounding = 0.0f;
  ImGui::GetStyle().WindowRounding = 0.0f;

  // console bg 0.24f, 0.27f, 0.22f
  // title bg 0.30f, 0.35f, 0.27f
  // scroll bg 0.35f, 0.42f, 0.31f

  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.43f, 0.50f, 0.43f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.22f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.22f, 0.17f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.07f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.56f, 0.27f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.88f, 0.52f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.30f, 0.25f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.50f, 0.43f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.75f, 0.40f, 1.00f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.75f, 0.40f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.58f, 0.35f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.68f, 0.41f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.15f, 0.10f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.42f, 0.26f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.35f, 0.43f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.00f, 0.70f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.60f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.30f, 0.35f, 0.27f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
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

  if (EngineSettings::get().shouldShowEditor())
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    GameObjectManager::get().inspectGameObjects(PropertyInspector());
  }
}

void Window::endFrame()
{
  if (EngineSettings::get().shouldShowEditor())
  {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
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

  frameBufferSizeCallback(m_window, 800, 600);

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
