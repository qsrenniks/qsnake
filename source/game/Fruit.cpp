/*!
 * \file Fruit.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#include "pch.h"
#include "Fruit.h"
#include "GraphicsManager.h"
#include "DrawCommand.h"
#include "Shader.h"

class FruitDrawCommand : public DrawCommand
{
public:
  virtual void bindShader() override
  {
    auto shader = m_fruitObject->getShader();
    shader->bind();
    shader->setUniform("model", glm::mat4(1.0f));
    shader->setUniform("pv", GraphicsManager::getCamera().getProjectionMatrix() * GraphicsManager::getCamera().getViewMatrix());
  };

  virtual void bindGeometry() override
  {
    GraphicsManager::bindQuad();
  };

  virtual void draw() override
  {
    GraphicsManager::drawQuad();
  };

  Fruit* m_fruitObject = nullptr;
};

void Fruit::initialize()
{
  Object::initialize();
  m_testShader = std::make_shared<Shader>();
  m_testShader->compile("PassThroughShader.json");
}

void Fruit::render()
{
  Object::render();

  std::unique_ptr<FruitDrawCommand> fruitCommand = std::make_unique<FruitDrawCommand>();
  fruitCommand->m_fruitObject = this;
  GraphicsManager::addDrawCommand(std::move(fruitCommand));
}