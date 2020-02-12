/*!
 * \file GraphicsManager.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#include "pch.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"
#include <algorithm>
#include "qGL.h"

GraphicsManager &GraphicsManager::get()
{
  static GraphicsManager graphics;
  return graphics;
}

void GraphicsManager::initialize()
{
  GameObjectManager::get().initialize();
  GraphicsManager &g = GraphicsManager::get();
  g.createVertexArrayObject();
  g.createQuadData();

  g.m_defaultCamera.setPerspective(false);
  g.m_defaultCamera.setOrthographicZoom(10.0f);
  g.m_defaultCamera.setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
  g.m_defaultCamera.setViewTarget(glm::vec3(0.0f, 0.0f, 0.0f));
}

void GraphicsManager::onWindowSizeChange(int width, int height)
{
  GraphicsManager& g = GraphicsManager::get();
  g.m_defaultCamera.setScreenRes(width, height);
}

void GraphicsManager::shutdown()
{
  GraphicsManager &g = GraphicsManager::get();
  g.deleteQuadData();
  g.deleteVertexArrayObject();
  GameObjectManager::get().shutdown();
}

void GraphicsManager::gatherDrawCommands()
{
  GameObjectManager::get().render();
}

void GraphicsManager::addDrawCommand(std::unique_ptr<IDrawCommand> command)
{
  GraphicsManager &graphics = GraphicsManager::get();
  graphics.m_drawCommands.emplace_back(std::move(command));
}

void GraphicsManager::renderDrawCommands()
{
  GraphicsManager &graphics = GraphicsManager::get();
  bindVertexArray(graphics.m_vertexArrayObject);

  std::for_each(graphics.m_drawCommands.begin(), graphics.m_drawCommands.end(), [](const std::unique_ptr<IDrawCommand> &command) {
    command->bindShader();
    command->bindGeometry();
    command->draw();
  });

  graphics.m_drawCommands.clear();
}

void GraphicsManager::bindQuad()
{
  GraphicsManager &g = GraphicsManager::get();

  bindBuffer(GL_ARRAY_BUFFER, g.m_quadData.m_positionsBuffer);
  enableVertexAttribArray(0);
  setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  bindBuffer(GL_ARRAY_BUFFER, g.m_quadData.m_textureBuffer);
  enableVertexAttribArray(1);
  setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  bindBuffer(GL_ELEMENT_ARRAY_BUFFER, g.m_quadData.m_elementBuffer);
}

void GraphicsManager::drawQuad()
{
  GraphicsManager &g = GraphicsManager::get();
  drawElements(GL_TRIANGLES, g.m_quadData.m_indicesCount, GL_UNSIGNED_INT, nullptr);
}

void GraphicsManager::createQuadData()
{
  static const glm::vec3 vertexPositions[] = {
      {-0.5f, -0.5f, 0.0f},
      {0.5f, -0.5f, 0.0f},
      {0.5f, 0.5f, 0.0f},
      {-0.5f, 0.5f, 0.0f}};

  static const glm::vec2 uvs[] = {
      {0.0f, 0.0f},
      {1.0f, 0.0f},
      {1.0f, 1.0f},
      {0.0f, 1.0f}};

  static const unsigned elementBuffer[] = {
      0, 1, 3,
      1, 2, 3};

  GraphicsManager &g = GraphicsManager::get();

  createBuffer(g.m_quadData.m_positionsBuffer);
  createBuffer(g.m_quadData.m_textureBuffer);
  createBuffer(g.m_quadData.m_elementBuffer);

  setBufferData(g.m_quadData.m_positionsBuffer, sizeof(glm::vec3) * 4, vertexPositions, GL_STATIC_DRAW);
  setBufferData(g.m_quadData.m_textureBuffer, sizeof(glm::vec2) * 4, uvs, GL_STATIC_DRAW);
  setBufferData(g.m_quadData.m_elementBuffer, sizeof(unsigned) * 6, elementBuffer, GL_STATIC_DRAW);
}

void GraphicsManager::deleteQuadData()
{
  GraphicsManager &g = GraphicsManager::get();
  deleteBuffer(g.m_quadData.m_positionsBuffer);
  deleteBuffer(g.m_quadData.m_textureBuffer);
  deleteBuffer(g.m_quadData.m_elementBuffer);
}

void GraphicsManager::createVertexArrayObject()
{
  createVertexArray(m_vertexArrayObject);
}

void GraphicsManager::deleteVertexArrayObject()
{
  deleteVertexArray(m_vertexArrayObject);
}

Camera &GraphicsManager::getCamera()
{
  return GraphicsManager::get().m_defaultCamera;
}
