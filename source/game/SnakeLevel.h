/*!
 * \file SnakeLevel.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef SNAKELEVEL_H
#define SNAKELEVEL_H

#include "Level.h"

class Grid;

class SnakeLevel : public Level
{
public:
  virtual void initialize() override;

  std::shared_ptr<Grid> getGrid() const { return m_grid; };

private:
  std::shared_ptr<Grid> m_grid = nullptr;
};

#endif