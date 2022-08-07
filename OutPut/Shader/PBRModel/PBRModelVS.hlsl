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
	float4 Weights		: BLENDWEIGHT0;
	uint4  WeightIndex	: BLENDINDICES0;
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

	return output;
}

/* VS Main - Skinning */
VS_Default_Output SkinnedMain(VS_Skinning_Input input)
{
	VS_Default_Output output = (VS_Default_Output)0;

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
	output.Diffuse = float4( Albedo, Alpha );
	output.TexCoord = input.TexCoord.xy;

	return output;
}