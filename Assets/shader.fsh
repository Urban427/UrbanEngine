#version 410

in vec3 vertOutColor;

out vec4 outColor;

void main() 
{
	outColor = vec4(vertOutColor, 1);
}
