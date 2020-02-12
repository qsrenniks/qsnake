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

private:
  std::vector<std::shared_ptr<IObject>> m_objectList;
};

#endif