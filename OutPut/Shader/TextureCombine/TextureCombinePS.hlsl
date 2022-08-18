/********************************
*								*
*	Texture Combine PS.hlsl		*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/22		*
*********************************/

/* Texture Map */
Texture2D<float4> BaseTexture : register(t0);
Texture2D<float4> SourceTexture : register(t1);

/* Sampler */
sampler Sampler : register(s0);

/* Parameter */
cbuffer CombineParameter : register (b0)
{
	float BaseSaturation;
	float SourceSaturation;
	float BaseIntensity;
	float SourceIntensity;
}

float4 AdjustSaturation(float4 Color, float Saturation)
{
	float Grey = dot(Color.rgb, float3(0.3f, 0.59f, 0.11f));

	return lerp(Grey, Color, Saturation);
}

/* PS Main */
float4 main(float4 Color : COLOR0, float2 TexCoord : TEXCOORD0) : SV_TARGET0
{
	float4 Base = BaseTexture.Sample(Sampler, TexCoord);
	float4 Source = SourceTexture.Sample(Sampler, TexCoord);

	Base = AdjustSaturation(Base, BaseSaturation) * BaseIntensity;
	Source = AdjustSaturation(Source, SourceSaturation) * SourceIntensity;

	Base *= (1 - saturate(Source));

	return Base + Source;
}