/********************************
*								*
*	Legacy Model Types.hlsli	*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
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