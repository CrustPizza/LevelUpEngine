/********************************
*								*
*	Line VS.hlsl				*
*								*
*	Created : 2022/08/11		*
*	Updated : 2022/08/11		*
*********************************/

#include "LineTypes.hlsli"

/* Matrix */
cbuffer cbMatrix : register( b0 )
{
	matrix World;
}

/* View */
cbuffer cbView : register( b1 )
{
	matrix ViewProjection;
}

/* Input */
struct VS_Input
{
	float4 Pos		: POSITION;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;
	output.Pos = mul( input.Pos, World );
	output.Pos = mul( output.Pos, ViewProjection );

	return output;
}