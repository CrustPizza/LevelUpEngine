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
	float4 Weights1		: BLENDWEIGHT0;
	float4 Weights2		: BLENDWEIGHT1;
	uint4  WeightIndex1	: BLENDINDICES0;
	uint4  WeightIndex2	: BLENDINDICES1;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	float weight[8] =
	{
		input.Weights1.x,
		input.Weights1.y,
		input.Weights1.z,
		input.Weights1.w,
		input.Weights2.x,
		input.Weights2.y,
		input.Weights2.z,
		1.0f - input.Weights1.x - input.Weights1.y - input.Weights1.z - input.Weights1.w - input.Weights2.x - input.Weights2.y - input.Weights2.z
	};

	uint  index[8] = 
	{
		input.WeightIndex1[0],
		input.WeightIndex1[1],
		input.WeightIndex1[2],
		input.WeightIndex1[3],
		input.WeightIndex2[0],
		input.WeightIndex2[1],
		input.WeightIndex2[2],
		input.WeightIndex2[3]
	};

	float3 pos = 0.0f;
	float3 normal = 0.0f;

	for (int i = 0; i < 8; i++)
	{
		pos += weight[i] * mul( input.Position, BoneMatrix[index[i]] ).xyz;
		normal += weight[i] * mul( input.Normal.xyz, (float3x3)BoneMatrix[index[i]] );
	}

	output.WorldPos = pos;
	output.Position = mul( float4( pos, 1.0f ), ViewProjection );
	output.Normal = normalize( normal );
	output.TexCoord = input.TexCoord.xy;
	output.Tangent = mul( input.Tangent.xyz, (float3x3)World );

	return output;
}