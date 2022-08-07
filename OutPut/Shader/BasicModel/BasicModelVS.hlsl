/********************************
*								*
*	Basic Model VS.hlsl			*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/20		*
*********************************/

#include "BasicModelTypes.hlsli"

/* Matrix */
cbuffer cbMatrix : register( b0 )
{
	matrix World;
	matrix WorldInvTranspose;
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
	float4 Color	: COLOR0;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;
	output.Pos = mul( input.Pos, World );
	output.Pos = mul( output.Pos, ViewProjection );
	output.Color = input.Color;

	return output;
}