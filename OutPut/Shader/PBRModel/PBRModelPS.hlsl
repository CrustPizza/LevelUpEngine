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
Texture2D ShadowMap	 : register( t2 );

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
	float4 DLightColor;
	float  DLightSpecularPower;
}

/* Point Light */
struct PointLight
{
	float4 PLightPosition;
	float4 PLightDiffuse;
	float4 PLightColor;
	float  PLightSpecularPower;
	float  PLightIntensity;
	float2 padding;
};

cbuffer cbPointLight : register( b2 )
{
	PointLight PointLights[20];
}

/* Const PBR Parameter */
cbuffer cbPBRParmeter : register( b3 )
{
	float3 Albedo;
	float  Alpha;
	float  Metallic;
	float  Roughness;
}

/* PS Output */
struct PS_Output
{
	float4 screen	: SV_TARGET0;
	float4 depth	: SV_TARGET1;
	float4 albedo	: SV_TARGET2;
	float4 normal	: SV_TARGET3;
	float4 worldPos	: SV_TARGET4;
	float4 tangent	: SV_TARGET5;
};

/* PS Main - Constant Value */
PS_Output ConstVarMain(VS_Default_Output input)
{
	PS_Output output = (PS_Output)0;

	const float3 ViewVector = normalize( ViewPosition - input.WorldPos );
	const float3 Normal = normalize( input.Normal );
	const float AO = 1.0f;

	float3 LightColor[21];
	float3 LightDirection[21];

	LightColor[0] = DLightColor.xyz;
	LightDirection[0] = -DLightDirection;

	for (int i = 0; i < 20; i++)
	{
		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length( pLightDirection );

		LightColor[i + 1] = 0;
		LightDirection[i + 1] = 0;

		if (distance < PointLights[i].PLightIntensity)
		{
			LightDirection[i + 1] = normalize( pLightDirection );

			float NDotL = dot( Normal, LightDirection[i] );

			if (NDotL > 0.0f)
			{
				float intensity = 1.0f - ( distance / PointLights[i].PLightIntensity );

				LightColor[i + 1] = PointLights[i].PLightColor.xyz * intensity;
			}
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, LightColor, LightDirection, Albedo, Roughness, Metallic, AO );

	float NdotL = dot(Normal, -DLightDirection);
	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample( Sampler, shadowTexCoord ).r;
	
	if (depthFormShadowMap + 0.005f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(Albedo, 1.0f);
	output.normal = float4(Normal, 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(0.0f, 0.0f, 0.0f, 1.0f);

	return output;
}

/* PS Main - Albedo Map */
PS_Output AlbedoMain(VS_Default_Output input)
{
	PS_Output output = (PS_Output)0;

	const float3 ViewVector = normalize( ViewPosition - input.WorldPos );
	const float3 Normal = normalize( input.Normal );
	const float AO = 1.0f;
	const float3 AlbedoColor = DiffuseMap.Sample( Sampler, input.TexCoord ).xyz;

	float3 LightColor[21];
	float3 LightDirection[21];

	LightColor[0] = DLightColor.xyz;
	LightDirection[0] = -DLightDirection;

	for (int i = 0; i < 20; i++)
	{
		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		LightColor[i + 1] = 0;
		LightDirection[i + 1] = 0;

		if (distance < PointLights[i].PLightIntensity)
		{
			LightDirection[i + 1] = normalize(pLightDirection);

			float NDotL = dot(Normal, LightDirection[i]);

			if (NDotL > 0.0f)
			{
				float intensity = 1.0f - (distance / PointLights[i].PLightIntensity);

				LightColor[i + 1] = PointLights[i].PLightColor.xyz * intensity;
			}
		}
	}

	float3 color = LightSurface( ViewVector, Normal, 21, LightColor, LightDirection, AlbedoColor, Roughness, Metallic, AO );

	float NdotL = dot(Normal, -DLightDirection);
	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.005f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(AlbedoColor, 1.0f);
	output.normal = float4(Normal, 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(0.0f, 0.0f, 0.0f, 1.0f);

	return output;
}

/* PS Main - Albedo Map + Normal Map */
PS_Output AlbedoNormalMain(VS_Normal_Output input)
{
	PS_Output output = (PS_Output)0;

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

	float3 LightColor[21];
	float3 LightDirection[21];

	LightColor[0] = DLightColor.xyz;
	LightDirection[0] = -DLightDirection;

	for (int i = 0; i < 20; i++)
	{
		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		LightColor[i + 1] = 0;
		LightDirection[i + 1] = 0;

		if (distance < PointLights[i].PLightIntensity)
		{
			LightDirection[i + 1] = normalize(pLightDirection);

			float NDotL = dot(Normal, LightDirection[i]);

			if (NDotL > 0.0f)
			{
				float intensity = 1.0f - (distance / PointLights[i].PLightIntensity);

				LightColor[i + 1] = PointLights[i].PLightColor.xyz * intensity;
			}
		}
	}

	float3 color = LightSurface( ViewVector, Normal, 21, LightColor, LightDirection, AlbedoColor, Roughness, Metallic, AO );

	float NdotL = dot(Normal, -DLightDirection);
	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.005f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(AlbedoColor, 1.0f);
	output.normal = float4(N, 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(Normal, 1.0f);

	return output;
}