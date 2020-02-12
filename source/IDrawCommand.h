/*!
 * \file IDrawCommand.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#ifndef IDRAWCOMMAND_H
#define IDRAWCOMMAND_H

class  IDrawCommand
{
public:
  virtual ~IDrawCommand() = default;
  virtual void bindShader() = 0;
  virtual void bindGeometry() = 0;
  virtual void draw() = 0;
};

#endif