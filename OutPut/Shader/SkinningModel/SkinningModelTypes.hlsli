/********************************
*								*
*	Skinning Model Types.hlsl	*
*								*
*	Created : 2022/08/01		*
*	Updated : 2022/08/01		*
*********************************/

/* Output */
struct VS_Output
{
	float4 Position : SV_POSITION;
	float3 WorldPos : COLOR0;
	float3 Normal	: NORMAL;
	float2 TexCoord	: TEXCOORD0;
	float3 Tangent  : TANGENT0;
};