/********************************
*								*
*	Basic Color PS.hlsl			*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#include "BasicColorTypes.hlsli"

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return input.Color;
}