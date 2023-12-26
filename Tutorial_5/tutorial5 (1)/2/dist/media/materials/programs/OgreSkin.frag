#version 130

// Input variable declarations
uniform vec4 vLightPosition;
uniform vec4 vLightAmbient;
uniform vec4 vLightDiffuse;

uniform vec4 vSurfAmbient;
uniform vec4 vSurfDiffuse;

uniform sampler2D sSkinTex;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexCoord;


// Compute diffuse color
void DiffuseColor(out vec4 vDiffuse, in vec3 vPosition, in vec3 vNormal)
{
	vec3 vLightDir = normalize(vLightPosition.xyz - vPosition);
	vDiffuse = max(0.0, dot(vLightDir, vNormal)) * vLightDiffuse * vSurfDiffuse;
}

// Per-fragment operations
void main()
{
	vec4 vDiffuse;
	DiffuseColor(vDiffuse, vPosition, normalize(vNormal));
	
	vec4 vColor = vLightAmbient * vSurfAmbient + vDiffuse;
	gl_FragColor = vColor * texture(sSkinTex, vTexCoord);
}
