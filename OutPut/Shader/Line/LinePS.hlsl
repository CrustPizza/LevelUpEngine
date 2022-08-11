/********************************
*								*
*	Line PS.hlsl				*
*								*
*	Created : 2022/08/11		*
*	Updated : 2022/08/11		*
*********************************/

#include "LineTypes.hlsli"

/* Color */
cbuffer LineColor : register ( b6 )
{
	float4 Color;
}

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return Color;
}