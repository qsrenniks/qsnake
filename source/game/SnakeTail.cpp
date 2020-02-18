/*!
 * \file SnakeTail.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/13
 */

#include "pch.h"
#include "SnakeTail.h"
#include "SnakeDrawCommand.h"
#include "GraphicsManager.h"

void SnakeTail::render()
{
  Object::render();

  std::unique_ptr<SnakeDrawCommand> command = std::make_unique<SnakeDrawCommand>();
  command->m_snake = m_head;
  command->m_position = getPosition();
  command->m_color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
  GraphicsManager::addDrawCommand(std::move(command));
}