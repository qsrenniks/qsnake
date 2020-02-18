/**************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Author: Quinton Skinner
Email: q.skinner@digipen
Date: 09/17/2019
Filename: Random.h
**************************************************************/

#ifndef RANDOM_H
#define RANDOM_H

#include "glm/glm.hpp"

namespace Random
{
float generateRandomFloat(float min = -1.0f, float max = 1.0f);
int generateRandomInt(int min = 0, int max = 1);
glm::vec3 generateRandomVector3(float min = -1.0f, float max = 1.0f);
}; // namespace Random

#endif