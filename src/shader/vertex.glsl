#version 330 core
layout (position = 0) in vec3 as pos;

void main() 
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
}