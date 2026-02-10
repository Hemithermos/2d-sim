#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 u_Position;     // world position
uniform float u_Radius;      // world radius
uniform mat4 u_ViewProj;     // camera matrix

void main()
{
    vec2 worldPos = aPos * u_Radius + u_Position;
    gl_Position = u_ViewProj * vec4(worldPos, 0.0, 1.0);
}
