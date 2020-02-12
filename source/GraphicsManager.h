/*!
 * \file GraphicsManager.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/11
 */

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class GraphicsManager
{
public:
  static GraphicsManager& get();

  static void initialize();
  static void shutdown();

  static void gatherDrawCommands();
  static void renderDrawCommands();

  ~GraphicsManager() = default;
private:
  GraphicsManager() = default;
};

#endif