#version 450 core

layout (location = 0) in vec3 vertPosition;

uniform mat4 model;
uniform mat4 pv;

out vec3 worldPos;

void main()
{
  worldPos = vec3(model * vec4(vertPosition, 1.0f));
  gl_Position = pv * vec4(worldPos, 1.0f);
}