/********************************
*								*
*	PBR Model VS.hlsl			*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/05		*
*********************************/

#include "PBRModelTypes.hlsli"

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

/* Parameter */
cbuffer cbPBRParameter : register( b2 )
{
	float3 Albedo;
	float  Alpha;
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
	float4 Normal	: NORMAL;
	float4 TexCoord : TEXCOORD0;
};

struct VS_Normal_Input
{
	float4 Position : POSITION;
	float4 Normal	: NORMAL;
	float4 TexCoord : TEXCOORD0;
	float4 Tangent  : TANGENT0;
};

struct VS_Skinning_Input
{
	float4 Position		: POSITION;
	float4 Normal		: NORMAL;
	float4 TexCoord		: TEXCOORD0;
	float4 Weights1		: BLENDWEIGHT0;
	float4 Weights2		: BLENDWEIGHT1;
	float4 Weights3		: BLENDWEIGHT2;
	float4 Weights4		: BLENDWEIGHT3;
	uint4  WeightIndex1	: BLENDINDICES0;
	uint4  WeightIndex2	: BLENDINDICES1;
	uint4  WeightIndex3	: BLENDINDICES2;
	uint4  WeightIndex4	: BLENDINDICES3;
};

struct VS_SkinningNormal_Input
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

/* VS Main - Basic */
VS_Default_Output BasicMain(VS_Basic_Input input)
{
	VS_Default_Output output = (VS_Default_Output)0;

	output.WorldPos = mul( input.Position, World ).xyz;
	output.Position = mul( float4( output.WorldPos, 1.0f ), ViewProjection );
	output.Normal = normalize( mul( input.Normal.xyz, (float3x3)WorldInvTranspose ) );
	output.Diffuse = float4( Albedo, Alpha );
	output.TexCoord = input.TexCoord.xy;
	output.ShadowDepth = mul( float4( output.WorldPos, 1.0f ), LightViewProjection );

	return output;
}

/* VS Main - Normal */
VS_Normal_Output NormalMain(VS_Normal_Input input)
{
	VS_Normal_Output output = (VS_Normal_Output)0;

	output.WorldPos = mul( input.Position, World ).xyz;
	output.Position = mul( float4( output.WorldPos, 1.0f ), ViewProjection );
	output.Normal = normalize( mul( input.Normal.xyz, (float3x3)WorldInvTranspose ) );
	output.Diffuse = float4( Albedo, Alpha );
	output.TexCoord = input.TexCoord.xy;
	output.Tangent = mul( input.Tangent.xyz, (float3x3)World );
	output.ShadowDepth = mul( float4( output.WorldPos, 1.0f ), LightViewProjection );

	return output;
}

/* VS Main - Skinning */
VS_Default_Output SkinnedMain(VS_Skinning_Input input)
{
	VS_Default_Output output = (VS_Default_Output)0;

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
	output.Diffuse = float4( Albedo, Alpha );
	output.TexCoord = input.TexCoord.xy;
	output.ShadowDepth = mul( float4( output.WorldPos, 1.0f ), LightViewProjection );

	return output;
}

/* VS Main - Skinning Normal */
VS_Normal_Output SkinnedNormalMain(VS_SkinningNormal_Input input)
{
	VS_Normal_Output output = (VS_Normal_Output)0;

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
	output.Diffuse = float4( Albedo, Alpha );
	output.TexCoord = input.TexCoord.xy;
	output.Tangent = mul( input.Tangent.xyz, (float3x3)World );
	output.ShadowDepth = mul( float4( output.WorldPos, 1.0f ), LightViewProjection );

	return output;
}