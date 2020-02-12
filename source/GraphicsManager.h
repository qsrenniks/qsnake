/*!
 * \file GraphicsManager.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <vector>
#include "IDrawCommand.h"
#include <memory>
#include "Camera.h"

class QuadData
{
public:
  unsigned m_indicesCount = 6;
  unsigned m_positionsBuffer;
  unsigned m_textureBuffer;
  unsigned m_elementBuffer;
};

class GraphicsManager
{
public:
  static GraphicsManager& get();

  static void initialize();
  static void shutdown();

  static void gatherDrawCommands();
  static void renderDrawCommands();

  static void addDrawCommand(std::unique_ptr<IDrawCommand> command);

  ~GraphicsManager() = default;

  static void bindQuad();
  static void drawQuad();

  static Camera& getCamera();

  static void onWindowSizeChange(int width, int height);
private:
  GraphicsManager() = default;

  void createQuadData();
  void deleteQuadData();

  void createVertexArrayObject();
  void deleteVertexArrayObject();

  unsigned m_vertexArrayObject;

  std::vector<std::unique_ptr<IDrawCommand>> m_drawCommands;

  Camera m_defaultCamera;

  QuadData m_quadData;
};

#endif