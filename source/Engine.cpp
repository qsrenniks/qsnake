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
}

void Engine::gameLoop()
{
}

void Engine::shutdown()
{
}
