/*!
 * \file SnakeLevel.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "SnakeLevel.h"
#include "Fruit.h"
#include "Grid.h"
#include "SnakeObject.h"

void SnakeLevel::initialize() 
{
  std::shared_ptr<SnakeObject> snake = std::make_shared<SnakeObject>(); 
  std::shared_ptr<Fruit> fruit = std::make_shared<Fruit>();

  m_grid = std::make_shared<Grid>();
  addObject(m_grid);
  addObject(fruit);
  addObject(snake);

  Level::initialize();
}