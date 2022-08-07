/********************************
*								*
*	Basic Color VS.hlsl			*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#include "BasicColorTypes.hlsli"

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
	output.Pos = input.Pos;
	output.Color = input.Color;

	return output;
}