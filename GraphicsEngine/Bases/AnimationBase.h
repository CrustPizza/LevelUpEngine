/********************************
*								*
*	Animation Base.h			*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include <vector>
#include "Bases/ResourceBase.h"
#include "Transform/Transform.h"
#include "../HeraclesMath/HeraclesMath.h"

namespace GraphicsEngineSpace
{
	class ASEBuilder;

	using HeraclesMath::Vector;

	struct AnimationData
	{
		float tick;
		Vector vec;
	};

	class AnimationBase : public ResourceBase<AnimationBase>
	{
		std::vector<AnimationData> positions;
		std::vector<AnimationData> rotations;

	public:
		AnimationBase() = default;
		virtual ~AnimationBase() = default;

		bool UpdateAnimation(Transform* transform, float animTime)
		{
			bool reset = true;

			if (animTime < 0.0f)
			{
				if (rotations.empty() != true)
				{
					Vector quat = rotations.back().vec;
					transform->SetRotation(ConvertQuaternionToEuler(quat));
				}
				
				if (positions.empty() != true)
				{
					Vector pos = positions.back().vec;
					transform->SetPosition(pos);
				}

				return true;
			}

			for (int i = 1; i < rotations.size(); i++)
			{
				float destTick = rotations[i - 1].tick;
				float srcTick = rotations[i].tick;

				if (animTime < destTick)
				{
					reset = false;

					break;
				}

				if (animTime < srcTick)
				{
					float ratio = (animTime - destTick) / (srcTick - destTick);
					Vector quat = QuaternionSlerp(rotations[i - 1].vec, rotations[i].vec, ratio);

					transform->SetRotation(ConvertQuaternionToEuler(quat));

					reset = false;

					break;
				}
			}

			for (int i = 1; i < positions.size(); i++)
			{
				float destTick = positions[i - 1].tick;
				float srcTick = positions[i].tick;

				if (animTime < destTick)
				{
					reset = false;

					break;
				}

				if (animTime < srcTick)
				{
					float ratio = (animTime - destTick) / (srcTick - destTick);
					Vector pos = VectorLerp(positions[i - 1].vec, positions[i].vec, ratio);

					transform->SetPosition(pos);

					reset = false;

					break;
				}
			}

			return !reset;
		}

	private:
		friend ASEBuilder;
	};
}