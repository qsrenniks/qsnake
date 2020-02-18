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
#include "Fruit.h"
#include "SnakeDrawCommand.h"
#include "SnakeTail.h"

void SnakeObject::tick(float dt)
{
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

  moveChildren();
  setPosition(currentPos);

  if(didHitFruit())
  {
    addChild();
  }

}

void SnakeObject::moveChildren()
{
  glm::vec3 nextPos = glm::vec3(getPosition().x, getPosition().y, 0.5f);
  SnakeTail* node = m_head;
  while(node)
  {
    glm::vec3 temp = node->getPosition();
    node->setPosition(nextPos);
    nextPos = temp;
    node = node->getNext();
  }
}

void SnakeObject::addChild()
{
  std::shared_ptr<SnakeTail> newTail = std::make_shared<SnakeTail>();

  if(m_tail)
  {
    m_tail->setNext(newTail.get());
  }
  else
  {
    m_head = newTail.get();
  }

  getLevel()->addObject(newTail);
  m_tail = newTail.get();
  m_tail->setPosition(glm::vec3(getPosition().x, getPosition().y, 0.5f));
  m_tail->setHead(this);
}

bool SnakeObject::didHitFruit() const
{
  bool didHit = false;

  auto level = ((SnakeLevel *)getLevel());

  for (const auto &fruit : m_fruitObjects)
  {
    if (level->getGrid()->convertWorldPosToGridPos(fruit->getPosition()) == level->getGrid()->convertWorldPosToGridPos(getPosition()))
    {
      didHit = true;
      fruit->respawn();
      break;
    }
  }

  return didHit;
}

void SnakeObject::onKeyPress(int key, int action)
{
  if (action != GLFW_PRESS)
  {
    return;
  }

  if (key == GLFW_KEY_W && m_currentMoveDirection != MovementDirection::South)
  {
    m_currentMoveDirection = MovementDirection::North;
  }
  else if (key == GLFW_KEY_S && m_currentMoveDirection != MovementDirection::North)
  {
    m_currentMoveDirection = MovementDirection::South;
  }

  if (key == GLFW_KEY_D && m_currentMoveDirection != MovementDirection::West)
  {
    m_currentMoveDirection = MovementDirection::East;
  }
  else if (key == GLFW_KEY_A && m_currentMoveDirection != MovementDirection::East)
  {
    m_currentMoveDirection = MovementDirection::West;
  }
}

void SnakeObject::initialize()
{
  Object::initialize();
  m_snakeShader = std::make_shared<Shader>();
  m_snakeShader->compile("SnakeShader.json");

  int startX = 1;
  int startY = 1;

  auto level = ((SnakeLevel *)getLevel());

  setPosition(glm::vec3(glm::vec2(level->getGrid()->gridIDToWorldPos(startX, startY)), 1.0f));

  level->getObjects<Fruit>(m_fruitObjects);
}

void SnakeObject::render()
{
  Object::render();
  std::unique_ptr<SnakeDrawCommand> command = std::make_unique<SnakeDrawCommand>();
  command->m_snake = this;
  command->m_position = getPosition();
  command->m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  GraphicsManager::addDrawCommand(std::move(command));
}
