#include "pch.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include "game/SnakeGameMode.h"
#include "EngineSettings.h"

int main(int argc, char** argv)
{
  Engine::initialize(argc, argv);

  GameObjectManager::get().setGameMode(std::make_shared<SnakeGameMode>());

  Engine::gameLoop();
  Engine::shutdown();
  return 0;
}