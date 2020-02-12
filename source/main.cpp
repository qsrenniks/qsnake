#include "pch.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include "game/SnakeGameMode.h"

int main()
{
  Engine::initialize();

  GameObjectManager::get().setGameMode(std::make_shared<SnakeGameMode>());

  Engine::gameLoop();
  Engine::shutdown();
  return 0;
}