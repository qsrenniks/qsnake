/*!
 * \file Engine.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Engine.h"
#include "EngineSettings.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "cxxopts.h"

Engine &Engine::get()
{
  static Engine engine;
  return engine;
}

static void processCommandLineArgs(int argc, char **argv)
{
  cxxopts::Options options("QSnake", "open source snake game");

  options.add_options()("g,grid", "show the grid the snake runs along")("e,editor", "show engine editor");

  auto result = options.parse(argc, argv);

  EngineSettings::get().setShowGrid(result["grid"].as<bool>());
  EngineSettings::get().setShowEditor(result["editor"].as<bool>());
}

void Engine::initialize(int argc, char **argv)
{
  processCommandLineArgs(argc, argv);
  Engine &engine = Engine::get();
  engine.m_window.initialize();
  GraphicsManager::initialize();
}

void Engine::gameLoop()
{
  Engine &engine = Engine::get();
  GraphicsManager &graphics = GraphicsManager::get();

  double previousTime = engine.m_window.getTime();
  while (!engine.m_window.shouldClose())
  {
    double currentTime = engine.m_window.getTime();
    double elapsedTime = currentTime - previousTime;

    if (elapsedTime >= engine.m_tickRate)
    {
      engine.m_deltaTime = float(currentTime - previousTime);
      previousTime = currentTime;
      engine.m_window.beginFrame();
      GameObjectManager::get().tick(engine.m_deltaTime);
      graphics.gatherDrawCommands();
      graphics.renderDrawCommands();
      engine.m_window.endFrame();
    }
    else
    {
      std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(engine.m_tickRate - elapsedTime));
    }
  }
}

void Engine::shutdown()
{
  Engine &engine = Engine::get();
  GraphicsManager::shutdown();
  engine.m_window.shutdown();
}
