/********************************
*								*
*	Transform.h					*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GameEngineSpace
{
	using namespace HeraclesMath;

	class Transform
	{
	private:
		Matrix localTransform;
		Matrix worldTransform;
		Matrix parentWorldTransform;

		Vector originalPosition;
		Vector originalRotation;
		Vector originalScale;

	public:
		Vector position;
		Vector rotation;
		Vector scale;

	public:
		Transform();
		~Transform();

		Matrix& GetWorldTransform();

		void UpdateWorldTransform();
		void UpdateWorldTransform(const Matrix& parentTransform);
		void DecomposeWorldTransform(const Matrix& matrix);

	private:
		void UpdateLocalTransform();
		void DecomposeLocalTransform(Matrix local);
		void DecomposeWorldTransform();

		void DecomposeMatrix(Vector& scale, Vector& rotation, Vector& translation, Matrix matrix);
	};
}