/*!
 * \file ILevel.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef ILEVEL_H
#define ILEVEL_H

#include <memory>

class IObject;
class PropertyInspector;

class ILevel
{
public:
  virtual ~ILevel() = default;
  virtual void initialize() = 0;
  virtual void render() = 0;
  virtual void tick(float dt) = 0;
  virtual void shutdown() = 0;

  virtual void addObject(const std::shared_ptr<IObject>& object) = 0;
  virtual void onKeyPress(int key, int action) = 0;

  virtual void inspect(PropertyInspector& inspector) = 0;

};

#endif