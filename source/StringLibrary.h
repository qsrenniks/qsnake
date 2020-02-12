/*!
 * \file StringLibrary.h
 * \author Quinton Skinner
 * \par Email: qsrenniks\@gmail.com
 * \par 2020/02/12
 */

#ifndef STRINGLIBRARY_H
#define STRINGLIBRARY_H

namespace StringLibrary
{
static const char *dataDir = DATA_DIR;

static const std::string textureDir = dataDir + std::string("textures/");
static const std::string shaderDir = dataDir + std::string("shaders/");
}; // namespace StringLibrary

#endif