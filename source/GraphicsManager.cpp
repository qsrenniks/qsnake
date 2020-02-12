/*!
 * \file GraphicsManager.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"

GraphicsManager &GraphicsManager::get()
{
  static GraphicsManager graphics;
  return graphics;
}

void GraphicsManager::initialize()
{
  GameObjectManager::get().initialize();
}

void GraphicsManager::shutdown()
{
  GameObjectManager::get().shutdown();
}

void GraphicsManager::gatherDrawCommands()
{
  GameObjectManager::get().render();
}

void GraphicsManager::renderDrawCommands()
{
}
