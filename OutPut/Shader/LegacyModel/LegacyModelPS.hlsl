/********************************
*								*
*	Legacy Model PS.hlsl		*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "LegacyModelTypes.hlsli"

/* Texture Map */
Texture2D DiffuseMap : register( t0 );
Texture2D NormalMap  : register( t1 );

/* Sampler */
sampler   Sampler    : register( s0 );

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

/* Point Light */
cbuffer cbPointLight : register( b2 )
{
	float4 PLightPosition;
	float4 PLightDiffuse;
	float  PLightSpecularPower;
	float  PLightIntensity;
}

/* Material */
cbuffer cbMaterial : register( b3 )
{
	float4 MaterialAmbient;
	float4 MaterialDiffuse;
	float4 MaterialSpecular;
}

/* PS Output */
struct PS_Output
{
	float4 screen	: SV_TARGET0;
	float4 depth	: SV_TARGET1;
	float4 albedo	: SV_TARGET2;
	float4 normal	: SV_TARGET3;
	float4 worldPos	: SV_TARGET4;
};

/* PS Main */
PS_Output main(VS_Output input)
{
	float3 N = normalize( input.Normal );
	float3 T = input.Tangent;
	T = normalize( T - dot( T, N ) * N );
	float3 B = cross( N, T );

	float3x3 TSpace = { T, B, N };

	float4 DiffuseColor = DiffuseMap.Sample( Sampler, input.TexCoord );
	float3 Normal = NormalMap.Sample( Sampler, input.TexCoord ).xyz;
	Normal = mul( Normal.xyz, TSpace );

	// Directional Light

	// Ambient
	float4 ret = 0;
	ret.x = DLightAmbient.x * MaterialAmbient.x;
	ret.y = DLightAmbient.y * MaterialAmbient.y;
	ret.z = DLightAmbient.z * MaterialAmbient.z;

	// Diffuse & Specular
	float NDotL = dot( Normal, -DLightDirection);
	float Specular = 0.0f;

	float3 V = normalize(ViewPosition - input.WorldPos); // View Vector

	if (NDotL > 0.0f)
	{
		ret += NDotL * DLightDiffuse * MaterialDiffuse;

		float3 H = normalize( -DLightDirection + V ); // Half Vector

		float NDotH = max( dot( Normal, H ), 0.0f );

		Specular = pow( NDotH, DLightSpecularPower );
	}

	// Point Light

	// Diffuse & Specular
	float3 pLightDirection = PLightPosition.xyz - input.WorldPos;
	float distance = length(pLightDirection);
	pLightDirection = normalize( pLightDirection );

	if (distance < PLightIntensity)
	{
		float NDotL = dot( Normal, pLightDirection );

		if (NDotL > 0.0f)
		{
			float intensity = 1.0f - (distance / PLightIntensity);

			ret += NDotL * PLightDiffuse * MaterialDiffuse * intensity;

			float3 H = normalize( pLightDirection + V );

			float NDotH = max( dot( Normal, H ), 0.0f );

			Specular += pow( NDotH, PLightSpecularPower ) * intensity;
		}
	}

	// Gamma Correction
	DiffuseColor = pow(DiffuseColor, 2.2f);
	DiffuseColor = DiffuseColor * saturate(ret) + Specular * MaterialSpecular;
	DiffuseColor = pow(DiffuseColor, 1.0f / 2.2f);

	DiffuseColor.a = 1.0f;

	PS_Output output = (PS_Output)0;

	output.screen = DiffuseColor;
	output.depth = input.Position.z;
	output.albedo = DiffuseMap.Sample(Sampler, input.TexCoord);
	output.normal = float4(input.Normal, 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);

	return output;
}