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
	float4 Weights3		: BLENDWEIGHT2;
	float4 Weights4		: BLENDWEIGHT3;
	uint4  WeightIndex1	: BLENDINDICES0;
	uint4  WeightIndex2	: BLENDINDICES1;
	uint4  WeightIndex3	: BLENDINDICES2;
	uint4  WeightIndex4	: BLENDINDICES3;
};

/* VS Main */
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	float weight[16] =
	{
		input.Weights1.x,
		input.Weights1.y,
		input.Weights1.z,
		input.Weights1.w,
		input.Weights2.x,
		input.Weights2.y,
		input.Weights2.z,
		input.Weights2.w,
		input.Weights3.x,
		input.Weights3.y,
		input.Weights3.z,
		input.Weights3.w,
		input.Weights4.x,
		input.Weights4.y,
		input.Weights4.z,
		input.Weights4.w
	};

	uint  index[16] =
	{
		input.WeightIndex1[0],
		input.WeightIndex1[1],
		input.WeightIndex1[2],
		input.WeightIndex1[3],
		input.WeightIndex2[0],
		input.WeightIndex2[1],
		input.WeightIndex2[2],
		input.WeightIndex2[3],
		input.WeightIndex3[0],
		input.WeightIndex3[1],
		input.WeightIndex3[2],
		input.WeightIndex3[3],
		input.WeightIndex4[0],
		input.WeightIndex4[1],
		input.WeightIndex4[2],
		input.WeightIndex4[3]
	};

	float3 pos = 0.0f;
	float3 normal = 0.0f;

	for (int i = 0; i < 16; i++)
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