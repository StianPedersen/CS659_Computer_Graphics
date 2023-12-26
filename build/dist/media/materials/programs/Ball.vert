#version 130

// Input and output variable declarations
uniform mat4x4 mWorldViewProjMatrix;
uniform mat4x4 mTextureMatrix;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec4 vTexCoord;

// Per-vertex operations
void main()
{
	gl_Position = mWorldViewProjMatrix * gl_Vertex;

	vPosition = gl_Vertex.xyz;
	vNormal = gl_Normal;
	vTexCoord.st = gl_MultiTexCoord0.st;
	vTexCoord.pq = (mTextureMatrix * vec4(gl_MultiTexCoord0.st, 0, 1)).st;
}
