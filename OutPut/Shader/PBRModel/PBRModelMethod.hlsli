/********************************
*								*
*	PBR Model Method.hlsli		*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/07		*
*********************************/

/* IBL Texture */
TextureCube<float3> Radiance   : register( t5 );
TextureCube<float3> Irradiance : register( t6 );

/* Sampler */
sampler   Sampler    : register( s0 );

/* Math Variable */
static const float PI = 3.14159265f;
static const float EPSILON = 1e-6f;

/* Pixel Lighting */
struct PixelLighting
{
	float4 Position;
	float4 WorldPos;
	float3 Normal;
};

// RadianceMipLevel
cbuffer cbRadianceMipLevels : register( b4 )
{
	int RadianceMipLevels[4];
}

/* Fresnel Shlick */
float3 FresnelShlick(float3 f0, float3 f90, float x)
{
	return f0 + ( f90 - f0 ) * pow( 1.0f - x, 5.0f );
}

/* Diffuse Burley */
float DiffuseBurley(float NDotL, float NDotV, float LDotH, float roughness)
{
	float fd90 = 0.5f + 2.0f * roughness * LDotH * LDotH;

	return FresnelShlick( 1, fd90, NDotL ).x * FresnelShlick( 1, fd90, NDotV ).x;
}

/* Specular D GGX */
float SpecularD_GGX(float alpha, float NDotH)
{
	const float alpha2 = alpha * alpha;
	const float lower = NDotH * NDotH * (alpha2 - 1.0f) + 1.0f;

	return alpha2 / max( EPSILON, PI * lower * lower );
}

/* Specular G Schlick-Smith */
float G_ShlickSmithHable(float alpha, float LDotH)
{
	return rcp( lerp( LDotH * LDotH, 1, alpha * alpha * 0.25f ) ) ;
}

/* Specular BRDF */
float3 SpecularBRDF(float alpha, float3 specularColor, float NDotV, float NDotL, float LDotH, float NDotH)
{
	float D = SpecularD_GGX( alpha, NDotH );

	float3 F = FresnelShlick( specularColor, 1, LDotH );

	float G = G_ShlickSmithHable( alpha, LDotH );

	return D * F * G;
}

/* IBL */
float3 DiffuseIBL(float3 Normal)
{
	return Irradiance.Sample( Sampler, Normal );
}

float3 SpecularIBL(float3 Normal, float3 View, float lodBias)
{
	float mip = lodBias * RadianceMipLevels[0];
	float3 dir = reflect( -View, Normal );
	
	return Radiance.SampleLevel( Sampler, dir, mip );
}

/* Light Surface */
float3 LightSurface(
	float3 View,
	float3 Normal,
	int lightsAmount,
	float3 lightColor[21],
	float3 lightDirection[21],
	float3 albedo, float roughness, float metallic,	float ao)
{
	static const float specularCoefficient = 0.04f;

	const float NDotV = saturate( dot( Normal, View) );

	roughness = clamp(roughness, 0.04f, 1.0f);

	const float alpha = roughness * roughness;

	const float3 diffuseColor = lerp( albedo, (float3)0, metallic ) * ao;
	const float3 specularColor = lerp( specularCoefficient, albedo, metallic ) * ao;

	float3 ret = 0;

	[unroll]
	for (int i = 0; i < lightsAmount; i++)
	{
		const float3 L = normalize(lightDirection[i]);

		const float3 H = normalize(L + View);

		const float NDotL = saturate( dot( Normal, L ) );
		const float LDotH = saturate( dot( L, H ) );
		const float NDotH = saturate( dot( Normal, H ) );

		float diffuseFactor = DiffuseBurley( NDotL, NDotV, LDotH, roughness );
		float3 specular = SpecularBRDF( alpha, specularColor, NDotV, NDotL, LDotH, NDotH );

		ret += NDotL * lightColor[i] * ( diffuseColor * diffuseFactor + specular );
	}

	float3 diffuseEnvironment = DiffuseIBL( Normal );
	ret += diffuseEnvironment * diffuseColor;
	
	float3 specularEnvironment = SpecularIBL(Normal, View, roughness);
	ret += specularEnvironment * specularColor;

	return ret;
}