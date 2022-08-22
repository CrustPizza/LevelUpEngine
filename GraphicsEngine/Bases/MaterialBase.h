/********************************
*								*
*	Material Base.h				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/07/27		*
*********************************/

#pragma once

#include <vector>
#include "Bases/ResourceBase.h"
#include "Bases/BufferBase.h"
#include "Bases/TextureBase.h"

namespace GraphicsEngineSpace
{
	enum class MapType
	{
		NONE,
		DIFFUSE,
		SPECULAR,
		NORMAL,
		SHINE,
		METALLIC,
		ROUGHNESS,
		AMBIENTOCCLUSION
	};

	struct MapData
	{
		TextureBase* map;
		MapType type;

		float offset[2];
		float tiling[2];
	};

	struct MaterialData
	{
		float ambient[3];
		float diffuse[4];
		float specular[3];

		std::vector<MapData> maps;

		// 추가로 필요하다고 생각되는 것은 필요할 때 추가하자..
	};

	class MaterialBase : public ResourceBase<MaterialBase>
	{
		BufferBase* constantBuffer;
		MaterialData material;

	public:
		MaterialBase()
			: constantBuffer(nullptr)
			, material{} {}
		virtual ~MaterialBase() = default;

		MaterialData& GetMaterialData() { return material; }

		void SetMaterial(MaterialData material) { this->material = material; }
	};
}