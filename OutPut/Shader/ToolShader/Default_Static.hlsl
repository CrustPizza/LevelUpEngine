cbuffer CB_PERFRAME :register(b0)
{
	float4x4 transform;
	float4x4 world;
};

cbuffer CB_LIGHTVIEWPOJ:register(b1)
{
	float4 lightDirection;
};

cbuffer CB_PALLETE:register(b2)
{
	float4x4 palette[256];
};

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord1 : TEXCOORD1;
	float2 texcoord2 : TEXCOORD2;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
	float4 bone : BONE;
	float4 weight : WEIGHT;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord1 : TEXCOORD1;
	float3 lightDirection : LIGHT;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
	VS_OUTPUT Output;	
	float3 N = mul(world, input.normal);
	float3 T = mul(world, input.tangent);
	float3 B = mul(world, input.binormal);

	float3x3 Tangent = { T,B,N };

	Output.lightDirection = mul(Tangent,lightDirection.xyz );
    Output.position = mul(transform, input.position);
	Output.texcoord1 = input.texcoord1;

	return Output;
}


SamplerState textureSampler;
Texture2D textureMap:register(t0);
Texture2D normalMap:register(t1);


float4 PSMain(VS_OUTPUT input) : SV_TARGET
{
	float3 L = -normalize(input.lightDirection);

	float4 D = textureMap.Sample(textureSampler, input.texcoord1);
	float3 N = normalMap.Sample(textureSampler, input.texcoord1).xyz*2.0f - 1.0f;
	N = normalize(N);

	// return saturate(dot(N,L))*D + 0.2F;
	return D;
}