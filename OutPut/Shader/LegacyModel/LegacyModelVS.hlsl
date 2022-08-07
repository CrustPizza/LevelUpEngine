/********************************
*								*
*	Legacy Model VS.hlsl		*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "LegacyModelTypes.hlsli"

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
	float4 Position : POSITION;
	float4 Normal	: NORMAL;
	float4 TexCoord : TEXCOORD0;
	float4 Tangent	: TANGENT0;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;
	output.WorldPos = mul( input.Position, World ).xyz;
	output.Position = mul( float4(output.WorldPos, 1.0f), ViewProjection );
	output.Normal = normalize( mul( input.Normal.xyz, (float3x3)WorldInvTranspose ) );
	output.TexCoord = input.TexCoord.xy;
	output.Tangent = mul( input.Tangent.xyz, (float3x3)World );

	return output;
}