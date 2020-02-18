/**************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Author: Quinton Skinner
Email: q.skinner@digipen
Date: 09/17/2019
Filename: Random.cpp
**************************************************************/

#include "pch.h"
#include "Random.h"
#include <random>

static std::random_device dev;
static std::mt19937 rng(dev());

float Random::generateRandomFloat(float min, float max)
{
  if (min > max)
  {
    std::swap(min, max);
  }

  std::uniform_real_distribution<float> dist(min, max);
  return dist(rng);
}

int Random::generateRandomInt(int min, int max)
{
  if (min > max)
  {
    std::swap(min, max);
  }

  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}

glm::vec3 Random::generateRandomVector3(float min, float max)
{
  glm::vec3 gen;
  gen.x = generateRandomFloat(min, max);
  gen.y = generateRandomFloat(min, max);
  gen.z = generateRandomFloat(min, max);
  return gen;
}