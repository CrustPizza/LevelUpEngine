/********************************
*								*
*	Sky Box VS.hlsl				*
*								*
*	Created : 2022/08/03		*
*	Updated : 2022/08/03		*
*********************************/

#include "SkyBoxTypes.hlsli"

/* View */
cbuffer cbView : register( b0 )
{
	matrix ViewProjection;
}

/* Input */
struct VS_Input
{
	float4 Position		: POSITION;
};

/* VS Main */
VS_Output main(float4 Position : SV_POSITION)
{
	VS_Output output = (VS_Output)0;

	output.Position = mul( Position, ViewProjection ).xyww;

	//output.TexCoord.x = -Position.x;
	//output.TexCoord.yz = Position.yz;

	output.TexCoord.xyz = normalize( Position.xyz );

	return output;
}