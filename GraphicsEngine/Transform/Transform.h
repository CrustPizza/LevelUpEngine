/********************************
*								*
*	Transform.h					*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GraphicsEngineSpace
{
	using namespace HeraclesMath;

	class ObjectBase;

	class Transform
	{
	private:
		Matrix localTransform;
		Matrix worldTransform;
		Matrix parentWorldTransform;

		Vector originalPosition;
		Vector originalRotation;
		Vector originalScale;

		Vector position;
		Vector rotation;
		Vector scale;

		ObjectBase* object;

	public:
		Transform(ObjectBase* object);
		~Transform();

		const Vector& GetPosition() { return position; }
		const Vector& GetRotation() { return rotation; }
		const Vector& GetScale() { return scale; }

		void SetPosition(const Vector& pos) { this->position = pos; }
		void SetRotation(const Vector& rot) { this->rotation = rot; }
		void SetScale(const Vector& scl) { this->scale = scl; }

		void Translate(const Vector& vec) { this->position += vec; }
		void Rotate(const Vector& vec) { this->rotation += vec; }
		void Scale(const Vector& vec) { this->scale *= vec; }

		virtual Matrix& GetWorldTransform();
		virtual Matrix& GetLocalTransform();

		virtual void SetWorldTransform(const Matrix& world);

		virtual void UpdateWorldTransform();
		void DecomposeWorldTransform(const Matrix& matrix);
		void DecomposeLocalTransform(Matrix local);

		void SetOriginal();
		virtual void ResetLocation();

	private:
		void UpdateLocalTransform();
		void DecomposeWorldTransform();

		void DecomposeMatrix(Vector& scale, Vector& rotation, Vector& translation, Matrix matrix);

	};
}