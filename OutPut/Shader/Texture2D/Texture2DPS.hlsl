/********************************
*								*
*	Texture 2D PS.hlsl			*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "Texture2DTypes.hlsli"

/* Texture Map */
Texture2D Texture : register( t0 );

/* Sampler */
sampler   Sampler : register( s0 );

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return Texture.Sample( Sampler, input.TexCoord );
}