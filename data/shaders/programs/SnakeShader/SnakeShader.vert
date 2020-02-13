#version 450 core

layout (location = 0) in vec3 vertPos;

uniform mat4 model;
uniform mat4 pv;

void main()
{
  gl_Position = pv * model * vec4(vertPos, 1.0f);
}