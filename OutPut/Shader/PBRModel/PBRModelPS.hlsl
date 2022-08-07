/********************************
*								*
*	PBR Model PS.hlsl			*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/07		*
*********************************/

#include "PBRModelTypes.hlsli"
#include "PBRModelMethod.hlsli"

/* Texture Map */
Texture2D DiffuseMap : register( t0 );
Texture2D NormalMap  : register( t1 );

/* View */
cbuffer cbView : register( b0 )
{
	float3 ViewPosition;
}

/* Directional Light */
cbuffer cbDirectionalLight : register( b1 )
{
	float3 DLightDirection;
	float4 DLightDiffuse;
	float4 DLightAmbient;
	float  DLightSpecularPower;
}

/* Const PBR Parameter */
cbuffer cbPBRParmeter : register( b2 )
{
	float3 LightDirection[3];
	float3 LightColor[3];

	float3 Albedo;
	float  Alpha;
	float  Metallic;
	float  Roughness;
}

/* PS Main - Constant Value */
float4 ConstVarMain(VS_Default_Output input) : SV_TARGET0
{
	const float3 ViewVector = normalize( ViewPosition - input.WorldPos );
	const float3 Normal = normalize( input.Normal );
	const float AO = 1.0f;

	float3 color = LightSurface(ViewVector, Normal, 3, LightColor, LightDirection, Albedo, Roughness, Metallic, AO );

	return float4(color, Alpha);
}

/* PS Main - Albedo Map */
float4 AlbedoMain(VS_Default_Output input) : SV_TARGET0
{
	const float3 ViewVector = normalize( ViewPosition - input.WorldPos );
	const float3 Normal = normalize( input.Normal );
	const float AO = 1.0f;
	const float3 AlbedoColor = DiffuseMap.Sample( Sampler, input.TexCoord ).xyz;

	float3 color = LightSurface( ViewVector, Normal, 3, LightColor, LightDirection, AlbedoColor, Roughness, Metallic, AO );

	return float4(color, Alpha);
}

/* PS Main - Albedo Map + Normal Map */
float4 AlbedoNormalMain(VS_Normal_Output input) : SV_TARGET0
{
	float3 N = normalize(input.Normal);
	float3 T = input.Tangent;
	T = normalize(T - dot(T, N) * N);
	float3 B = cross(N, T);

	float3x3 TSpace = { T, B, N };

	N = NormalMap.Sample(Sampler, input.TexCoord).xyz;

	const float3 ViewVector = normalize( ViewPosition - input.WorldPos );
	const float3 Normal = mul( N.xyz, TSpace );
	const float AO = 1.0f;
	const float3 AlbedoColor = DiffuseMap.Sample( Sampler, input.TexCoord ).xyz;

	float3 color = LightSurface( ViewVector, Normal, 3, LightColor, LightDirection, AlbedoColor, Roughness, Metallic, AO );

	return float4(color, Alpha);
}