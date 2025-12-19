#version 460 core

out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;

in vec2 TexCoord;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, TexCoord);
}