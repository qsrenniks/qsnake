/*!
 * \file Level.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "Level.h"
#include "IObject.h"
#include "PropertyInspector.h"

void Level::initialize()
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [](std::shared_ptr<IObject> &object) {
    object->initialize();
  });
}

void Level::render()
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [](std::shared_ptr<IObject> &object) {
    object->render();
  });
}

void Level::tick(float dt)
{
  for(unsigned i = 0; i < unsigned(m_objectList.size()); ++i)
  {
    m_objectList[i]->tick(dt);
  }
}

void Level::shutdown()
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [=](std::shared_ptr<IObject> &object) {
    object->shutdown();
  });
}

void Level::addObject(const std::shared_ptr<IObject> &object)
{
  object->setLevel(this);
  m_objectList.push_back(object);
}

void Level::inspect(PropertyInspector &inspector)
{
  int i = 0;
  std::for_each(m_objectList.begin(), m_objectList.end(), [&](std::shared_ptr<IObject> &object) {
    ++i;
    std::string objectName = "object " + std::to_string(i);
    if (inspector.beginTree(objectName.c_str(), object.get()))
    {
      glm::vec3 position = object->getPosition();
      if (inspector.editVector3("position", position))
      {
        object->setPosition(position);
      }
      inspector.endTree();
    }
  });
}

void Level::onKeyPress(int key, int action)
{
  std::for_each(m_objectList.begin(), m_objectList.end(), [=](std::shared_ptr<IObject> &object) {
    object->onKeyPress(key, action);
  });
}