/********************************
*								*
*	Shadow PS.hlsl				*
*								*
*	Created : 2022/08/16		*
*	Updated : 2022/08/16		*
*********************************/

#include "ShadowTypes.hlsli"

/* PS Main */
float4 main(VS_Output input) : SV_TARGET0
{
	return float4( (float3)input.Position.z, 1.0f );
}