/*!
 * \file Window.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

class Window
{
public:
  void initialize();
  void shutdown();

  bool shouldClose() const;

  void beginFrame();
  void endFrame();

  double getTime();

private:
  void initializeGLFW();
  void shutdownGLFW();
  void initializeGLEW();
  void initializeOpenGL();

  GLFWwindow* m_window = nullptr;
};

#endif