/********************************
*								*
*	Basic Model PS.hlsl			*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/20		*
*********************************/

#include "BasicModelTypes.hlsli"

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return input.Color;
}