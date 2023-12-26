#version 130

// Input variable declarations
uniform vec4 vLightPosition;
uniform vec4 vCameraPosition;
uniform vec4 vLightAmbient;
uniform vec4 vLightDiffuse;
uniform vec4 vLightSpecular;
uniform vec4 vLightAttenuation;

uniform vec4 vSurfEmissive;
uniform vec4 vSurfAmbient;
uniform vec4 vSurfDiffuse;
uniform vec4 vSurfSpecular;
uniform float fSurfShininess;

uniform sampler2D sBallTex;
uniform sampler2D sStainTex;

varying vec3 vPosition;
varying vec3 vNormal; 
uniform vec3 Ldcs;


varying vec4 vTexCoord;

// Phong reflection model for one point light source
vec4 PhongReflect(vec3 vLightDir, float fLightDist, vec3 vViewDir, vec3 vNormal)
{
	// Compute light attenuation term
	float fLightAtt = 0.0;
	if(fLightDist <= vLightAttenuation.x)
		fLightAtt = 1.0 / (vLightAttenuation.y + vLightAttenuation.z * fLightDist + vLightAttenuation.w * fLightDist * fLightDist);

	// Compute diffuse and specular terms
	vec4 vDiffuse = max(0.0, dot(vLightDir, vNormal)) * vLightDiffuse * vSurfDiffuse;
	vec4 vSpecular = pow(max(0.0, dot(normalize(vLightDir + vViewDir), vNormal)), fSurfShininess) * vLightSpecular * vSurfSpecular;
	
	//  vSurfSpecular specular albedu cs
	// Compute final reflected color

	// Spot
	penumbra = radian(120); // outermost angle
	umbra =  radian(90); // where the light is the highest
	float Spot = SpotlightFactor(vLightDir, umbra, penumbra);

	vec4 vColor = vSurfEmissive + vLightAmbient * vSurfAmbient + fLightAtt * Spot * (vDiffuse + vSpecular);
	return vColor;
}

// Spotlight factor
vec4 SpotlightFactor(vec3 vLightDir, float umbra, float penumbra)
{	
	// Spotlight factor	
	rho = dot(Ldcs, vLightDir); 
	theta = umbraangle;
	phi = penangle;


	if (rho > cos(theta/2))
	{
		return 1;
	}
	else if (rho <= cos(phi/2))
	{
		retur 0;
	}
	else
	{
		factor = (rho - cos(phi/2)) / (cos(theta/2) - cos(phi/2))
		return factor;
	}	
}

// Per-fragment operations
void main()
{
	// Obtain light direction and distance
	vec3 vLightDir = vLightPosition.xyz - vPosition;
	float fLightDist = length(vLightDir);
	vLightDir = vLightDir / fLightDist;
	
	// Compute lighting color based on Phong reflection model
	vec3 vViewDir = normalize(vCameraPosition.xyz - vPosition);
	vec3 vNormalDir = normalize(vNormal);

	vec4 vColor = PhongReflect(vLightDir, fLightDist, vViewDir, vNormalDir);
	
	// Multiply lighting color with texture colors to obtain final result
	gl_FragColor = vColor * texture(sBallTex, vTexCoord.st) * texture(sStainTex, vTexCoord.pq);
}
