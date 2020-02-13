/*!
 * \file IGameModeController.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef IGAMEMODECONTROLLER_H
#define IGAMEMODECONTROLLER_H

class IGameModeController
{
public:
  virtual ~IGameModeController() = default;
  virtual void initialize() = 0;
  virtual void render() = 0;
  virtual void tick(float dt) = 0;
  virtual void shutdown() = 0;
  virtual void onKeyPress(int key, int action) = 0;
};

#endif