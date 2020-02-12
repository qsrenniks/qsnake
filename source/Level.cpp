/*!
 * \file Level.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Level.h"

void Level::initialize()
{
}

void Level::render()
{
}

void Level::tick(float dt)
{
}

void Level::shutdown()
{
}

void Level::addObject(const std::shared_ptr<IObject> &object)
{
  m_objectList.push_back(object);
}