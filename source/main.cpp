#include "pch.h"

int main()
{
  Engine::initialize();
  Engine::gameLoop();
  Engine::shutdown();
  return 0;
}