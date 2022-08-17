/********************************
*								*
*	Shadow VS.hlsl				*
*								*
*	Created : 2022/08/16		*
*	Updated : 2022/08/16		*
*********************************/

#include "ShadowTypes.hlsli"

/* Matrix */
cbuffer cbMatrix : register( b0 )
{
	matrix World;
	matrix WorldInvTranspose;
}

/* Bone Matrix */
cbuffer cbBoneMatrix : register ( b3 )
{
	matrix BoneMatrix[64];
}

/* Light View Projection */
cbuffer cbLightViewProjection : register( b7 )
{
	matrix LightViewProjection;
}

/* Input */
struct VS_Basic_Input
{
	float4 Position : POSITION;
};

struct VS_Skinning_Input
{
	float4 Position		: POSITION;
	float4 Weights1		: BLENDWEIGHT0;
	float4 Weights2		: BLENDWEIGHT1;
	uint4  WeightIndex1	: BLENDINDICES0;
	uint4  WeightIndex2	: BLENDINDICES1;
};

/* VS Main - Basic */
VS_Output BasicMain(VS_Basic_Input input)
{
	VS_Output output = (VS_Output)0;

	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, LightViewProjection);

	return output;
}

/* VS Main - Skinning */
VS_Output SkinningMain(VS_Skinning_Input input)
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
		input.Weights2.w
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

	for (int i = 0; i < 8; i++)
	{
		pos += weight[i] * mul( input.Position, BoneMatrix[index[i]] ).xyz;
	}

	output.Position = mul( float4( pos, 1.0f ), LightViewProjection );

	return output;
}