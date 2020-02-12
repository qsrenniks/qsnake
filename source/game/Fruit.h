/*!
 * \file Fruit.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef FRUIT_H
#define FRUIT_H

#include "Object.h"
#include <memory>

class Shader;

class Fruit : public Object
{
public:
  virtual void initialize() override;
  virtual void render() override;

  const std::shared_ptr<Shader> &getShader() const { return m_testShader; };

private:
  std::shared_ptr<Shader> m_testShader = nullptr;
};

#endif