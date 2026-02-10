#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 uVP;

void main()
{
    gl_Position = uVP * vec4(aPos, 0.0, 1.0);
}
