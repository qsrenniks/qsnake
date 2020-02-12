#include "pch.h"
#include "Shader.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include "Engine.h"
#include <any>
#include "StringLibrary.h"

enum ShaderType
{
  eVertex = GL_VERTEX_SHADER,
  eFragment = GL_FRAGMENT_SHADER,
  eTessControl = GL_TESS_CONTROL_SHADER,
  eTessEvaluation = GL_TESS_EVALUATION_SHADER,
  eGeometry = GL_GEOMETRY_SHADER,
  eCompute = GL_COMPUTE_SHADER,
  eInvalid = 0
};

static bool getShaderValidationStatus(std::string &output, int shaderProgram)
{
  glValidateProgram(shaderProgram);
  GLint shaderStatus;
  glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &shaderStatus);
  if (shaderStatus == GL_FALSE)
  {
    std::cout << "Error: shader program cannot be validated." << std::endl;
    GLint log_len;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0)
    {
      char *log_str = new char[log_len];
      GLsizei written_log_len;
      glGetProgramInfoLog(shaderProgram,
                          log_len,
                          &written_log_len,
                          log_str);

      output = log_str;
      delete[] log_str;
    }
    return false;
  }
  return true;
}

static bool getShaderCompileStatus(std::string &output, int shader)
{
  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (GL_FALSE == result)
  {
    GLint log_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0)
    {
      char *error_log_str = new GLchar[log_len];
      GLsizei written_log_len;
      glGetShaderInfoLog(shader, log_len, &written_log_len, error_log_str);
      output = error_log_str;
      delete[] error_log_str;
    }
    return GL_FALSE;
  }
  return GL_TRUE;
}

static bool getShaderLinkStatus(std::string &output, int shaderProgram)
{
  GLint result;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
  if (result == GL_FALSE)
  {
    GLint log_len;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0)
    {
      GLchar *error_log_str = new GLchar[log_len];
      GLsizei written_log_len;
      glGetProgramInfoLog(shaderProgram,
                          log_len,
                          &written_log_len,
                          error_log_str);
      output = error_log_str;
      delete[] error_log_str;
    }
    return GL_FALSE;
  }
  return GL_TRUE;
}

static void getShaderSource(std::string &source, const std::string &fileName)
{
  if (fileName.empty())
  {
    return;
  }

  std::ifstream sourceFile;
  sourceFile.open(StringLibrary::shaderDir + "programs/" + fileName);

  if (!sourceFile)
  {
    std::cout << "unable to load shader program: " << fileName << std::endl;
    return;
  }

  std::stringstream sourceStream;
  sourceStream << sourceFile.rdbuf();
  source = sourceStream.str();
  return;
}

enum CompileState
{
  eSuccess,
  eFailed,
  eValid
};

static const char *shaderTypeToString(const ShaderType &type)
{
  switch (type)
  {
  case ShaderType::eVertex:
    return "vertex shader";
    break;
  case ShaderType::eFragment:
    return "fragment shader";
    break;
  case ShaderType::eGeometry:
    return "geometry shader";
    break;
  case ShaderType::eTessControl:
    return "tesselation control shader";
    break;
  case ShaderType::eTessEvaluation:
    return "tesselation evaluation shader";
    break;
  case ShaderType::eCompute:
    return "vertex shader";
    break;
  default:
  case ShaderType::eInvalid:
    return "invalid shader";
    break;
  }
}

static CompileState compileShaderProgram(const char *shaderName, ShaderType type, const std::string &source, int &program)
{
  if (type == ShaderType::eInvalid)
  {
    return eFailed;
  }

  if (source.empty())
  {
    return eValid;
  }

  program = glCreateShader(GLenum(type));

  const char *sourceData = source.c_str();
  glShaderSource(program, 1, reinterpret_cast<const GLchar *const *>(&sourceData), nullptr);

  glCompileShader(program);

  std::string outputLog;
  bool status = getShaderCompileStatus(outputLog, program);

  if (status == false)
  {
    std::cout << "problem compiling shader: " << shaderName << ", in " << shaderTypeToString(type) << std::endl
              << outputLog << std::endl;
    return eFailed;
  }

  return eSuccess;
}

Shader::~Shader()
{
  clear();
}

bool Shader::recompile()
{
  if (m_shaderName.empty())
  {
    return false;
  }

  int shaderProgram = -1;
  bool success = buildShader(m_shaderName.c_str(), shaderProgram);

  if (success)
  {
    clear();
    m_shaderProgram = shaderProgram;
  }
  return success;
}

void Shader::clear()
{
  if (m_shaderProgram != -1)
  {
    glUseProgram(0);
    glDeleteProgram(m_shaderProgram);
  }
}

bool Shader::buildShader(const char *shaderName, int &shaderProgram)
{
  std::string shaderPath = StringLibrary::shaderDir + shaderName;
  std::ifstream shaderFile;
  shaderFile.open(shaderPath);
  if (!shaderFile)
  {
    std::cout << "unable to open shader file: " << shaderPath << std::endl;
    ;
    return false;
  }

  json shaderJson;
  shaderFile >> shaderJson;

  std::string vertShaderName = shaderJson["vert"].get<std::string>();
  std::string fragShaderName = shaderJson["frag"].get<std::string>();
  std::string tessControlName = shaderJson["tesc"].get<std::string>();
  std::string tessEvalName = shaderJson["tese"].get<std::string>();
  std::string geometryName = shaderJson["geom"].get<std::string>();
  std::string computeName = shaderJson["comp"].get<std::string>();

  std::string vertShaderSource;
  std::string fragShaderSource;
  std::string tessControlSource;
  std::string tessEvalSource;
  std::string geometrySource;
  std::string computeSource;

  getShaderSource(vertShaderSource, vertShaderName);
  getShaderSource(fragShaderSource, fragShaderName);
  getShaderSource(tessControlSource, tessControlName);
  getShaderSource(tessEvalSource, tessEvalName);
  getShaderSource(geometrySource, geometryName);
  getShaderSource(computeSource, computeName);

  int vertex = -1;
  int fragment = -1;
  int tessControl = -1;
  int tessEval = -1;
  int geometry = -1;
  int compute = -1;

  CompileState vertS = compileShaderProgram(shaderName, ShaderType::eVertex, vertShaderSource, vertex);
  CompileState fragS = compileShaderProgram(shaderName, ShaderType::eFragment, fragShaderSource, fragment);
  CompileState tescS = compileShaderProgram(shaderName, ShaderType::eTessControl, tessControlSource, tessControl);
  CompileState teseS = compileShaderProgram(shaderName, ShaderType::eTessEvaluation, tessEvalSource, tessEval);
  CompileState geomS = compileShaderProgram(shaderName, ShaderType::eGeometry, geometrySource, geometry);
  CompileState compS = compileShaderProgram(shaderName, ShaderType::eCompute, computeSource, compute);

  if (vertS == eFailed || fragS == eFailed || tescS == eFailed || teseS == eFailed || geomS == eFailed || compS == eFailed)
  {
    return false;
  }

  shaderProgram = glCreateProgram();

  if (vertS == eSuccess)
  {
    glAttachShader(shaderProgram, vertex);
  }
  if (fragS == eSuccess)
  {
    glAttachShader(shaderProgram, fragment);
  }
  if (tescS == eSuccess)
  {
    glAttachShader(shaderProgram, tessControl);
  }
  if (teseS == eSuccess)
  {
    glAttachShader(shaderProgram, tessEval);
  }
  if (geomS == eSuccess)
  {
    glAttachShader(shaderProgram, geometry);
  }
  if (compS == eSuccess)
  {
    glAttachShader(shaderProgram, compute);
  }

  glLinkProgram(shaderProgram);

  if (vertex != -1 && vertS == eSuccess)
  {
    glDetachShader(shaderProgram, vertex);
    glDeleteShader(vertex);
  }
  if (fragment != -1 && fragS == eSuccess)
  {
    glDetachShader(shaderProgram, fragment);
    glDeleteShader(fragment);
  }
  if (tessControl != -1 && tescS == eSuccess)
  {
    glDetachShader(shaderProgram, tessControl);
    glDeleteShader(tessControl);
  }

  if (tessEval != -1 && teseS == eSuccess)
  {
    glDetachShader(shaderProgram, tessEval);
    glDeleteShader(tessEval);
  }

  if (geometry != -1 && geomS == eSuccess)
  {
    glDetachShader(shaderProgram, geometry);
    glDeleteShader(geometry);
  }

  if (compute != -1 && compS == eSuccess)
  {
    glDetachShader(shaderProgram, compute);
    glDeleteShader(compute);
  }

  std::string output;
  bool success = getShaderLinkStatus(output, shaderProgram);

  if (success == false)
  {
    std::cout << "program did not link successfully: " << shaderName << "\n"
              << output << std::endl;
    return false;
  }

  std::string validationOutput;
  bool validated = getShaderValidationStatus(validationOutput, shaderProgram);

  if (!validated)
  {
    std::cout << "could not validate shader program: " << shaderName << "\n"
              << validationOutput << std::endl;
    return false;
  }

  return true;
}

bool Shader::compile(const char *shaderName)
// const char *vertShaderName,
// const char *fragShaderName,
// const char *tesscontrolName,
// const char *tessevalName,
// const char *geometryName,
// const char *computeName)
{
  int shaderProgram = -1;
  bool success = buildShader(shaderName, shaderProgram);
  if (success)
  {
    m_shaderName = shaderName;
    m_shaderProgram = shaderProgram;
  }
  return success;
}

void Shader::bind()
{
  glUseProgram(m_shaderProgram);
}

void Shader::setUniform(const char *uniformName, const glm::vec2 &vec2R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform2f(uniform, vec2R.x, vec2R.y);
}
void Shader::setUniform(const char *uniformName, const glm::vec3 &vec3R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform3f(uniform, vec3R.x, vec3R.y, vec3R.z);
}
void Shader::setUniform(const char *uniformName, const glm::vec4 &vec4R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform4f(uniform, vec4R.x, vec4R.y, vec4R.z, vec4R.w);
}
void Shader::setUniform(const char *uniformName, const glm::ivec2 &ivec2R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform2i(uniform, ivec2R.x, ivec2R.y);
}
void Shader::setUniform(const char *uniformName, const glm::ivec3 &ivec3R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform3i(uniform, ivec3R.x, ivec3R.y, ivec3R.z);
}
void Shader::setUniform(const char *uniformName, const glm::ivec4 &ivec4R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform4i(uniform, ivec4R.x, ivec4R.y, ivec4R.z, ivec4R.w);
}
void Shader::setUniform(const char *uniformName, const float &floatR)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform1f(uniform, floatR);
}
void Shader::setUniform(const char *uniformName, const int &intR)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform1i(uniform, intR);
}
void Shader::setUniform(const char *uniformName, const double &doubleR)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform1d(uniform, doubleR);
}
void Shader::setUniform(const char *uniformName, const bool &boolR)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniform1i(uniform, int(boolR));
}
int Shader::getUniformIndex(const char *uniformName) const
{
  return glGetUniformLocation(m_shaderProgram, uniformName);
}

int Shader::getProgramId()
{
  return m_shaderProgram;
}

void Shader::setUniform(const char *uniformName, const glm::mat4 &mat4R)
{
  int uniform = getUniformIndex(uniformName);

  if (uniform < 0)
  {
    std::cout << "uniform: " << uniformName << " does not exist." << std::endl;
    return;
  }

  glUniformMatrix4fv(uniform, 1, false, &mat4R[0][0]);
}

void Shader::setUniform(const char *uniformName, const glm::mat4 *matArray, unsigned count)
{
  GLint uniform = getUniformIndex(uniformName);
  if (uniform < 0)
  {
    return;
  }
  glUniformMatrix4fv(uniform, count, false, &((*matArray)[0][0]));
}
