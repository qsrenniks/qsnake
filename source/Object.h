/*!
 * \file Object.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "IObject.h"

class ILevel;

class Object : public IObject
{
public:
  virtual void initialize() override;
  virtual void tick(float dt) override;
  virtual void render() override;
  virtual void shutdown() override;

  virtual ILevel *getLevel() const override { return m_parentLevel; };
  virtual void setLevel(ILevel *level) override { m_parentLevel = level; };

  virtual const glm::vec3 &getPosition() const override { return m_position; };
  virtual void setPosition(const glm::vec3 &position) override { m_position = position; };

private:
  glm::vec3 m_position = glm::vec3(0.0f);
  ILevel *m_parentLevel = nullptr;
};

#endif