/********************************
*								*
*	Transform.cpp				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/07/19		*
*********************************/

#include <math.h>
#include "Transform.h"
#include "Bases/ObjectBase.h"

namespace GraphicsEngineSpace
{
	Transform::Transform(ObjectBase* object)
		: localTransform{ MatrixIdentity() }
		, worldTransform{}
		, parentWorldTransform{ MatrixIdentity() }
		, originalPosition(Vector::Zero)
		, originalRotation(Vector::Zero)
		, originalScale(Vector::One)
		, position(Vector::Zero)
		, rotation(Vector::Zero)
		, scale(Vector::One)
		, object(object)
	{

	}

	Transform::~Transform()
	{

	}

	Matrix& Transform::GetWorldTransform()
	{
		return worldTransform;
	}

	Matrix& Transform::GetLocalTransform()
	{
		return localTransform;
	}

	void Transform::SetWorldTransform(const Matrix& world)
	{
		worldTransform = world;
	}

	void Transform::UpdateWorldTransform()
	{
		UpdateLocalTransform();

		ObjectBase* parent = object->GetParent();

		if (parent == nullptr)
		{
			worldTransform = localTransform;
		}
		else
		{
			worldTransform = localTransform * parent->GetTransform().worldTransform;
		}
	}

	void Transform::DecomposeWorldTransform(const Matrix& matrix)
	{
		worldTransform = matrix;

		DecomposeWorldTransform();
	}

	void Transform::DecomposeLocalTransform(Matrix local)
	{
		DecomposeMatrix(scale, rotation, position, local);
	
		UpdateLocalTransform();
	}

	void Transform::SetOriginal()
	{
		originalPosition = position;
		originalRotation = rotation;
		originalScale = scale;
	}

	void Transform::ResetLocation()
	{
		position = originalPosition;
		rotation = originalRotation;
		scale = originalScale;
	}

	void Transform::UpdateLocalTransform()
	{
		Matrix scaleMatrix = MatrixScalingFromVector(scale);
		Matrix rotationMatrix = MatrixRotationFromVector(rotation);
		Matrix translationMatrix = MatrixTranslationFromVector(position);

		localTransform = scaleMatrix * rotationMatrix * translationMatrix;
	}

	void Transform::DecomposeWorldTransform()
	{
		ObjectBase* parent = object->GetParent();

		if (parent == nullptr)
		{
			DecomposeLocalTransform(worldTransform);

			UpdateWorldTransform();

			return;
		}

		Transform* parentTransform = &parent->GetTransform();

		DecomposeLocalTransform(worldTransform * MatrixInverse(parentTransform->worldTransform));

		UpdateWorldTransform();
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