/*!
 * \file Level.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Level.h"
#include "IObject.h"

void Level::initialize()
{
}

void Level::render()
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [](std::shared_ptr<IObject>& object){
    object->render();
  });
}

void Level::tick(float dt)
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [=](std::shared_ptr<IObject>& object){
    object->tick(dt);
  });
}

void Level::shutdown()
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [=](std::shared_ptr<IObject>& object){
    object->shutdown();
  });
}

void Level::addObject(const std::shared_ptr<IObject> &object)
{
  object->setLevel(this);
  object->initialize();
  m_objectList.push_back(object);
}