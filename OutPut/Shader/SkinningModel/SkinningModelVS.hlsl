/********************************
*								*
*	Skinning Model VS.hlsl		*
*								*
*	Created : 2022/08/01		*
*	Updated : 2022/08/02		*
*********************************/

#include "SkinningModelTypes.hlsli"

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

/* Bone Matrix */
cbuffer cbBoneMatrix : register ( b2 )
{
	matrix BoneMatrix[64];
}

/* Input */
struct VS_Input
{
	float4 Position		: POSITION;
	float4 Normal		: NORMAL;
	float4 TexCoord		: TEXCOORD0;
	float4 Tangent		: TANGENT0;
	float4 Weights		: BLENDWEIGHT0;
	uint4  WeightIndex  : BLENDINDICES0;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	float weight[4] = { input.Weights.x, input.Weights.y, input.Weights.z, 1.0f - input.Weights.x - input.Weights.y - input.Weights.z };
	uint  index[4] = { input.WeightIndex[0], input.WeightIndex[1], input.WeightIndex[2], input.WeightIndex[3] };

	float3 pos = 0.0f;
	float3 normal = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		pos += weight[i] * mul( input.Position, BoneMatrix[index[i]] ).xyz;
		normal += weight[i] * mul( input.Normal.xyz, (float3x3)BoneMatrix[index[i]] );
	}

	output.WorldPos = pos;
	output.Position = mul( float4( pos, 1.0f ), ViewProjection );
	output.Normal = normalize( mul( normal, (float3x3)WorldInvTranspose ) );
	output.TexCoord = input.TexCoord.xy;
	output.Tangent = mul( input.Tangent.xyz, (float3x3)World );

	return output;
}