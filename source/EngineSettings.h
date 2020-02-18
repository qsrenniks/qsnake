/*!
 * \file EngineSettings.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/17
 */

#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

class EngineSettings
{
public:
  ~EngineSettings() = default;

  void setShowGrid(bool showGrid) { m_showGrid = showGrid; };
  bool shouldShowGrid() const { return m_showGrid; };

  void setShowEditor(bool showEditor) { m_showEditor = showEditor; };
  bool shouldShowEditor() const { return m_showEditor; };

  static EngineSettings &get();

private:
  EngineSettings() = default;

  bool m_showGrid = false;
  bool m_showEditor = false;
};

#endif