/*!
 * \file Object.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef OBJECT_H
#define OBJECT_H

class Object : public IObject
{
public:
  virtual void initialize() override;
  virtual void tick(float dt) override;
  virtual void render() override;
  virtual void shutdown() override;

  virtual const glm::ivec2 &getPosition() const override { return m_position; };
  virtual void setPosition(const glm::ivec2 &position) override { m_position = position; };

private:
  glm::ivec2 m_position;
};

#endif