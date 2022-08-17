/********************************
*								*
*	PBR Model Types.hlsli		*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/04		*
*********************************/

/* Output */
struct VS_Default_Output
{
	float4 Position : SV_POSITION;
	float3 WorldPos : COLOR0;
	float3 Normal   : NORMAL;
	float2 TexCoord : TEXCOORD0;
	float4 Diffuse  : COLOR1;
	float4 ShadowDepth : COLOR2;
};

struct VS_Normal_Output
{
	float4 Position : SV_POSITION;
	float3 WorldPos : COLOR0;
	float3 Normal   : NORMAL;
	float2 TexCoord : TEXCOORD0;
	float4 Diffuse  : COLOR1;
	float3 Tangent  : TANGENT0;
	float4 ShadowDepth : COLOR2;
};