/********************************
*								*
*	Math.h						*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/07/22		*
*********************************/

#pragma once

namespace Math
{
	constexpr float PI = 3.14159265359f;

	class Matrix;

	union Vector
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		int i[4];
		float v[4];
		unsigned int u[4];

		float& operator [](int index);
		const float& operator [](int index) const;

		Vector& operator =(const float fVector[4]);

		Vector& operator +=(const Vector& other);
		Vector& operator -=(const Vector& other);
		Vector& operator *=(float scalar);
		Vector& operator /=(float scalar);
		Vector& operator /=(const Vector& other);

		Vector operator +(const Vector& other);
		Vector operator +(const Vector& other) const;

		Vector operator -(const Vector& other);
		Vector operator -(const Vector& other) const;

		Vector operator *(float scalar);
		Vector operator *(const Vector& other);
		Vector operator *(const Vector& other) const;
		Vector operator *(const Matrix& other);
		
		Vector operator /(float scalar);
		Vector operator /(const Vector& other);
		Vector operator /(const Vector& other) const;
	};

	Vector operator *(float scalar, Vector& vec);

	struct Matrix
	{
		union
		{
			Vector r[4];
			float m[4][4];
		};

		Vector& operator [](int index);
		const Vector& operator [](int index) const;

		Matrix& operator =(const Vector vMatrix[4]);
		Matrix& operator =(const float fMatrix[4][4]);

		Matrix operator *(const Matrix& other);
		Matrix operator *(const Matrix& other) const;
	};

	Vector VectorZero();

	bool Vector3Equal(const Vector& v1, const Vector& v2);
	bool Vector3IsInfinite(const Vector& v);

	float Vector3Length(const Vector& v);
	float Vector3Dot(const Vector& v1, const Vector& v2);
	Vector Vector3Cross(const Vector& v1, const Vector& v2);
	Vector Vector3Normalize(Vector v);
	Vector VectorReciprocal(const Vector& v);
	Vector VectorReplicate(float value);

	Vector QuaternionMultiply(const Vector& q1, const Vector& q2);

	Matrix MatrixIdentity();
	Matrix MatrixInverse(Matrix matrix);
	Matrix MatrixTranspose(const Matrix& matrix);

	Matrix PerspectiveMatrix(float fovY, float aspectRatio, float nearZ, float farZ);
	Matrix ViewMatrix(Vector position, Vector rotation);

	Matrix MatrixScalingFromVector(Vector scale);
	Matrix MatrixRotationFromVector(Vector rotation);
	Matrix MatrixTranslationFromVector(Vector translation);

	Vector ConvertRotationNormalToQuaternion(const Vector& normalAxis, float angle);
	Vector ConvertRotationAxisAngleToQuaternion(const Vector& axis, float angle);
	Vector ConvertRotationMatrixToQuaternion(const Matrix& matrix);
	Vector ConvertQuaternionToEuler(const Vector& quaternion);
	Vector ConvertRotationMatrixToEuler(const Matrix& matrix);
	
	float ConvertDegreeToRadian(float degree);
	float ConvertRadianToDegree(float radian);
	void ConvertRadianToScalarSinCos(float& fSin, float& fCos, float radian);

	float ComputeGaussian(float n, float theta);
}