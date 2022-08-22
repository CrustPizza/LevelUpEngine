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

		virtual void SetPrefab(PrefabBase* prefab);
		virtual void SetAlbedo(const Vector& albedo);
		virtual void SetAlpha(float alpha);
		virtual void SetMetallic(float metallic);
		virtual void SetRoughness(float roughness);

		virtual bool PrepareRender(const Matrix& worldTransform, float animationTime);
		virtual void Render(GraphicsEngineBase* engine);

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