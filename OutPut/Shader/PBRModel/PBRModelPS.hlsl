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
Texture2D DiffuseMap	: register(t0);
Texture2D NormalMap		: register(t1);
Texture2D MetallicMap	: register(t2);
Texture2D RoughnessMap	: register(t3);
Texture2D AOMap			: register(t4);
Texture2D ShadowMap		: register(t7);

/* View */
cbuffer cbView : register(b0)
{
	float3 ViewPosition;
}

/* Directional Light */
cbuffer cbDirectionalLight : register(b1)
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
	float  PLightRange;
	float padding;
};

cbuffer cbPointLight : register(b2)
{
	PointLight PointLights[20];
}

/* Const PBR Parameter */
cbuffer cbPBRParmeter : register(b3)
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

	const float3 ViewVector = normalize(ViewPosition - input.WorldPos);
	const float3 Normal = normalize(input.Normal);
	const float AO = 1.0f;

	float3 lightColor[21];
	float3 lightDirection[21];

	lightColor[0].xyz = DLightColor.xyz;
	lightDirection[0].xyz = -DLightDirection.xyz;

	[unroll]
	for (int i = 0; i < 20; i++)
	{
		int j = i + 1;

		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		lightColor[j] = 0;
		lightDirection[j] = 0;

		if (distance < PointLights[i].PLightRange)
		{
			lightDirection[j] = normalize(pLightDirection);

			float intensity = (1.0f - (distance / PointLights[i].PLightRange)) * PointLights[i].PLightIntensity;

			lightColor[j] = PointLights[i].PLightColor.xyz * intensity;
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, lightColor, lightDirection, Albedo, Roughness, Metallic, AO);

	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.0025f < input.ShadowDepth.z)
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

	const float3 ViewVector = normalize(ViewPosition - input.WorldPos);
	const float3 Normal = normalize(input.Normal);
	const float AO = 1.0f;
	const float3 AlbedoColor = pow(DiffuseMap.Sample(Sampler, input.TexCoord).xyz, 2.2f);

	float3 lightColor[21];
	float3 lightDirection[21];

	lightColor[0].xyz = DLightColor.xyz;
	lightDirection[0].xyz = -DLightDirection.xyz;

	[unroll]
	for (int i = 0; i < 20; i++)
	{
		int j = i + 1;

		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		lightColor[j] = 0;
		lightDirection[j] = 0;

		if (distance < PointLights[i].PLightRange)
		{
			lightDirection[j] = normalize(pLightDirection);

			float intensity = (1.0f - (distance / PointLights[i].PLightRange)) * PointLights[i].PLightIntensity;

			lightColor[j] = PointLights[i].PLightColor.xyz * intensity;
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, lightColor, lightDirection, AlbedoColor, Roughness, Metallic, AO);

	color = pow(color, 1.0f / 2.2);

	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.0025f < input.ShadowDepth.z)
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
	float3 B = cross(T, N);

	float3x3 TSpace = { T, B, N };

	N = NormalMap.Sample(Sampler, input.TexCoord).xyz;

	const float3 ViewVector = normalize(ViewPosition - input.WorldPos);
	const float3 Normal = normalize(mul(N.xyz, TSpace));
	const float AO = 1.0f;
	const float3 AlbedoColor = pow(DiffuseMap.Sample(Sampler, input.TexCoord).xyz, 2.2f);

	float3 lightColor[21];
	float3 lightDirection[21];

	lightColor[0].xyz = DLightColor.xyz;
	lightDirection[0].xyz = -DLightDirection.xyz;

	[unroll]
	for (int i = 0; i < 20; i++)
	{
		int j = i + 1;

		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		lightColor[j] = 0;
		lightDirection[j] = 0;

		if (distance < PointLights[i].PLightRange)
		{
			lightDirection[j] = normalize(pLightDirection);

			float intensity = (1.0f - (distance / PointLights[i].PLightRange)) * PointLights[i].PLightIntensity;

			lightColor[j] = PointLights[i].PLightColor.xyz * intensity;
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, lightColor, lightDirection, AlbedoColor, Roughness, Metallic, AO);

	color = pow(color, 1.0f / 2.2);

	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.0025f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(AlbedoColor, 1.0f);
	output.normal = float4(normalize(input.Normal), 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(Normal, 1.0f);

	return output;
}

/* PS Main - Albedo Map + Normal Map + RM */
PS_Output WithoutAOMain(VS_Normal_Output input)
{
	PS_Output output = (PS_Output)0;

	float3 N = normalize(input.Normal);
	float3 T = input.Tangent;
	T = normalize(T - dot(T, N) * N);
	float3 B = cross(N, T);
	B = normalize(B - dot(B, N) * N - B * dot(B, T) * T);

	float3x3 TSpace = float3x3(T, B, N);

	N = NormalMap.Sample(Sampler, input.TexCoord).xyz;
	N = N * 2.0f - 1.0f;

	const float3 ViewVector = normalize(ViewPosition - input.WorldPos);
	const float3 Normal = normalize(mul(N.xyz, TSpace));
	const float metallic = MetallicMap.Sample(Sampler, input.TexCoord).r;
	const float roughness = RoughnessMap.Sample(Sampler, input.TexCoord).r;
	const float AO = 1.0f;
	const float3 AlbedoColor = pow(DiffuseMap.Sample(Sampler, input.TexCoord).xyz, 2.2f);

	float3 lightColor[21];
	float3 lightDirection[21];

	lightColor[0].xyz = DLightColor.xyz;
	lightDirection[0].xyz = -DLightDirection.xyz;

	[unroll]
	for (int i = 0; i < 20; i++)
	{
		int j = i + 1;

		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		lightColor[j] = 0;
		lightDirection[j] = 0;

		if (distance < PointLights[i].PLightRange)
		{
			lightDirection[j] = normalize(pLightDirection);

			float intensity = (1.0f - (distance / PointLights[i].PLightRange)) * PointLights[i].PLightIntensity;

			lightColor[j] = PointLights[i].PLightColor.xyz * intensity;
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, lightColor, lightDirection, AlbedoColor, roughness, metallic, AO);

	color = pow(color, 1.0f / 2.2);

	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.0025f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(AlbedoColor, 1.0f);
	output.normal = float4(normalize(input.Normal), 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(Normal, 1.0f);

	return output;
}

/* PS Main - Albedo Map + Normal Map + RMA */
PS_Output AllTextureMain(VS_Normal_Output input)
{
	PS_Output output = (PS_Output)0;

	float3 N = normalize(input.Normal);
	float3 T = input.Tangent;
	T = normalize(T - dot(T, N) * N);
	float3 B = cross(N, T);
	B = normalize(B - dot(B, N) * N - B * dot(B, T) * T);

	float3x3 TSpace = float3x3(T, B, N);

	N = NormalMap.Sample(Sampler, input.TexCoord).xyz;
	N = N * 2.0f - 1.0f;

	const float3 ViewVector = normalize(ViewPosition - input.WorldPos);
	const float3 Normal = normalize(mul(N.xyz, TSpace));
	const float metallic = MetallicMap.Sample(Sampler, input.TexCoord).r;
	const float roughness = RoughnessMap.Sample(Sampler, input.TexCoord).r;
	const float AO = AOMap.Sample(Sampler, input.TexCoord).r;
	const float3 AlbedoColor = pow(DiffuseMap.Sample(Sampler, input.TexCoord).xyz, 2.2f);

	float3 lightColor[21];
	float3 lightDirection[21];

	lightColor[0].xyz = DLightColor.xyz;
	lightDirection[0].xyz = -DLightDirection.xyz;

	[unroll]
	for (int i = 0; i < 20; i++)
	{
		int j = i + 1;

		float3 pLightDirection = PointLights[i].PLightPosition.xyz - input.WorldPos;
		float distance = length(pLightDirection);

		lightColor[j] = 0;
		lightDirection[j] = 0;

		if (distance < PointLights[i].PLightRange)
		{
			lightDirection[j] = normalize(pLightDirection);

			float intensity = (1.0f - (distance / PointLights[i].PLightRange)) * PointLights[i].PLightIntensity;

			lightColor[j] = PointLights[i].PLightColor.xyz * intensity;
		}
	}

	float3 color = LightSurface(ViewVector, Normal, 21, lightColor, lightDirection, AlbedoColor, roughness, metallic, AO);

	color = pow(color, 1.0f / 2.2);

	float4 shadowDepth = input.ShadowDepth;

	float2 shadowTexCoord = shadowDepth.xy / shadowDepth.w;
	shadowTexCoord.y *= -1;
	shadowTexCoord = shadowTexCoord * 0.5f + 0.5f;
	float depthFormShadowMap = ShadowMap.Sample(Sampler, shadowTexCoord).r;

	if (depthFormShadowMap + 0.0025f < input.ShadowDepth.z)
	{
		color *= 0.5f;
	}

	output.screen = float4(color, Alpha);
	output.depth = input.Position.z;
	output.albedo = float4(AlbedoColor, 1.0f);
	output.normal = float4(normalize(input.Normal), 1.0f);
	output.worldPos = float4(input.WorldPos, 1.0f);
	output.tangent = float4(Normal, 1.0f);

	return output;
}