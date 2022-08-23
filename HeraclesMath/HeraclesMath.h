/********************************
*								*
*	HeraclesMath.h				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include <math.h>

namespace HeraclesMath
{
	constexpr float PI = 3.14159265359f;

	struct Matrix;

	struct Rect
	{
		long left;
		long top;
		long right;
		long bottom;

		long GetWidth() { return right - left; }
		long GetHeight() { return bottom - top; }
	};

	struct Vector
	{
		union
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
		};

		static const Vector Zero;
		static const Vector UnitX;
		static const Vector UnitY;
		static const Vector UnitZ;
		static const Vector UnitW;
		static const Vector One;
		static const Vector NegativeOne;
		static const Vector SignMask;

		static const Vector Left;
		static const Vector Right;
		static const Vector Up;
		static const Vector Down;
		static const Vector Forward;
		static const Vector Backward;

		static const Vector Select0101;
		static const Vector Select1010;
		static const Vector Select1000;
		static const Vector Select1100;
		static const Vector Select1110;
		static const Vector Select1011;

		Vector() = default;
		Vector(const Vector& other) = default;

		Vector(const float x, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f);
		Vector(const int i1, const int i2 = 0, const int i3 = 0, const int i4 = 0);
		Vector(const unsigned int u1, const unsigned int u2 = 0, const unsigned int u3 = 0, const unsigned int u4 = 0);

		float& operator [](int index);
		const float& operator [](int index) const;

		Vector& operator =(const float fVector[4]);

		Vector& operator +=(const Vector& other);
		Vector& operator -=(const Vector& other);
		Vector& operator *=(float scalar);
		Vector& operator *=(const Vector& other);
		Vector& operator /=(float scalar);
		Vector& operator /=(const Vector& other);

		Vector operator +(const Vector& other);
		Vector operator +(const Vector& other) const;

		Vector operator -();
		Vector operator -() const;
		Vector operator -(const Vector& other);
		Vector operator -(const Vector& other) const;

		Vector operator *(float scalar);
		Vector operator *(const Vector& other);
		Vector operator *(const Vector& other) const;
		Vector operator *(const Matrix& other);
		Vector operator *(const Matrix& other) const;

		Vector operator /(float scalar);
		Vector operator /(const Vector& other);
		Vector operator /(const Vector& other) const;

		bool operator ==(const Vector& v);
	};

	Vector operator *(float scalar, Vector& vec);

	struct Matrix
	{
		union
		{
			Vector r[4];
			float m[4][4];
		};

		static Matrix Identity;

		Matrix() = default;
		Matrix(const Matrix& other) = default;

		Matrix(const Vector& v1, const Vector& v2 = Vector::Zero, const Vector& v3 = Vector::Zero, const Vector& v4 = Vector::Zero);
		Matrix(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		Vector& operator [](int index);
		const Vector& operator [](int index) const;

		Matrix& operator =(const Vector vMatrix[4]);
		Matrix& operator =(const float fMatrix[4][4]);

		Matrix operator *(const Matrix& other);
		Matrix operator *(const Matrix& other) const;
		Vector operator *(const Vector& v);
		Vector operator *(const Vector& v) const;

		bool operator ==(const Matrix& m);
	};

	Vector VectorZero();

	bool Vector3Equal(const Vector& v1, const Vector& v2);
	bool Vector4Equal(const Vector& v1, const Vector& v2);
	bool Vector3IsInfinite(const Vector& v);

	float Vector3Length(const Vector& v);
	float Vector3Dot(const Vector& v1, const Vector& v2);
	float Vector4Dot(const Vector& v1, const Vector& v2);
	Vector Vector3Cross(const Vector& v1, const Vector& v2);
	Vector Vector3Normalize(Vector v);
	Vector Vector3Transform(const Vector& v, const Matrix& m);

	template <unsigned int elements>
	Vector VectorShiftLeft(const Vector& v1, const Vector& v2);
	template <unsigned int permuteX, unsigned int permuteY, unsigned int permuteZ, unsigned int permuteW>
	Vector VectorPermute(const Vector& v1, const Vector& v2);
	template <unsigned int swizzleX, unsigned int swizzleY, unsigned int swizzleZ, unsigned int swizzleW>
	Vector VectorSwizzle(const Vector& v);

	Vector VectorReciprocal(const Vector& v);
	Vector VectorReplicate(float value);
	Vector VectorLess(const Vector& v1, const Vector& v2);
	Vector VectorSelect(const Vector& v1, const Vector& v2, const Vector& control);
	Vector VectorXorInt(const Vector& v1, const Vector& v2);
	Vector VectorLerp(const Vector& v1, const Vector& v2, float tick);

	Vector VectorSplatX(const Vector& v);
	Vector VectorSplatY(const Vector& v);
	Vector VectorSplatZ(const Vector& v);
	Vector VectorSplatW(const Vector& v);

	Vector VectorSqrt(const Vector& v);
	Vector VectorSin(const Vector& v);
	Vector VectorCos(const Vector& v);
	Vector VectorAtan2(const Vector& y, const Vector& x);

	Matrix QuaternionToRotationMatrix(const Vector& quaternion);
	Vector QuaternionMultiply(const Vector& q1, const Vector& q2);
	Vector QuaternionSlerp(const Vector& q1, const Vector& q2, float tick);

	Matrix MatrixIdentity();
	Matrix MatrixInverse(Matrix matrix);
	Matrix MatrixTranspose(const Matrix& matrix);
	bool MatrixEqaul(const Matrix& m1, const Matrix& m2);

	Matrix MatrixLookAtLH(const Vector& eyePosition, const Vector& focusPosition, const Vector& upDirection);
	Matrix MatrixLookAtRH(const Vector& eyePosition, const Vector& focusPosition, const Vector& upDirection);
	Matrix MatrixLookAt(const Vector& eyePosition, const Vector& eyeDirection, const Vector& upDirection);

	Matrix OrthographicMatrix(float ViewWidth, float ViewHeight, float nearZ, float farZ);
	Matrix OrthographicOffCenterMatrix(float left, float right, float bottom, float top, float nearZ, float farZ);
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
	Vector ConvertEulerToQuaternion(const Vector& euler);
	Vector ConvertDegreeToRadian(const Vector& degree);
	Vector ConvertRadianToDegree(const Vector& radian);

	float ConvertDegreeToRadian(float degree);
	float ConvertRadianToDegree(float radian);
	void ConvertRadianToScalarSinCos(float& fSin, float& fCos, float radian);

	float ComputeGaussian(float n, float theta);

	template<unsigned int elements>
	Vector VectorShiftLeft(const Vector& v1, const Vector& v2)
	{
		// 마소 XMVectorShiftLeft 함수
		static_assert(elements < 4, "Elements template parameter out of range");

		return VectorPermute<elements, elements + 1, elements + 2, elements + 3>(v1, v2);
	}

	template<unsigned int permuteX, unsigned int permuteY, unsigned int permuteZ, unsigned int permuteW>
	Vector VectorPermute(const Vector& v1, const Vector& v2)
	{
		// 마소 XMVectorPermute 함수
		static_assert(permuteX < 8, "PermuteX template parameter out of range");
		static_assert(permuteY < 8, "PermuteY template parameter out of range");
		static_assert(permuteZ < 8, "PermuteZ template parameter out of range");
		static_assert(permuteW < 8, "PermuteW template parameter out of range");

		const unsigned int shuffle = (((permuteW & 3) << 6) | ((permuteZ & 3) << 4) | ((permuteY & 3) << 2) | (permuteX & 3));

		const bool whichX = permuteX > 3;
		const bool whichY = permuteY > 3;
		const bool whichZ = permuteZ > 3;
		const bool whichW = permuteW > 3;

		const unsigned int* aPtr[2];
		aPtr[0] = reinterpret_cast<const unsigned int*>(&v1);
		aPtr[1] = reinterpret_cast<const unsigned int*>(&v2);

		Vector result;
		auto* pWork = reinterpret_cast<unsigned int*>(&result);

		const unsigned int i0 = permuteX & 3;
		const unsigned int vi0 = (permuteX >> 2);
		pWork[0] = aPtr[vi0][i0];

		const unsigned int i1 = permuteY & 3;
		const unsigned int vi1 = (permuteY >> 2);
		pWork[1] = aPtr[vi1][i1];

		const unsigned int i2 = permuteZ & 3;
		const unsigned int vi2 = (permuteZ >> 2);
		pWork[2] = aPtr[vi2][i2];

		const unsigned int i3 = permuteW & 3;
		const unsigned int vi3 = (permuteW >> 2);
		pWork[3] = aPtr[vi3][i3];

		return result;
	}

	template<unsigned int swizzleX, unsigned int swizzleY, unsigned int swizzleZ, unsigned int swizzleW>
	Vector VectorSwizzle(const Vector& v)
	{
		// 마소 XMVectorSwizzle 함수
		static_assert(swizzleX < 4, "SwizzleX template parameter out of range");
		static_assert(swizzleY < 4, "SwizzleY template parameter out of range");
		static_assert(swizzleZ < 4, "SwizzleZ template parameter out of range");
		static_assert(swizzleW < 4, "SwizzleW template parameter out of range");

		return Vector
		{
			v[swizzleX],
			v[swizzleY],
			v[swizzleZ],
			v[swizzleW]
		};
	}
}