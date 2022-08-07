/********************************
*								*
*	PBR Model.h					*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/07		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"
#include "Bases/PrefabBase.h"

namespace GraphicsEngineSpace
{
	class PBRBuilder;

	class PBRModel : public ResourceBase<PBRModel>
	{
		struct PBR_VSParameterCB
		{
			float albedo[3];
			float alpha;
		} PBR_VSParameter;

		struct PBR_PSParameterCB
		{
			Vector lightDirection[3];
			Vector lightColor[3];

			float albedo[3];
			float alpha;
			float metallic;
			float roughness;
		} PBR_PSParameter;

		PrefabBase* prefab;

	public:
		PBRModel();
		virtual ~PBRModel();

		PrefabBase* const GetPrefab() { return prefab; }

		virtual void SetLightDirection(const Vector& lightDirection, int index);
		virtual void SetLightColor(const Vector& lightColor, int index);
		virtual void SetPrefab(PrefabBase* prefab);
		virtual void SetAlbedo(const Vector& albedo);
		virtual void SetAlpha(float alpha);
		virtual void SetMetallic(float metallic);
		virtual void SetRoughness(float roughness);

		virtual void Render(GraphicsEngineBase* engine, const Matrix& worldTransform, float tick);

		template <typename T>
		void CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor);

		friend PBRBuilder;
	};

	template<typename T>
	inline void PBRModel::CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor)
	{
		if (prefab == nullptr)
			return;

		prefab->CreateVertexBuffer<T>(factory, vertexConstructor);
	}
}