/*!
 * \file SnakeDrawCommand.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/13
 */

#include "pch.h"
#include "SnakeDrawCommand.h"
#include "Shader.h"
#include "GraphicsManager.h"
#include "SnakeObject.h"

void SnakeDrawCommand::bindShader()
{
  auto shader = m_snake->getShader();
  shader->bind();
  shader->setUniform("model", glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
  shader->setUniform("pv", GraphicsManager::getCamera().getProjectionMatrix() * GraphicsManager::getCamera().getViewMatrix());
  shader->setUniform("color", m_color);
}

void SnakeDrawCommand::bindGeometry()
{
  GraphicsManager::bindQuad();
}

void SnakeDrawCommand::draw()
{
  GraphicsManager::drawQuad();
}