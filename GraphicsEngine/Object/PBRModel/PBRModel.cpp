/********************************
*								*
*	PBR Model.h					*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/07		*
*********************************/

#include "PBRModel.h"

namespace GraphicsEngineSpace
{
	PBRModel::PBRModel()
		: prefab(nullptr)
		, PBR_VSParameter{}
		, PBR_PSParameter{}
	{
		PBR_PSParameter.albedo[0] = 1.0f;
		PBR_PSParameter.albedo[1] = 1.0f;
		PBR_PSParameter.albedo[2] = 1.0f;
		PBR_PSParameter.metallic = 0.5f;
		PBR_PSParameter.roughness = 0.2f;
	}

	PBRModel::~PBRModel()
	{

	}

	void PBRModel::SetPrefab(PrefabBase* prefab)
	{
		this->prefab = prefab;
	}

	void PBRModel::SetAlbedo(const Vector& albedo)
	{
		PBR_VSParameter.albedo[0] = albedo.x;
		PBR_VSParameter.albedo[1] = albedo.y;
		PBR_VSParameter.albedo[2] = albedo.z;
		PBR_PSParameter.albedo[0] = albedo.x;
		PBR_PSParameter.albedo[1] = albedo.y;
		PBR_PSParameter.albedo[2] = albedo.z;
	}

	void PBRModel::SetAlpha(float alpha)
	{
		if (alpha < 0.0f)
			alpha = 0.0f;
		else if (alpha > 1.0f)
			alpha = 1.0f;

		PBR_VSParameter.alpha = alpha;
		PBR_PSParameter.alpha = alpha;
	}

	void PBRModel::SetMetallic(float metallic)
	{
		if (metallic < 0.0f)
			metallic = 0.0f;
		else if (metallic > 1.0f)
			metallic = 1.0f;

		PBR_PSParameter.metallic = metallic;
	}

	void PBRModel::SetRoughness(float roughness)
	{
		if (roughness < 0.0f)
			roughness = 0.0f;
		else if (roughness > 1.0f)
			roughness = 1.0f;

		PBR_PSParameter.roughness = roughness;
	}

	bool PBRModel::PrepareRender(const Matrix& worldTransform, float animationTime)
	{
		if (prefab == nullptr)
			assert(0);

		return prefab->PrepareRender(worldTransform, animationTime);
	}

	void PBRModel::Render(GraphicsEngineBase* engine)
	{
		if (prefab == nullptr)
			assert(0);

		prefab->Render(engine);
	}
}