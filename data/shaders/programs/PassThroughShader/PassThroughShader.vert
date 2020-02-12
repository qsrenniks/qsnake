#version 450 core

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;

uniform mat4 model;
uniform mat4 pv;

out vec3 worldPos;
smooth out vec3 worldNormal;

void main()
{
  worldPos = vec3(model * vec4(vertPosition, 1.0f));
  mat4 normalTransform = transpose(inverse(model));
  worldNormal = vec3(normalize(normalTransform * vec4(vertNormal, 0.0f)));
  gl_Position = pv * model * vec4(vertPosition, 1.0f);
}