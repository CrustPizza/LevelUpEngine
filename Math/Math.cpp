/********************************
*								*
*	Math.cpp					*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/07/20		*
*********************************/

#include "Math.h"
#include <math.h>
#include <assert.h>

#define MAT_MUL_MAT(result, dest, src, col, row) \
(result)[##col##][##row##] = \
(dest)[##col##][0] * (src)[0][##row##] \
+ (dest)[##col##][1] * (src)[1][##row##] \
+ (dest)[##col##][2] * (src)[2][##row##] \
+ (dest)[##col##][3] * (src)[3][##row##]

#define VEC_MUL_MAT(dest, src, row) \
(dest).x * (src)[0][##row##] \
+ (dest).y * (src)[1][##row##] \
+ (dest).z * (src)[2][##row##] \
+ (dest).w * (src)[3][##row##]

namespace Math
{
	float& Vector::operator[](int index)
	{
		return v[index];
	}

	const float& Vector::operator[](int index) const
	{
		return v[index];
	}

	Vector& Vector::operator=(const float fVector[4])
	{
		this->x = fVector[0];
		this->y = fVector[1];
		this->z = fVector[2];
		this->w = fVector[3];

		return *this;
	}

	Vector& Vector::operator+=(const Vector& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;

		return *this;
	}

	Vector& Vector::operator-=(const Vector& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;

		return *this;
	}

	Vector& Vector::operator*=(float scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	Vector& Vector::operator/=(float scalar)
	{
		*this = *this / scalar;

		return *this;
	}

	Vector& Vector::operator/=(const Vector& other)
	{
		*this = *this / other;
		
		return *this;
	}

	Vector Vector::operator+(const Vector& other)
	{
		return Vector
		{
			this->x + other.x,
			this->y + other.y,
			this->z + other.z,
			this->w + other.w
		};
	}

	Vector Vector::operator+(const Vector& other) const
	{
		return Vector
		{
			this->x + other.x,
			this->y + other.y,
			this->z + other.z,
			this->w + other.w
		};
	}

	Vector Vector::operator-(const Vector& other)
	{
		return Vector
		{
			this->x - other.x,
			this->y - other.y,
			this->z - other.z,
			this->w - other.w
		};
	}

	Vector Vector::operator-(const Vector& other) const
	{
		return Vector
		{
			this->x - other.x,
			this->y - other.y,
			this->z - other.z,
			this->w - other.w
		};
	}

	Vector Vector::operator*(float scalar)
	{
		return Vector
		{
			this->x * scalar,
			this->y * scalar,
			this->z * scalar,
			this->w * scalar
		};
	}

	Vector Vector::operator*(const Vector& other)
	{
		return Vector
		{
			this->x * other.x,
			this->y * other.y,
			this->z * other.z,
			this->w * other.w
		};
	}

	Vector Vector::operator*(const Vector& other) const
	{
		return Vector
		{
			this->x * other.x,
			this->y * other.y,
			this->z * other.z,
			this->w * other.w
		};
	}

	Vector Vector::operator*(const Matrix& other)
	{
		return Vector
		{
			VEC_MUL_MAT(*this, other, 0),
			VEC_MUL_MAT(*this, other, 1),
			VEC_MUL_MAT(*this, other, 2),
			VEC_MUL_MAT(*this, other, 3)
		};
	}

	Vector Vector::operator/(float scalar)
	{
		return Vector
		{
			this->x / scalar,
			this->y / scalar,
			this->z / scalar,
			this->w / scalar
		};
	}

	Vector Vector::operator/(const Vector& other)
	{
		return *this * VectorReciprocal(other);
	}

	Vector Vector::operator/(const Vector& other) const
	{
		return *this * VectorReciprocal(other);
	}

	Vector& Matrix::operator[](int index)
	{
		return r[index];
	}

	const Vector& Matrix::operator[](int index) const
	{
		return r[index];
	}

	Matrix& Matrix::operator=(const Vector vMatrix[4])
	{
		this->r[0] = vMatrix[0];
		this->r[1] = vMatrix[1];
		this->r[2] = vMatrix[2];
		this->r[3] = vMatrix[3];

		return *this;
	}

	Matrix& Matrix::operator=(const float fMatrix[4][4])
	{
		this->r[0] = fMatrix[0];
		this->r[1] = fMatrix[1];
		this->r[2] = fMatrix[2];
		this->r[3] = fMatrix[3];

		return *this;
	}

	Matrix Matrix::operator*(const Matrix& other)
	{
		Matrix result;

		MAT_MUL_MAT(result, *this, other, 0, 0);
		MAT_MUL_MAT(result, *this, other, 0, 1);
		MAT_MUL_MAT(result, *this, other, 0, 2);
		MAT_MUL_MAT(result, *this, other, 0, 3);

		MAT_MUL_MAT(result, *this, other, 1, 0);
		MAT_MUL_MAT(result, *this, other, 1, 1);
		MAT_MUL_MAT(result, *this, other, 1, 2);
		MAT_MUL_MAT(result, *this, other, 1, 3);

		MAT_MUL_MAT(result, *this, other, 2, 0);
		MAT_MUL_MAT(result, *this, other, 2, 1);
		MAT_MUL_MAT(result, *this, other, 2, 2);
		MAT_MUL_MAT(result, *this, other, 2, 3);

		MAT_MUL_MAT(result, *this, other, 3, 0);
		MAT_MUL_MAT(result, *this, other, 3, 1);
		MAT_MUL_MAT(result, *this, other, 3, 2);
		MAT_MUL_MAT(result, *this, other, 3, 3);

		return result;
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{
		Matrix result;

		MAT_MUL_MAT(result, *this, other, 0, 0);
		MAT_MUL_MAT(result, *this, other, 0, 1);
		MAT_MUL_MAT(result, *this, other, 0, 2);
		MAT_MUL_MAT(result, *this, other, 0, 3);

		MAT_MUL_MAT(result, *this, other, 1, 0);
		MAT_MUL_MAT(result, *this, other, 1, 1);
		MAT_MUL_MAT(result, *this, other, 1, 2);
		MAT_MUL_MAT(result, *this, other, 1, 3);

		MAT_MUL_MAT(result, *this, other, 2, 0);
		MAT_MUL_MAT(result, *this, other, 2, 1);
		MAT_MUL_MAT(result, *this, other, 2, 2);
		MAT_MUL_MAT(result, *this, other, 2, 3);

		MAT_MUL_MAT(result, *this, other, 3, 0);
		MAT_MUL_MAT(result, *this, other, 3, 1);
		MAT_MUL_MAT(result, *this, other, 3, 2);
		MAT_MUL_MAT(result, *this, other, 3, 3);

		return result;
	}

	Vector operator*(float scalar, Vector& vec)
	{
		return vec * scalar;
	}

	Vector VectorZero()
	{
		return Vector{ 0.0f, 0.0f, 0.0f, 0.0f };
	}

	bool Vector3Equal(const Vector& v1, const Vector& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	bool Vector3IsInfinite(const Vector& v)
	{
		return isinf(v.x) || isinf(v.y) || isinf(v.z);
	}

	float Vector3Length(const Vector& v)
	{
		return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
	}

	float Vector3Dot(const Vector& v1, const Vector& v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
	}

	Vector Vector3Cross(const Vector& v1, const Vector& v2)
	{
		return Vector
		{
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0],
			0.0f
		};
	}

	Vector Vector3Normalize(Vector v)
	{
		if (Vector3Equal(v, VectorZero()) == true)
			assert(0);

		float length = Vector3Length(v);
		
		v.x /= length;
		v.y /= length;
		v.z /= length;

		return v;
	}

	Vector VectorReciprocal(const Vector& v)
	{
		Vector temp = {};

		if (v.x != 0.0f)
			temp.x = 1.0f / v.x;

		if (v.y != 0.0f)
			temp.y = 1.0f / v.y;

		if (v.z != 0.0f)
			temp.z = 1.0f / v.z;

		if (v.w != 0.0f)
			temp.w = 1.0f / v.w;

		return temp;
	}

	Vector VectorReplicate(float value)
	{
		return Vector
		{
			value,
			value,
			value,
			value
		};
	}

	Vector QuaternionMultiply(const Vector& q1, const Vector& q2)
	{
		// 영원한 마소의 XMQuaternionMultiply 코드
		return Vector
		{
			(q2.w * q1.x) + (q2.x * q1.w) + (q2.y * q1.z) - (q2.z * q1.y),
			(q2.w * q1.y) - (q2.x * q1.z) + (q2.y * q1.w) + (q2.z * q1.x),
			(q2.w * q1.z) + (q2.x * q1.y) - (q2.y * q1.x) + (q2.z * q1.w),
			(q2.w * q1.w) - (q2.x * q1.x) - (q2.y * q1.y) - (q2.z * q1.z)
		};
	}

	Matrix MatrixIdentity()
	{
		return Matrix
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	Matrix MatrixInverse(Matrix matrix)
	{
		// https://nnuu.tistory.com/136
		// 왜 되는지 모르겠지만 됨
		Matrix inverseMatrix = MatrixIdentity();

		for (int i = 0; i < 4; i++)
		{
			float t = matrix[i][i];

			for (int j = 0; j < 4; j++)
			{
				if (j >= i)
					matrix[i][j] /= t;

				inverseMatrix[i][j] /= t;
			}

			for (int j = 0; j < 4; j++)
			{
				if (i != j)
				{
					t = matrix[j][i];

					for (int k = 0; k < 4; k++)
					{
						matrix[j][k] -= t * matrix[i][k];
						inverseMatrix[j][k] -= t * inverseMatrix[i][k];
					}
				}
			}
		}

		return inverseMatrix;
	}

	Matrix MatrixTranspose(const Matrix& matrix)
	{
		return Matrix
		{
			matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
			matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
			matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
			matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]
		};
	}

	Matrix PerspectiveMatrix(float fovY, float aspectRatio, float nearZ, float farZ)
	{
		// 마소 XMMatrixPerspectiveFovLH 함수 참조
		float fSin;
		float fCos;

		ConvertRadianToScalarSinCos(fSin, fCos, fovY * 0.5f);

		float height = fCos / fSin;
		float width = height / aspectRatio;
		float fRange = farZ / (farZ - nearZ);

		return Matrix
		{
			width,	0.0f,	0.0f,	0.0f,
			0.0f,	height,	0.0f,	0.0f,
			0.0f,	0.0f,	fRange,	1.0f,
			0.0f,	0.0f,	-fRange * nearZ, 0.0f
		};
	}

	Matrix ViewMatrix(Vector position, Vector rotation)
	{
		Vector radian =
		{
			ConvertDegreeToRadian(rotation.x),
			ConvertDegreeToRadian(rotation.y),
			ConvertDegreeToRadian(rotation.z)
		};

		Matrix temp = MatrixRotationFromVector(radian);

		Vector right = temp[0];
		Vector up = temp[1];
		Vector look = temp[2];

		float dotX = Vector3Dot(position, right);
		float dotY = Vector3Dot(position, up);
		float dotZ = Vector3Dot(position, look);

		return Matrix
		{
			right[0], up[0], look[0], 0.0f,
			right[1], up[1], look[1], 0.0f,
			right[2], up[2], look[2], 0.0f,
			-dotX, -dotY, -dotZ, 1.0f
		};
	}

	Matrix MatrixScalingFromVector(Vector scale)
	{
		return Matrix
		{
			scale[0], 0, 0, 0,
			0, scale[1], 0, 0,
			0, 0, scale[2], 0,
			0, 0, 0, 1
		};
	}

	Matrix MatrixRotationFromVector(Vector rotation)
	{
		Matrix xAxis =
		{
			1, 0, 0, 0,
			0, +cosf(rotation.x), +sinf(rotation.x), 0,
			0, -sinf(rotation.x), +cosf(rotation.x), 0,
			0, 0, 0, 1
		};

		Matrix yAxis =
		{
			+cosf(rotation.y), 0, -sinf(rotation.y), 0,
			0, 1, 0, 0,
			+sinf(rotation.y), 0, +cosf(rotation.y), 0,
			0, 0, 0, 1
		};

		Matrix zAxis =
		{
			+cosf(rotation.z), +sinf(rotation.z), 0, 0,
			-sinf(rotation.z), +cosf(rotation.z), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		return xAxis * yAxis * zAxis;
	}

	Matrix MatrixTranslationFromVector(Vector translation)
	{
		return Matrix
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			translation.x, translation.y, translation.z, 1.0f
		};
	}

	Vector ConvertRotationNormalToQuaternion(const Vector& normalAxis, float angle)
	{
		// 마소 XMQuaternionRotationNormal 코드
		float fSin = 0.0f;
		float fCos = 0.0f;

		ConvertRadianToScalarSinCos(fSin, fCos, angle);

		Vector normal = normalAxis;
		normal[3] = 1.0f;
		Vector scale = { fSin, fSin, fSin, fCos };

		return normal * scale;
	}

	Vector ConvertRotationAxisAngleToQuaternion(const Vector& axis, float angle)
	{
		// 마소 XMQuaternionRotationAxis 코드
		assert(!Vector3Equal(axis, VectorZero()));
		assert(!Vector3IsInfinite(axis));

		Vector normalAxis = Vector3Normalize(axis);
		Vector quaternion = ConvertRotationNormalToQuaternion(normalAxis, angle);

		return quaternion;
	}

	Vector ConvertRotationMatrixToQuaternion(const Matrix& matrix)
	{
		// 마소의 XMQuaternionRotationMatrix 함수 코드 긁어옴
		Vector quaternion;

		float r22 = matrix[2][2];

		if (r22 <= 0.f)  // x^2 + y^2 >= z^2 + w^2
		{
			float dif10 = matrix[1][1] - matrix[0][0];
			float omr22 = 1.f - r22;
			if (dif10 <= 0.f)  // x^2 >= y^2
			{
				float fourXSqr = omr22 - dif10;
				float inv4x = 0.5f / sqrtf(fourXSqr);
				quaternion[0] = fourXSqr * inv4x;
				quaternion[1] = (matrix[0][1] + matrix[1][0]) * inv4x;
				quaternion[2] = (matrix[0][2] + matrix[2][0]) * inv4x;
				quaternion[3] = (matrix[1][2] - matrix[2][1]) * inv4x;
			}
			else  // y^2 >= x^2
			{
				float fourYSqr = omr22 + dif10;
				float inv4y = 0.5f / sqrtf(fourYSqr);
				quaternion[0] = (matrix[0][1] + matrix[1][0]) * inv4y;
				quaternion[1] = fourYSqr * inv4y;
				quaternion[2] = (matrix[1][2] + matrix[2][1]) * inv4y;
				quaternion[3] = (matrix[2][0] - matrix[0][2]) * inv4y;
			}
		}
		else  // z^2 + w^2 >= x^2 + y^2
		{
			float sum10 = matrix[1][1] + matrix[0][0];
			float opr22 = 1.f + r22;
			if (sum10 <= 0.f)  // z^2 >= w^2
			{
				float fourZSqr = opr22 - sum10;
				float inv4z = 0.5f / sqrtf(fourZSqr);
				quaternion[0] = (matrix[0][2] + matrix[2][0]) * inv4z;
				quaternion[1] = (matrix[1][2] + matrix[2][1]) * inv4z;
				quaternion[2] = fourZSqr * inv4z;
				quaternion[3] = (matrix[0][1] - matrix[1][0]) * inv4z;
			}
			else  // w^2 >= z^2
			{
				float fourWSqr = opr22 + sum10;
				float inv4w = 0.5f / sqrtf(fourWSqr);
				quaternion[0] = (matrix[1][2] - matrix[2][1]) * inv4w;
				quaternion[1] = (matrix[2][0] - matrix[0][2]) * inv4w;
				quaternion[2] = (matrix[0][1] - matrix[1][0]) * inv4w;
				quaternion[3] = fourWSqr * inv4w;
			}
		}

		return quaternion;
	}

	Vector ConvertQuaternionToEuler(const Vector& quaternion)
	{
		// X
		float t0 = 2.0f * (quaternion[0] * quaternion[3] - quaternion[1] * quaternion[2]);

		if (t0 > 1.0f)
			t0 = 1.0f;
		else if (t0 < -1.0f)
			t0 = -1.0f;

		// Y
		float t1 = 2.0f * (quaternion[0] * quaternion[2] + quaternion[1] * quaternion[3]);
		float t2 = 1.0f - 2.0f * (quaternion[0] * quaternion[0] + quaternion[1] * quaternion[1]);

		// Z
		float t3 = 2.0f * (quaternion[0] * quaternion[1] + quaternion[2] * quaternion[3]);
		float t4 = 1.0f - 2.0f * (quaternion[0] * quaternion[0] + quaternion[2] * quaternion[2]);

		return Vector
		{
			ConvertRadianToDegree(asinf(t0)),
			ConvertRadianToDegree(atan2f(t1, t2)),
			ConvertRadianToDegree(atan2f(t3, t4)),
			0.0f
		};
	}

	Vector ConvertRotationMatrixToEuler(const Matrix& matrix)
	{
		return ConvertQuaternionToEuler(ConvertRotationMatrixToQuaternion(matrix));
	}

	float ConvertDegreeToRadian(float degree)
	{
		return degree * (PI / 180.0f);
	}

	float ConvertRadianToDegree(float radian)
	{
		return radian * (180.0f / PI);
	}

	void ConvertRadianToScalarSinCos(float& fSin, float& fCos, float radian)
	{
		// 마소 코드 XMScalarSinCos 참조
		radian *= 0.5f;

		// y를 -PI ~ PI 사이값으로, x는 2 * PI * 몫 + 나머지?
		float quotient = 1.0f / (PI * 2) * radian;
		
		if (radian >= 0.0f)
			quotient += 0.5f;
		else
			quotient -= 0.5f;

		quotient = static_cast<float>(static_cast<int>(quotient));

		float y = radian - PI * 2 * quotient;

		// y를 -PI / 2 ~ PI / 2 사이값으로
		float sign = 1.0f;

		if (y > PI / 2.0f)
		{
			y = PI - y;
			sign = -1.0f;
		}
		else if (y < -PI / 2.0f)
		{
			y = -PI - y;
			sign = -1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		fSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
		
		// 11-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		fCos = sign * p;
	}

	float ComputeGaussian(float n, float theta)
	{
		return (1.0f / sqrtf(2 * PI * theta)) * expf(-(n * n) / (2 * theta * theta));
	}
}