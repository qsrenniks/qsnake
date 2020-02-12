/*!
 * \file SnakeLevel.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "SnakeLevel.h"
#include "Fruit.h"

SnakeLevel::initialize() 
{
  std::shared_ptr<Fruit> fruit = std::make_shared<Fruit>();
  addObject(fruit);
}