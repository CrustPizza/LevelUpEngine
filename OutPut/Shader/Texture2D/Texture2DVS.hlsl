/********************************
*								*
*	Texture 2D VS.hlsl			*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "Texture2DTypes.hlsli"

/* World View Projection Matrix */
cbuffer cbWVPMatrix : register( b4 )
{
	matrix WVPMatrix;
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

	output.Position = mul( input.Position, WVPMatrix );
	output.TexCoord = input.TexCoord;

	return output;
}