/*!
 * \file IObject.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef IOBJECT_H
#define IOBJECT_H

class IObject
{
public:
  virtual void initialize() = 0;
  virtual void tick(float dt) = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;

  virtual const glm::ivec2& getPosition() const = 0;
  virtual void setPosition(const glm::ivec2& position) = 0;
};

#endif