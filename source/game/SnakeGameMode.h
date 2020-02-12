/*!
 * \file SnakeGameMode.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef SNAKEGAMEMODE_H
#define SNAKEGAMEMODE_H

#include "IGameModeController.h"
#include <memory>

class SnakeLevel;

class SnakeGameMode : public IGameModeController
{
public:
  virtual void initialize();
  virtual void render();
  virtual void tick(float dt);
  virtual void shutdown();
private:
  std::shared_ptr<SnakeLevel> m_testLevel = nullptr;
};

#endif