precision mediump float;
varying mediump vec2 v_TextureCoordinates;
varying mediump vec3 v_Normal;

uniform sampler2D u_TextureUnit;

void main()
{
	vec3 light = vec3(-0.5, -0.2, -0.2);
	vec4 color = texture2D(u_TextureUnit, v_TextureCoordinates.xy);
	float result_colot =  max(0.0, v_Normal.x);
	result_colot += 0.1;
	color *= result_colot;
	gl_FragColor = color;
}