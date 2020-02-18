/*!
 * \file EngineSettings.cpp
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/17
 */

#include "pch.h"
#include "EngineSettings.h"

EngineSettings &EngineSettings::get()
{
  static EngineSettings settings;
  return settings;
}