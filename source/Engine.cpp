/*!
 * \file Engine.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Engine.h"

Engine &Engine::get()
{
  static Engine engine;
  return engine;
}

void Engine::initialize()
{
  Engine &engine = Engine::get();
  engine.m_window.initialize();
}

void Engine::gameLoop()
{
  Engine &engine = Engine::get();

  while (!engine.m_window.shouldClose())
  {
    engine.m_window.beginFrame();

    engine.m_window.endFrame();
  }
}

void Engine::shutdown()
{
  Engine &engine = Engine::get();
  engine.m_window.shutdown();
}
