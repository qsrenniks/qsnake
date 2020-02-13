#version 450 core

uniform vec4 color;

out vec4 fbColor;

void main()
{
  fbColor = color;
}