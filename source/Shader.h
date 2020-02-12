/*!
 * \file    Shader.h
 * \author  Quinton Skinner
 * \par     Email: qsrenniks\@gmail.com
 * \par     2018/12/28
 */

#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
  ~Shader();

  bool recompile();
  bool compile(const char* shaderName);
  void bind();

  void setUniform(const char* uniformName, const glm::mat4& mat4R);
  void setUniform(const char* uniformName, const glm::vec2& vec2R);
  void setUniform(const char* uniformName, const glm::vec3& vec3R);
  void setUniform(const char* uniformName, const glm::vec4& vec4R);
  void setUniform(const char* uniformName, const glm::ivec2& ivec2R);
  void setUniform(const char* uniformName, const glm::ivec3& ivec3R);
  void setUniform(const char* uniformName, const glm::ivec4& ivec4R);
  void setUniform(const char* uniformName, const float& floatR);
  void setUniform(const char* uniformName, const int& intR);
  void setUniform(const char* uniformName, const double& doubleR);
  void setUniform(const char* uniformName, const bool& boolR);
  void setUniform(const char* uniformName, const glm::mat4* matArray, unsigned count);

  int getUniformIndex(const char* uniformNam) const;
  int getProgramId();

  const std::string& getShaderName() const { return m_shaderName; };

private:
  void clear();
  bool buildShader(const char* shaderName, int& shaderProgram);

  std::string m_shaderName;
  int m_shaderProgram = -1;
};

#endif