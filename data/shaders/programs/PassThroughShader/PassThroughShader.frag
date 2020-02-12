#version 450 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 worldPos;
smooth in vec3 worldNormal;

void main()
{
  gPosition = worldPos;
  gNormal = normalize(worldNormal);
  gAlbedoSpec = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

