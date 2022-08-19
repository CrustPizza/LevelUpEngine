/********************************
*								*
*	Mesh Base.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/08/02		*
*********************************/

#pragma once

#include <map>
#include <vector>
#include "Bases/ObjectBase.h"
#include "Bases/BufferBase.h"
#include "Bases/AnimationBase.h"
#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GraphicsEngineSpace
{
	class ASEBuilder;

	using namespace HeraclesMath;

	struct VertexData
	{
		Vector	position;
		Vector	normal;
		Vector	texCoord;
		int		materialIndex;
		Vector	weights1;
		Vector	weights2;
		Vector	weights3;
		Vector	weights4;
		unsigned int	weightIndex1;
		unsigned int	weightIndex2;
		unsigned int	weightIndex3;
		unsigned int	weightIndex4;
		Vector	tangent;
		Vector	binormal;
	};

	class MeshBase : public ObjectBase
	{
		std::vector<VertexData> vertices;

		BufferBase* indexBuffer;
		std::map<std::string, AnimationBase*> animations;

		Vector boundingBoxMin;
		Vector boundingBoxMax;

	public:
		MeshBase()
			: indexBuffer(nullptr)
			, boundingBoxMin{ 0.0f, 0.0f, 0.0f, 1.0f }
			, boundingBoxMax{ 0.0f, 0.0f, 0.0f, 1.0f } {}
		virtual ~MeshBase()
		{
			for (auto iter : animations)
			{
				if (iter.second != nullptr)
					delete iter.second;
			}
		}

		bool UpdateAnimation(const std::string& animationKey, float tick)
		{
			auto result = animations.find(animationKey);

			if (result == animations.end())
				return false;

			GetTransform().ResetLocation();

			return result->second->UpdateAnimation(&GetTransform(), tick);
		}

		BufferBase* GetIndexBuffer() { return indexBuffer; }
		const std::vector<VertexData>& GetVertexData() { return vertices; }
		std::map<std::string, AnimationBase*>& GetAnimation() { return animations; }

	protected:
		bool SetIndexBuffer(BufferBase* indexBuffer) { this->indexBuffer = indexBuffer; }

		friend ASEBuilder;
	};
}