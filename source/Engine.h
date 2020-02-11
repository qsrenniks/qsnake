/*!
 * \file Engine.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

class Engine
{
public:
  static Engine& get();

  static void initialize();
  static void gameLoop();
  static void shutdown();

  ~Engine() = default;
private:

  Window m_window;

  Engine() = default;
};

#endif