/*!
 * \file SnakeDrawCommand.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/13
 */

#ifndef SNAKEDRAWCOMMAND_H
#define SNAKEDRAWCOMMAND_H

#include "IDrawCommand.h"

class SnakeObject;

class SnakeDrawCommand : public IDrawCommand
{
public:
  virtual void bindShader() override;

  virtual void bindGeometry() override;

  virtual void draw() override;

  SnakeObject *m_snake = nullptr;
  glm::vec3 m_position = glm::vec3(0.0f);
  glm::vec4 m_color = glm::vec4(1.0f);
};

#endif