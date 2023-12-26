#version 130

// Input variable declarations
uniform vec4 vLightAmbient;
uniform vec4 vSurfAmbient;

uniform sampler2D sSkinTex;
varying vec2 vTexCoord;

// Per-fragment operations
void main()
{
	vec4 vColor = vLightAmbient * vSurfAmbient;
	gl_FragColor = vColor * texture(sSkinTex, vTexCoord);
}
