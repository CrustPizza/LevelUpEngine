/********************************
*								*
*	Texture 2D VS.hlsl			*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "Texture2DTypes.hlsli"

/* View */
cbuffer cbView : register( b1 )
{
	matrix ViewProjection;
}

/* Input */
struct VS_Input
{
	float4 Position : POSITION;
	float4 TexCoord : TEXCOORD0;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	output.Position = mul( input.Position, ViewProjection );
	output.TexCoord = input.TexCoord;

	return output;
}