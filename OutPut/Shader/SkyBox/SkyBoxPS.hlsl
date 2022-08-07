/********************************
*								*
*	Sky Box PS.hlsl				*
*								*
*	Created : 2022/08/03		*
*	Updated : 2022/08/03		*
*********************************/

#include "SkyBoxTypes.hlsli"

/* Texture Map */
TextureCube<float4> CubeMap : register(t0);

/* Sampler */
sampler   Sampler    : register(s0);

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return CubeMap.Sample( Sampler, input.TexCoord );
}