/*!
 * \file Grid.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#include "pch.h"
#include "Grid.h"
#include "qGL.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "EngineSettings.h"

void Grid::initialize()
{
  Object::initialize();

  const glm::vec3 fullSize = glm::vec3(m_gridWidth * m_cellWidth, m_gridHeight * m_cellHeight, 0.0f);
  const glm::vec3 center = -glm::vec3(m_cellWidth * m_gridWidth, m_cellHeight * m_gridHeight, 0.0f) / 2.0f;
  m_gridBottomLeft = -center;

  std::vector<glm::vec3> lines;

  for (unsigned i = 0; i < m_gridWidth + 1; ++i)
  {
    lines.push_back(center + glm::vec3(m_cellWidth * i, 0.0f, 0.0f));
    lines.push_back(center + glm::vec3(m_cellWidth * i, fullSize.y, 0.0f));
  }

  for (unsigned j = 0; j < m_gridHeight + 1; ++j)
  {
    lines.push_back(center + glm::vec3(0.0f, m_cellHeight * j, 0.0f));
    lines.push_back(center + glm::vec3(fullSize.x, m_cellHeight * j, 0.0f));
  }

  createBuffer(m_lineBuffer);
  setBufferData(m_lineBuffer, sizeof(glm::vec3) * unsigned(lines.size()), lines.data(), GL_STATIC_DRAW);
  m_lineCount = lines.size();

  m_gridShader = std::make_shared<Shader>();
  m_gridShader->compile("PassThroughShader.json");
}

class GridDrawCommand : public IDrawCommand
{
public:
  virtual void bindShader() override
  {
    auto camera = GraphicsManager::getCamera();
    auto shader = m_grid->getShader();
    shader->bind();
    shader->setUniform("model", glm::mat4(1.0f));
    shader->setUniform("pv", camera.getProjectionMatrix() * camera.getViewMatrix());
  }

  virtual void bindGeometry() override
  {
    bindBuffer(GL_ARRAY_BUFFER, m_grid->getLineBuffer());
    enableVertexAttribArray(0);
    setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  }

  virtual void draw() override
  {
    drawArrays(GL_LINES, 0, m_grid->getLineCount());
  }
  Grid *m_grid = nullptr;
};

void Grid::render()
{
  Object::render();

  if (EngineSettings::get().shouldShowGrid())
  {
    std::unique_ptr<GridDrawCommand> drawCommand = std::make_unique<GridDrawCommand>();
    drawCommand->m_grid = this;
    GraphicsManager::addDrawCommand(std::move(drawCommand));
  }
}

glm::vec3 Grid::convertWorldPosToGridPos(const glm::vec3 &worldPos)
{
  int x = int(glm::round(worldPos.x / m_cellWidth));
  int y = int(glm::round(worldPos.y / m_cellHeight));

  return glm::vec3(float(x), float(y), 0.0f);
}

glm::vec3 Grid::gridIDToWorldPos(int xID, int yID) const
{
  glm::vec3 startPos = glm::vec3(getCellWidth() * xID, getCellHeight() * yID, 0.0f);
  startPos -= m_gridBottomLeft;
  return startPos;
}
