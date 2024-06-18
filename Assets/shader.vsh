attribute vec4 a_Position;
attribute vec2 a_TextureCoordinates;
attribute vec4 a_Normal;

varying mediump vec2 v_TextureCoordinates;
varying mediump vec3 v_Normal;

uniform mat4 transform;
uniform mat4 camView;
uniform mat4 projection;

void main()
{
	gl_Position =  projection * (camView * (transform * a_Position));
	v_TextureCoordinates = a_TextureCoordinates.xy;
	v_Normal = (transform * a_Normal).xyz;
}