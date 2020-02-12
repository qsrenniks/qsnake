/*!
 * \file GameObjectManager.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <memory>

class IGameModeController;
class ILevel;

class GameObjectManager
{
public:
  void initialize();
  void tick(float dt);
  void render();
  void shutdown();

  void setLevel(const std::shared_ptr<ILevel> &level);
  void setGameMode(const std::shared_ptr<IGameModeController> &mode);

  static GameObjectManager& get();
  ~GameObjectManager() = default;
private:
  GameObjectManager() = default;

  std::shared_ptr<IGameModeController> m_currentMode = nullptr;
  std::shared_ptr<ILevel> m_currentLevel = nullptr;
};

#endif