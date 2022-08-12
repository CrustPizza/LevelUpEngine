/********************************
*								*
*	Texture 2D PS.hlsl			*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "Texture2DTypes.hlsli"

/* Texture Map */
Texture2D Texture : register(t0);

/* Sampler */
sampler   Sampler : register(s0);

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
	PS_Output output = (PS_Output)0;

	float4 color = Texture.Sample(Sampler, input.TexCoord);

	output.screen = color;
	output.depth = input.Position.z;
	output.albedo = color;
	output.normal = 0;
	output.worldPos = float4(input.Position.xyz, 1.0f);

	return output;
}