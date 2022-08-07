/********************************
*								*
*	Down Sampling PS.hlsl		*
*								*
*	Created : 2022/07/22		*
*	Updated : 2022/07/25		*
*********************************/

/* Texture Map */
Texture2D<float4> Texture : register( t0 );

/* Sampler */
sampler Sampler : register( s0 );

/* Parameter */
cbuffer ThresholdValue : register (b0)
{
	float Threshold;
}

/* PS Main */
float4 main(float4 Color : COLOR0, float2 TexCoord : TEXCOORD0) : SV_Target0
{
	float4 ret = Texture.Sample(Sampler, TexCoord);

	return saturate((ret - Threshold) / (1 - Threshold));
}