/********************************
*								*
*	Gaussian Blur PS.hlsl		*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/22		*
*********************************/

/* Define */
#define BlurDepth 15

/* Texture Map */
Texture2D<float4> Texture : register( t0 );

/* Sampler */
sampler Sampler : register( s0 );

/* Parameter */
cbuffer SampleOption : register ( b8 )
{
	float4 SampleOffsets[BlurDepth];
	float4 SampleWeights[BlurDepth];
}

/* PS Main */
float4 main(float4 Unused : COLOR0, float2 TexCoord : TEXCOORD0) : SV_Target0
{
	float4 Color = 0;

	for (int i = 0; i < BlurDepth; i++)
	{
		Color += Texture.Sample(Sampler, TexCoord + SampleOffsets[i].xy) * SampleWeights[i].x;
	}

	return Color;
}