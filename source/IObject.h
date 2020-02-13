/*!
 * \file IObject.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef IOBJECT_H
#define IOBJECT_H

class ILevel;

class IObject
{
public:
  virtual ~IObject() = default;
  virtual void initialize() = 0;
  virtual void tick(float dt) = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;

  virtual ILevel* getLevel() const = 0;
  virtual void setLevel(ILevel* level) = 0;

  virtual const glm::vec3& getPosition() const = 0;
  virtual void setPosition(const glm::vec3& position) = 0;

  virtual void onKeyPress(int key, int action)= 0;
};

#endif