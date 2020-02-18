/*!
 * \file Level.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "ILevel.h"
#include <vector>

class IObject;

class Level : public ILevel
{
public:
  virtual void initialize() override;
  virtual void render() override;
  virtual void tick(float dt) override;
  virtual void shutdown() override;

  virtual void addObject(const std::shared_ptr<IObject> &object) override;
  virtual void onKeyPress(int key, int action) override;
  virtual void inspect(PropertyInspector& inspector) override;

  template<typename tObject>
  void getObjects(std::vector<std::shared_ptr<tObject>>& objects)
  {
    std::for_each(m_objectList.begin(), m_objectList.end(), [&](const std::shared_ptr<IObject>& object){
      if(auto check = std::dynamic_pointer_cast<tObject>(object))
      {
        objects.push_back(check);
      }
    });
  }

private:
  std::vector<std::shared_ptr<IObject>> m_objectList;
};

#endif