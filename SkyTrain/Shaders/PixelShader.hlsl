struct DirectionalLight
{
	float4 color;
	float3 direction;
};

struct PointLight
{
	float4 color;
	float3 position;
};


cbuffer LightData : register(b0)
{
	// Direction light stuff
	DirectionalLight dLight;

	// Point light
	PointLight pLight;

	// Camera position
	float3 CameraPosition;

	float time;
}

// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal       : NORMAL;
	float3 worldPos     : TEXCOORD0;
	float2 uv           : TEXCOORD1;
};

Texture2D diffuseTexture    : register(t0);
Texture2D specMapTexture    : register(t1);

SamplerState trilinear      : register(s0);

// Entry point for this pixel shader
float4 main(VertexToPixel input) : SV_TARGET
{
	// Re-normalize interpolated normal
	input.normal = normalize(input.normal);

// Directional light ---------------------------------------

// Light direction
float3 lightDir = normalize(dLight.direction);

// Basic diffuse calculation (n dot l)
// We need the direction from the surface TO the light
float dirNdotL = saturate(dot(input.normal, -lightDir));

// Point light --------------------------------------------

// Get direction to the point light
float3 dirToPointLight = normalize(pLight.position - input.worldPos);
float pointNdotL = saturate(dot(input.normal, dirToPointLight));

// Point light specular ----------------------------------
float3 dirToCamera = normalize(CameraPosition - input.worldPos);
float3 refl = reflect(-dirToPointLight, input.normal);
float spec = pow(max(dot(refl, dirToCamera), 0), 64.0f);

// Sample the diffuse texture
float4 diffuseColor = diffuseTexture.Sample(trilinear, input.uv);

float specMapValue = specMapTexture.Sample(trilinear, input.uv).r;

// Combine lights
return (diffuseColor * pLight.color * pointNdotL) + (diffuseColor * dLight.color * dirNdotL) + float4(spec.xxx * specMapValue, 1);
}