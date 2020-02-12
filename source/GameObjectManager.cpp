/*!
 * \file GameObjectManager.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "GameObjectManager.h"
#include "ILevel.h"
#include "IGameModeController.h"

GameObjectManager &GameObjectManager::get()
{
  static GameObjectManager gameObjectManager;
  return gameObjectManager;
}

void GameObjectManager::setLevel(const std::shared_ptr<ILevel> &level)
{
  if (m_currentLevel)
  {
    m_currentLevel->shutdown();
  }

  m_currentLevel = level;
  m_currentLevel->initialize();
}

void GameObjectManager::setGameMode(const std::shared_ptr<IGameModeController> &mode)
{
  if (m_currentMode)
  {
    m_currentMode->shutdown();
  }

  m_currentMode = mode;
  m_currentMode->initialize();
}

void GameObjectManager::initialize()
{
}

void GameObjectManager::tick(float dt)
{
  if (m_currentMode)
  {
    m_currentMode->tick(dt);
  }

  if (m_currentLevel)
  {
    m_currentLevel->tick(dt);
  }
}

void GameObjectManager::render()
{
  if (m_currentMode)
  {
    m_currentMode->render();
  }

  if (m_currentLevel)
  {
    m_currentLevel->render();
  }
}

void GameObjectManager::shutdown()
{
  
}
