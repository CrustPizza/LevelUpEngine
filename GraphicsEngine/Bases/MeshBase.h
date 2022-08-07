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
		int		weightIndex;
		Vector	weights;
		Vector	tangent;
		Vector	binormal;
	};

	class MeshBase : public ObjectBase
	{
		std::vector<VertexData> vertices;

		BufferBase* indexBuffer;
		std::map<std::string, AnimationBase*> animations;

	public:
		MeshBase()
			: indexBuffer(nullptr) {}
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

			return result->second->UpdateAnimation(&GetTransform(), tick);
		}

		BufferBase* GetIndexBuffer() { return indexBuffer; }
		const std::vector<VertexData>& GetVertexData() { return vertices; }
		std::map<std::string, AnimationBase*>& GetAnimation() { return animations; }

	protected:
		bool SetIndexBuffer(BufferBase* indexBuffer) { this->indexBuffer = indexBuffer;	}

		friend ASEBuilder;
	};
}