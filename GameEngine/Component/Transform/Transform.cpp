/********************************
*								*
*	Transform.cpp				*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "Transform.h"
#include <math.h>

namespace GameEngineSpace
{
	Transform::Transform()
		: localTransform{ MatrixIdentity() }
		, worldTransform{}
		, parentWorldTransform{ MatrixIdentity() }
		, originalPosition{}
		, originalRotation{}
		, originalScale{ 1.0f, 1.0f, 1.0f, 1.0f }
		, position{}
		, rotation{}
		, scale{ 1.0f, 1.0f, 1.0f, 1.0f }
	{

	}

	Transform::~Transform()
	{

	}

	Matrix& Transform::GetWorldTransform()
	{
		return worldTransform;
	}

	void Transform::UpdateWorldTransform()
	{
		UpdateLocalTransform();

		worldTransform = localTransform * parentWorldTransform;
	}

	void Transform::UpdateWorldTransform(const Matrix& parentTransform)
	{
		UpdateLocalTransform();

		parentWorldTransform = parentTransform;

		UpdateWorldTransform();
	}

	void Transform::DecomposeWorldTransform(const Matrix& matrix)
	{
		worldTransform = matrix;

		DecomposeWorldTransform();
	}

	void Transform::UpdateLocalTransform()
	{
		Vector rad =
		{
			ConvertDegreeToRadian(rotation[0] + originalRotation[0]),
			ConvertDegreeToRadian(rotation[1] + originalRotation[1]),
			ConvertDegreeToRadian(rotation[2] + originalRotation[2]),
		};

		Matrix scaleMatrix = MatrixScalingFromVector(scale * originalScale);
		Matrix rotationMatrix = MatrixRotationFromVector(rad);
		Matrix translationMatrix = MatrixTranslationFromVector(position + originalPosition);

		localTransform = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void Transform::DecomposeLocalTransform(Matrix local)
	{
		localTransform = local;

		DecomposeMatrix(originalScale, originalRotation, originalPosition, local);

		originalPosition -= position;
		originalRotation -= rotation;
		originalScale /= scale;
	}

	void Transform::DecomposeWorldTransform()
	{
		Matrix parentInvWorld = MatrixInverse(parentWorldTransform);

		DecomposeLocalTransform(worldTransform * parentInvWorld);
	}

	void Transform::DecomposeMatrix(Vector& scale, Vector& rotation, Vector& translation, Matrix matrix)
	{
		// Position, Scale
		for (int i = 0; i < 3; i++)
		{
			translation[i] = matrix[3][i];
			scale[i] = sqrtf(powf(matrix[0][i], 2.0f) + powf(matrix[1][i], 2.0f) + powf(matrix[2][i], 2.0f));
		}
		translation[3] = 1.0f;
		scale[3] = 0.0f;

		// Negative Scale
		if (Vector3Dot(Vector3Cross(matrix[0], matrix[1]), matrix[2]) < 0.0f)
		{
			scale *= -1.0f;
		}

		// Rotation
		for (int i = 0; i < 3; i++)
		{
			matrix[i] /= scale[i];
		}

		rotation = ConvertRotationMatrixToEuler(matrix);
	}
}