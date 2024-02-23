attribute vec4 a_Position;
attribute vec2 a_TextureCoordinates;
varying vec2 v_TextureCoordinates;

uniform mat4 transform;
uniform mat4 projection;

void main()
{
	v_TextureCoordinates = a_TextureCoordinates.xy;
	gl_Position =  projection * (transform * a_Position);
};