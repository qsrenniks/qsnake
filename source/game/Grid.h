/*!
 * \file Grid.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#ifndef GRID_H
#define GRID_H

#include "Object.h"

class Shader;

class Grid : public Object
{
public:
  virtual void initialize() override;
  virtual void render() override;

  const std::shared_ptr<Shader> &getShader() const { return m_gridShader; };
  unsigned getLineBuffer() const { return m_lineBuffer; };
  unsigned getLineCount() const { return m_lineCount; };

  glm::vec3 convertWorldPosToGridPos(const glm::vec3 &worldPos);

  const float &getCellWidth() const { return m_cellWidth; };
  const float &getCellHeight() const { return m_cellHeight; };

  const int &getGridWidth() const { return m_gridWidth; };
  const int &getGridHeight() const { return m_gridHeight; };

  const glm::vec3 &getBottomLeft() const { return m_gridBottomLeft; };

  glm::vec3 gridIDToWorldPos(int xID, int yID) const;

private:
  const unsigned m_gridHeight = 18;
  const unsigned m_gridWidth = 24;

  const float m_cellWidth = 0.4f;
  const float m_cellHeight = 0.4f;

  glm::vec3 m_gridBottomLeft;
  std::shared_ptr<Shader> m_gridShader = nullptr;
  unsigned m_lineBuffer;
  unsigned m_lineCount = 0;
};

#endif