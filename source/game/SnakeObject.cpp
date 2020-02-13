/*!
 * \file SnakeObject.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#include "pch.h"
#include "SnakeObject.h"
#include "SnakeLevel.h"
#include "Grid.h"
#include "GraphicsManager.h"
#include "Shader.h"

void SnakeObject::tick(float dt)
{
  std::cout << dt << std::endl;
  m_moveTimer += dt;
  if (m_moveTimer <= m_moveIncrementDuration)
  {
    return;
  }

  m_moveTimer -= m_moveIncrementDuration;

  float cellHeight = ((SnakeLevel *)getLevel())->getGrid()->getCellHeight();
  float cellWidth = ((SnakeLevel *)getLevel())->getGrid()->getCellWidth();

  glm::vec3 currentPos = getPosition();

  switch (m_currentMoveDirection)
  {
  case MovementDirection::North:
    currentPos.y += cellHeight;
    break;
  case MovementDirection::East:
    currentPos.x += cellWidth;
    break;
  case MovementDirection::South:
    currentPos.y -= cellHeight;
    break;
  case MovementDirection::West:
    currentPos.x -= cellWidth;
    break;
  default:
    break;
  }

  setPosition(currentPos);
}

void SnakeObject::onKeyPress(int key, int action)
{
  if (action != GLFW_PRESS)
  {
    return;
  }

  if (key == GLFW_KEY_W)
  {
    m_currentMoveDirection = MovementDirection::North;
  }
  else if (key == GLFW_KEY_S)
  {
    m_currentMoveDirection = MovementDirection::South;
  }

  if (key == GLFW_KEY_D)
  {
    m_currentMoveDirection = MovementDirection::East;
  }
  else if (key == GLFW_KEY_A)
  {
    m_currentMoveDirection = MovementDirection::West;
  }
}

class SnakeDrawCommand : public IDrawCommand
{
public:
  virtual void bindShader() override
  {
    auto shader = m_snake->getShader();
    shader->bind();
    shader->setUniform("model", glm::translate(glm::mat4(1.0f), m_snake->getPosition()) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
    shader->setUniform("pv", GraphicsManager::getCamera().getProjectionMatrix() * GraphicsManager::getCamera().getViewMatrix());
    shader->setUniform("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  }

  virtual void bindGeometry() override
  {
    GraphicsManager::bindQuad();
  }

  virtual void draw() override
  {
    GraphicsManager::drawQuad();
  }

  SnakeObject *m_snake = nullptr;
};

void SnakeObject::initialize()
{
  Object::initialize();
  m_snakeShader = std::make_shared<Shader>();
  m_snakeShader->compile("SnakeShader.json");

  float cellHeight = ((SnakeLevel *)getLevel())->getGrid()->getCellHeight();
  float cellWidth = ((SnakeLevel *)getLevel())->getGrid()->getCellWidth();
  glm::vec3 bottomLeft = ((SnakeLevel *)getLevel())->getGrid()->getBottomLeft();
  bottomLeft -= glm::vec3(cellHeight, cellWidth, 0.0f) * glm::vec3(3.0f, 3.0f, 0.0f);
  // bottomLeft = ((SnakeLevel *)getLevel())->getGrid()->convertWorldPosToGridPos(bottomLeft);

  setPosition(glm::vec3(glm::vec2(bottomLeft), 1.0f));
}

void SnakeObject::render()
{
  Object::render();
  std::unique_ptr<SnakeDrawCommand> command = std::make_unique<SnakeDrawCommand>();
  command->m_snake = this;
  GraphicsManager::addDrawCommand(std::move(command));
}
