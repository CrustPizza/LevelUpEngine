/********************************
*								*
*	HeraclesMath.cpp			*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/02		*
*********************************/

#include "HeraclesMath.h"
#include <assert.h>

namespace HeraclesMath
{
	constexpr unsigned int SWIZZLE_X = 0;
	constexpr unsigned int SWIZZLE_Y = 1;
	constexpr unsigned int SWIZZLE_Z = 2;
	constexpr unsigned int SWIZZLE_W = 3;

	constexpr unsigned int PERMUTE_X0 = 0;
	constexpr unsigned int PERMUTE_Y0 = 1;
	constexpr unsigned int PERMUTE_Z0 = 2;
	constexpr unsigned int PERMUTE_W0 = 3;
	constexpr unsigned int PERMUTE_X1 = 4;
	constexpr unsigned int PERMUTE_Y1 = 5;
	constexpr unsigned int PERMUTE_Z1 = 6;
	constexpr unsigned int PERMUTE_W1 = 7;

	constexpr unsigned int SELECT_0 = 0x00000000u;
	constexpr unsigned int SELECT_1 = 0xffffffffu;

	Matrix Matrix::Identity = MatrixIdentity();

	const Vector Vector::Zero = VectorZero();
	const Vector Vector::UnitX = { 1.0f, 0.0f, 0.0f, 0.0f };
	const Vector Vector::UnitY = { 0.0f, 1.0f, 0.0f, 0.0f };
	const Vector Vector::UnitZ = { 0.0f, 0.0f, 1.0f, 0.0f };
	const Vector Vector::UnitW = { 0.0f, 0.0f, 0.0f, 1.0f };
	const Vector Vector::One = { 1.0f, 1.0f, 1.0f, 1.0f };
	const Vector Vector::NegativeOne = { -1.0f, -1.0f, -1.0f, -1.0f };
	const Vector Vector::SignMask = { 0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u };

	const Vector Vector::Left = { -1.0f, 0.0f, 0.0f, 0.0f };
	const Vector Vector::Right = { 1.0f, 0.0f, 0.0f, 0.0f };
	const Vector Vector::Up = { 0.0f, 1.0f, 0.0f, 0.0f };
	const Vector Vector::Down = { 0.0f, -1.0f, 0.0f, 0.0f };
	const Vector Vector::Forward = { 0.0f, 0.0f, 1.0f, 0.0f };
	const Vector Vector::Backward = { 0.0f, 0.0f, -1.0f, 0.0f };

	const Vector Vector::Select0101 = { SELECT_0, SELECT_1, SELECT_0, SELECT_1 };
	const Vector Vector::Select1010 = { SELECT_1, SELECT_0, SELECT_1, SELECT_0 };
	const Vector Vector::Select1000 = { SELECT_1, SELECT_0, SELECT_0, SELECT_0 };
	const Vector Vector::Select1100 = { SELECT_1, SELECT_1, SELECT_0, SELECT_0 };
	const Vector Vector::Select1110 = { SELECT_1, SELECT_1, SELECT_1, SELECT_0 };
	const Vector Vector::Select1011 = { SELECT_1, SELECT_0, SELECT_1, SELECT_1 };

	Vector::Vector(const float x, const float y, const float z, const float w)
		: v{ x, y, z, w }
	{
	}

	Vector::Vector(const int i1, const int i2, const int i3, const int i4)
		: i{ i1, i2, i3, i4 }
	{
	}

	Vector::Vector(const unsigned int u1, const unsigned int u2, const unsigned int u3, const unsigned int u4)
		: u{ u1, u2, u3, u4 }
	{
	}

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

	Vector& Vector::operator*=(const Vector& other)
	{
		*this = *this * other;

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

	Vector Vector::operator-()
	{
		return Vector
		{
			-this->x,
			-this->y,
			-this->z,
			-this->w
		};
	}

	Vector Vector::operator-() const
	{
		return Vector
		{
			-this->x,
			-this->y,
			-this->z,
			-this->w
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
			this->x * other.m[0][0] + this->y * other.m[1][0] + this->z * other.m[2][0] + this->w * other.m[3][0],
			this->x * other.m[0][1] + this->y * other.m[1][1] + this->z * other.m[2][1] + this->w * other.m[3][1],
			this->x * other.m[0][2] + this->y * other.m[1][2] + this->z * other.m[2][2] + this->w * other.m[3][2],
			this->x * other.m[0][3] + this->y * other.m[1][3] + this->z * other.m[2][3] + this->w * other.m[3][3]
		};
	}

	Vector Vector::operator*(const Matrix& other) const
	{
		return Vector
		{
			this->x * other.m[0][0] + this->y * other.m[1][0] + this->z * other.m[2][0] + this->w * other.m[3][0],
			this->x * other.m[0][1] + this->y * other.m[1][1] + this->z * other.m[2][1] + this->w * other.m[3][1],
			this->x * other.m[0][2] + this->y * other.m[1][2] + this->z * other.m[2][2] + this->w * other.m[3][2],
			this->x * other.m[0][3] + this->y * other.m[1][3] + this->z * other.m[2][3] + this->w * other.m[3][3]
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

	bool Vector::operator==(const Vector& v)
	{
		return Vector4Equal(*this, v);
	}

	Matrix::Matrix(const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4)
		: r{ v1, v2, v3, v4 }
	{

	}

	Matrix::Matrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
		: m{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 }
	{
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

		result[0][0] = this->m[0][0] * other[0][0] + this->m[0][1] * other[1][0] + this->m[0][2] * other[2][0] + this->m[0][3] * other[3][0];
		result[0][1] = this->m[0][0] * other[0][1] + this->m[0][1] * other[1][1] + this->m[0][2] * other[2][1] + this->m[0][3] * other[3][1];
		result[0][2] = this->m[0][0] * other[0][2] + this->m[0][1] * other[1][2] + this->m[0][2] * other[2][2] + this->m[0][3] * other[3][2];
		result[0][3] = this->m[0][0] * other[0][3] + this->m[0][1] * other[1][3] + this->m[0][2] * other[2][3] + this->m[0][3] * other[3][3];

		result[1][0] = this->m[1][0] * other[0][0] + this->m[1][1] * other[1][0] + this->m[1][2] * other[2][0] + this->m[1][3] * other[3][0];
		result[1][1] = this->m[1][0] * other[0][1] + this->m[1][1] * other[1][1] + this->m[1][2] * other[2][1] + this->m[1][3] * other[3][1];
		result[1][2] = this->m[1][0] * other[0][2] + this->m[1][1] * other[1][2] + this->m[1][2] * other[2][2] + this->m[1][3] * other[3][2];
		result[1][3] = this->m[1][0] * other[0][3] + this->m[1][1] * other[1][3] + this->m[1][2] * other[2][3] + this->m[1][3] * other[3][3];

		result[2][0] = this->m[2][0] * other[0][0] + this->m[2][1] * other[1][0] + this->m[2][2] * other[2][0] + this->m[2][3] * other[3][0];
		result[2][1] = this->m[2][0] * other[0][1] + this->m[2][1] * other[1][1] + this->m[2][2] * other[2][1] + this->m[2][3] * other[3][1];
		result[2][2] = this->m[2][0] * other[0][2] + this->m[2][1] * other[1][2] + this->m[2][2] * other[2][2] + this->m[2][3] * other[3][2];
		result[2][3] = this->m[2][0] * other[0][3] + this->m[2][1] * other[1][3] + this->m[2][2] * other[2][3] + this->m[2][3] * other[3][3];

		result[3][0] = this->m[3][0] * other[0][0] + this->m[3][1] * other[1][0] + this->m[3][2] * other[2][0] + this->m[3][3] * other[3][0];
		result[3][1] = this->m[3][0] * other[0][1] + this->m[3][1] * other[1][1] + this->m[3][2] * other[2][1] + this->m[3][3] * other[3][1];
		result[3][2] = this->m[3][0] * other[0][2] + this->m[3][1] * other[1][2] + this->m[3][2] * other[2][2] + this->m[3][3] * other[3][2];
		result[3][3] = this->m[3][0] * other[0][3] + this->m[3][1] * other[1][3] + this->m[3][2] * other[2][3] + this->m[3][3] * other[3][3];

		return result;
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{
		Matrix result;

		result[0][0] = this->m[0][0] * other[0][0] + this->m[0][1] * other[1][0] + this->m[0][2] * other[2][0] + this->m[0][3] * other[3][0];
		result[0][1] = this->m[0][0] * other[0][1] + this->m[0][1] * other[1][1] + this->m[0][2] * other[2][1] + this->m[0][3] * other[3][1];
		result[0][2] = this->m[0][0] * other[0][2] + this->m[0][1] * other[1][2] + this->m[0][2] * other[2][2] + this->m[0][3] * other[3][2];
		result[0][3] = this->m[0][0] * other[0][3] + this->m[0][1] * other[1][3] + this->m[0][2] * other[2][3] + this->m[0][3] * other[3][3];

		result[1][0] = this->m[1][0] * other[0][0] + this->m[1][1] * other[1][0] + this->m[1][2] * other[2][0] + this->m[1][3] * other[3][0];
		result[1][1] = this->m[1][0] * other[0][1] + this->m[1][1] * other[1][1] + this->m[1][2] * other[2][1] + this->m[1][3] * other[3][1];
		result[1][2] = this->m[1][0] * other[0][2] + this->m[1][1] * other[1][2] + this->m[1][2] * other[2][2] + this->m[1][3] * other[3][2];
		result[1][3] = this->m[1][0] * other[0][3] + this->m[1][1] * other[1][3] + this->m[1][2] * other[2][3] + this->m[1][3] * other[3][3];

		result[2][0] = this->m[2][0] * other[0][0] + this->m[2][1] * other[1][0] + this->m[2][2] * other[2][0] + this->m[2][3] * other[3][0];
		result[2][1] = this->m[2][0] * other[0][1] + this->m[2][1] * other[1][1] + this->m[2][2] * other[2][1] + this->m[2][3] * other[3][1];
		result[2][2] = this->m[2][0] * other[0][2] + this->m[2][1] * other[1][2] + this->m[2][2] * other[2][2] + this->m[2][3] * other[3][2];
		result[2][3] = this->m[2][0] * other[0][3] + this->m[2][1] * other[1][3] + this->m[2][2] * other[2][3] + this->m[2][3] * other[3][3];

		result[3][0] = this->m[3][0] * other[0][0] + this->m[3][1] * other[1][0] + this->m[3][2] * other[2][0] + this->m[3][3] * other[3][0];
		result[3][1] = this->m[3][0] * other[0][1] + this->m[3][1] * other[1][1] + this->m[3][2] * other[2][1] + this->m[3][3] * other[3][1];
		result[3][2] = this->m[3][0] * other[0][2] + this->m[3][1] * other[1][2] + this->m[3][2] * other[2][2] + this->m[3][3] * other[3][2];
		result[3][3] = this->m[3][0] * other[0][3] + this->m[3][1] * other[1][3] + this->m[3][2] * other[2][3] + this->m[3][3] * other[3][3];

		return result;
	}

	Vector Matrix::operator*(const Vector& v)
	{
		return Vector
		{
			this->m[0][0] * v[0] + this->m[0][1] * v[1] + this->m[0][2] * v[2] + this->m[0][3] * v[3],
			this->m[1][0] * v[0] + this->m[1][1] * v[1] + this->m[1][2] * v[2] + this->m[1][3] * v[3],
			this->m[2][0] * v[0] + this->m[2][1] * v[1] + this->m[2][2] * v[2] + this->m[2][3] * v[3],
			this->m[3][0] * v[0] + this->m[3][1] * v[1] + this->m[3][2] * v[2] + this->m[3][3] * v[3]
		};
	}

	Vector Matrix::operator*(const Vector& v) const
	{
		return Vector
		{
			this->m[0][0] * v[0] + this->m[0][1] * v[1] + this->m[0][2] * v[2] + this->m[0][3] * v[3],
			this->m[1][0] * v[0] + this->m[1][1] * v[1] + this->m[1][2] * v[2] + this->m[1][3] * v[3],
			this->m[2][0] * v[0] + this->m[2][1] * v[1] + this->m[2][2] * v[2] + this->m[2][3] * v[3],
			this->m[3][0] * v[0] + this->m[3][1] * v[1] + this->m[3][2] * v[2] + this->m[3][3] * v[3]
		};
	}

	bool Matrix::operator==(const Matrix& m)
	{
		return MatrixEqaul(*this, m);
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

	bool Vector4Equal(const Vector& v1, const Vector& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
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
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	float Vector4Dot(const Vector& v1, const Vector& v2)
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

	Vector Vector3Transform(const Vector& v, const Matrix& m)
	{
		return v * m;
	}

	Vector VectorReciprocal(const Vector& v)
	{
		return Vector
		{
			1.0f / v.x,
			1.0f / v.y,
			1.0f / v.z,
			1.0f / v.w
		};
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

	Vector VectorLess(const Vector& v1, const Vector& v2)
	{
		return Vector
		{
			v1.x < v2.x ? 0xffffffff : 0,
			v1.y < v2.y ? 0xffffffff : 0,
			v1.z < v2.z ? 0xffffffff : 0,
			v1.w < v2.w ? 0xffffffff : 0
		};
	}

	Vector VectorSelect(const Vector& v1, const Vector& v2, const Vector& control)
	{
		// 마소 XMVectorSelect 구현 참고
		return Vector
		{
			(v1.u[0] & ~control.u[0]) | (v2.u[0] & control.u[0]),
			(v1.u[1] & ~control.u[1]) | (v2.u[1] & control.u[1]),
			(v1.u[2] & ~control.u[2]) | (v2.u[2] & control.u[2]),
			(v1.u[3] & ~control.u[3]) | (v2.u[3] & control.u[3])
		};
	}

	Vector VectorXorInt(const Vector& v1, const Vector& v2)
	{
		return Vector
		{
			v1.u[0] ^ v2.u[0],
			v1.u[1] ^ v2.u[1],
			v1.u[2] ^ v2.u[2],
			v1.u[3] ^ v2.u[3]
		};
	}

	Vector VectorLerp(const Vector& v1, const Vector& v2, float tick)
	{
		Vector length = v2 - v1;

		return v1 + length * VectorReplicate(tick);
	}

	Vector VectorSplatX(const Vector& v)
	{
		return VectorReplicate(v.x);
	}

	Vector VectorSplatY(const Vector& v)
	{
		return VectorReplicate(v.y);
	}

	Vector VectorSplatZ(const Vector& v)
	{
		return VectorReplicate(v.z);
	}

	Vector VectorSplatW(const Vector& v)
	{
		return VectorReplicate(v.w);
	}

	Vector VectorSqrt(const Vector& v)
	{
		return Vector
		{
			sqrtf(v[0]),
			sqrtf(v[1]),
			sqrtf(v[2]),
			sqrtf(v[3])
		};
	}

	Vector VectorSin(const Vector& v)
	{
		return Vector
		{
			sinf(v.x),
			sinf(v.y),
			sinf(v.z),
			sinf(v.w)
		};
	}

	Vector VectorCos(const Vector& v)
	{
		return Vector
		{
			cosf(v.x),
			cosf(v.y),
			cosf(v.z),
			cosf(v.w)
		};
	}

	Vector VectorAtan2(const Vector& y, const Vector& x)
	{
		return Vector
		{
			atan2f(y[0], x[0]),
			atan2f(y[1], x[1]),
			atan2f(y[2], x[2]),
			atan2f(y[3], x[3])
		};
	}

	Matrix QuaternionToRotationMatrix(const Vector& quaternion)
	{
		// 마소 XMMatrixRotationQuaternion 함수 코드
		Vector mask1110 = { 1.0f, 1.0f, 1.0f, 0.0f };

		Vector q0 = quaternion + quaternion;
		Vector q1 = quaternion * q0;

		Vector v0 = VectorPermute<PERMUTE_Y0, PERMUTE_X0, PERMUTE_X0, PERMUTE_W1>(q1, mask1110);
		Vector v1 = VectorPermute<PERMUTE_Z0, PERMUTE_Z0, PERMUTE_Y0, PERMUTE_W1>(q1, mask1110);

		Vector r0 = mask1110 - v0 - v1;

		v0 = VectorSwizzle<SWIZZLE_X, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_W>(quaternion);
		v1 = VectorSwizzle<SWIZZLE_Z, SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_W>(q0);
		v0 = v0 * v1;

		v1 = VectorReplicate(quaternion.w);
		Vector v2 = VectorSwizzle<SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_X, SWIZZLE_W>(q0);
		v1 = v1 * v2;

		Vector r1 = v0 + v1;
		Vector r2 = v0 - v1;

		v0 = VectorPermute<PERMUTE_Y0, PERMUTE_X1, PERMUTE_Y1, PERMUTE_Z0>(r1, r2);
		v1 = VectorPermute<PERMUTE_X0, PERMUTE_Z1, PERMUTE_X0, PERMUTE_Z1>(r1, r2);

		Matrix rotationMatrix;

		rotationMatrix.r[0] = VectorPermute<PERMUTE_X0, PERMUTE_X1, PERMUTE_Y1, PERMUTE_W0>(r0, v0);
		rotationMatrix.r[1] = VectorPermute<PERMUTE_Z1, PERMUTE_Y0, PERMUTE_W1, PERMUTE_W0>(r0, v0);
		rotationMatrix.r[2] = VectorPermute<PERMUTE_X1, PERMUTE_Y1, PERMUTE_Z0, PERMUTE_W0>(r0, v1);
		rotationMatrix.r[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

		return rotationMatrix;
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

	Vector QuaternionSlerp(const Vector& q1, const Vector& q2, float tick)
	{
		// 마소 XMQuaternionSlerpV 코드
		Vector oneEpsillon = { 1.0f - 0.00001f, 1.0f - 0.00001f, 1.0f - 0.00001f, 1.0f - 0.00001f };

		Vector cosOmega = VectorReplicate(Vector4Dot(q1, q2));
		Vector control = VectorLess(cosOmega, Vector::Zero);
		Vector sign = VectorSelect(Vector::One, Vector::NegativeOne, control);

		cosOmega = cosOmega * sign;

		control = VectorLess(cosOmega, oneEpsillon);

		Vector sinOmega = Vector::One - cosOmega * cosOmega;
		sinOmega = VectorSqrt(sinOmega);

		Vector omega = VectorAtan2(sinOmega, cosOmega);

		Vector signMask;
		signMask.u[0] = 0x80000000u;
		signMask.u[1] = 0x80000000u;
		signMask.u[2] = 0x80000000u;
		signMask.u[3] = 0x80000000u;

		Vector v01 = VectorShiftLeft<2>(VectorReplicate(tick), Vector::Zero);
		signMask = VectorShiftLeft<3>(signMask, Vector::Zero);
		v01 = VectorXorInt(v01, signMask);
		v01 = Vector::UnitX + v01;

		Vector invSinOmega = VectorReciprocal(sinOmega);

		Vector s0 = v01 * omega;
		s0 = VectorSin(s0);
		s0 = s0 * invSinOmega;
		s0 = VectorSelect(v01, s0, control);

		Vector s1 = VectorSplatY(s0);
		s0 = VectorSplatX(s0);
		s1 = s1 * sign;

		Vector result = q1 * s0;
		result += q2 * s1;

		return result;
	}

	Matrix MatrixIdentity()
	{
		return Matrix
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix MatrixInverse(Matrix matrix)
	{
		// 마소 XMMatrixInverse 함수

		Matrix mt = MatrixTranspose(matrix);

		Vector v0[4];
		Vector v1[4];

		v0[0] = VectorSwizzle<SWIZZLE_X, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Y>(mt.r[2]);
		v1[0] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W>(mt.r[3]);
		v0[1] = VectorSwizzle<SWIZZLE_X, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Y>(mt.r[0]);
		v1[1] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W>(mt.r[1]);
		v0[2] = VectorPermute<PERMUTE_X0, PERMUTE_Z0, PERMUTE_X1, PERMUTE_Z1>(mt.r[2], mt.r[0]);
		v1[2] = VectorPermute<PERMUTE_Y0, PERMUTE_W0, PERMUTE_Y1, PERMUTE_W1>(mt.r[3], mt.r[1]);

		Vector d0 = v0[0] * v1[0];
		Vector d1 = v0[1] * v1[1];
		Vector d2 = v0[2] * v1[2];

		v0[0] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W>(mt.r[2]);
		v1[0] = VectorSwizzle<SWIZZLE_X, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Y>(mt.r[3]);
		v0[1] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W>(mt.r[0]);
		v1[1] = VectorSwizzle<SWIZZLE_X, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_Y>(mt.r[1]);
		v0[2] = VectorPermute<PERMUTE_Y0, PERMUTE_W0, PERMUTE_Y1, PERMUTE_W1>(mt.r[2], mt.r[0]);
		v1[2] = VectorPermute<PERMUTE_X0, PERMUTE_Z0, PERMUTE_X1, PERMUTE_Z1>(mt.r[3], mt.r[1]);

		d0 -= v0[0] * v1[0];
		d1 -= v0[1] * v1[1];
		d2 -= v0[2] * v1[2];

		v0[0] = VectorSwizzle<SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_X, SWIZZLE_Y>(mt.r[1]);
		v1[0] = VectorPermute<PERMUTE_Y1, PERMUTE_Y0, PERMUTE_W0, PERMUTE_X0>(d0, d2);
		v0[1] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_X>(mt.r[0]);
		v1[1] = VectorPermute<PERMUTE_W0, PERMUTE_Y1, PERMUTE_Y0, PERMUTE_Z0>(d0, d2);
		v0[2] = VectorSwizzle<SWIZZLE_Y, SWIZZLE_Z, SWIZZLE_X, SWIZZLE_Y>(mt.r[3]);
		v1[2] = VectorPermute<PERMUTE_W1, PERMUTE_Y0, PERMUTE_W0, PERMUTE_X0>(d1, d2);
		v0[3] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_X, SWIZZLE_Y, SWIZZLE_X>(mt.r[2]);
		v1[3] = VectorPermute<PERMUTE_W0, PERMUTE_W1, PERMUTE_Y0, PERMUTE_Z0>(d1, d2);

		Vector c0 = v0[0] * v1[0];
		Vector c2 = v0[1] * v1[1];
		Vector c4 = v0[2] * v1[2];
		Vector c6 = v0[3] * v1[3];

		v0[0] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Y, SWIZZLE_Z>(mt.r[1]);
		v1[0] = VectorPermute<PERMUTE_W0, PERMUTE_X0, PERMUTE_Y0, PERMUTE_X1>(d0, d2);
		v0[1] = VectorSwizzle<SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Y>(mt.r[0]);
		v1[1] = VectorPermute<PERMUTE_Z0, PERMUTE_Y0, PERMUTE_X1, PERMUTE_X0>(d0, d2);
		v0[2] = VectorSwizzle<SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Y, SWIZZLE_Z>(mt.r[3]);
		v1[2] = VectorPermute<PERMUTE_W0, PERMUTE_X0, PERMUTE_Y0, PERMUTE_Z1>(d1, d2);
		v0[3] = VectorSwizzle<SWIZZLE_W, SWIZZLE_Z, SWIZZLE_W, SWIZZLE_Y>(mt.r[2]);
		v1[3] = VectorPermute<PERMUTE_Z0, PERMUTE_Y0, PERMUTE_Z1, PERMUTE_X0>(d1, d2);

		c0 -= v0[0] * v1[0];
		c2 -= v0[1] * v1[1];
		c4 -= v0[2] * v1[2];
		c6 -= v0[3] * v1[3];

		v0[0] = VectorSwizzle<SWIZZLE_W, SWIZZLE_X, SWIZZLE_W, SWIZZLE_X>(mt.r[1]);
		v1[0] = VectorPermute<PERMUTE_Z0, PERMUTE_Y1, PERMUTE_X1, PERMUTE_Z0>(d0, d2);
		v0[1] = VectorSwizzle<SWIZZLE_Y, SWIZZLE_W, SWIZZLE_X, SWIZZLE_Z>(mt.r[0]);
		v1[1] = VectorPermute<PERMUTE_Y1, PERMUTE_X0, PERMUTE_W0, PERMUTE_X1>(d0, d2);
		v0[2] = VectorSwizzle<SWIZZLE_W, SWIZZLE_X, SWIZZLE_W, SWIZZLE_X>(mt.r[3]);
		v1[2] = VectorPermute<PERMUTE_Z0, PERMUTE_W1, PERMUTE_Z1, PERMUTE_Z0>(d1, d2);
		v0[3] = VectorSwizzle<SWIZZLE_Y, SWIZZLE_W, SWIZZLE_X, SWIZZLE_Z>(mt.r[2]);
		v1[3] = VectorPermute<PERMUTE_W1, PERMUTE_X0, PERMUTE_W0, PERMUTE_Z1>(d1, d2);

		Vector c1 = c0 - v0[0] * v1[0];
		c0 += v0[0] * v1[0];
		Vector c3 = c2 + v0[1] * v1[1];
		c2 -= v0[1] * v1[1];
		Vector c5 = c4 - v0[2] * v1[2];
		c4 += v0[2] * v1[2];
		Vector c7 = c6 + v0[3] * v1[3];
		c6 -= v0[3] * v1[3];

		Matrix result;
		result.r[0] = VectorSelect(c0, c1, Vector::Select0101);
		result.r[1] = VectorSelect(c2, c3, Vector::Select0101);
		result.r[2] = VectorSelect(c4, c5, Vector::Select0101);
		result.r[3] = VectorSelect(c6, c7, Vector::Select0101);

		Vector determinant = VectorReplicate(Vector4Dot(result.r[0], mt.r[0]));

		Vector reciprocal = VectorReciprocal(determinant);

		result.r[0] *= reciprocal;
		result.r[1] *= reciprocal;
		result.r[2] *= reciprocal;
		result.r[3] *= reciprocal;

		return result;

		// 안되는 상황이 있어서 교체

		//// https://nnuu.tistory.com/136
		//// 왜 되는지 모르겠지만 됨
		//Matrix inverseMatrix = Matrix::Identity;

		//for (int i = 0; i < 4; i++)
		//{
		//	float t = matrix[i][i];

		//	for (int j = 0; j < 4; j++)
		//	{
		//		if (j >= i)
		//			matrix[i][j] /= t;

		//		inverseMatrix[i][j] /= t;
		//	}

		//	for (int j = 0; j < 4; j++)
		//	{
		//		if (i != j)
		//		{
		//			t = matrix[j][i];

		//			for (int k = 0; k < 4; k++)
		//			{
		//				matrix[j][k] -= t * matrix[i][k];
		//				inverseMatrix[j][k] -= t * inverseMatrix[i][k];
		//			}
		//		}
		//	}
		//}

		//return inverseMatrix;
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

	bool MatrixEqaul(const Matrix& m1, const Matrix& m2)
	{
		return Vector4Equal(m1[0], m2[0]) && Vector4Equal(m1[1], m2[1]) && Vector4Equal(m1[2], m2[2]) && Vector4Equal(m1[3], m2[3]);
	}

	Matrix MatrixLookAtLH(const Vector& eyePosition, const Vector& focusPosition, const Vector& upDirection)
	{
		Vector eyeDirection = focusPosition - eyePosition;

		return MatrixLookAt(eyePosition, eyeDirection, upDirection);
	}

	Matrix MatrixLookAtRH(const Vector& eyePosition, const Vector& focusPosition, const Vector& upDirection)
	{
		Vector eyeDirection = eyePosition - focusPosition;

		return MatrixLookAt(eyePosition, eyeDirection, upDirection);
	}

	Matrix MatrixLookAt(const Vector& eyePosition, const Vector& eyeDirection, const Vector& upDirection)
	{
		assert(Vector3Equal(eyeDirection, Vector::Zero) != true);
		assert(Vector3IsInfinite(eyeDirection) != true);
		assert(Vector3Equal(upDirection, Vector::Zero) != true);
		assert(Vector3IsInfinite(upDirection) != true);

		Vector look = Vector3Normalize(eyeDirection);
		
		Vector right = Vector3Cross(upDirection, look);
		right = Vector3Normalize(right);

		Vector up = Vector3Cross(look, right);

		right.w = -Vector3Dot(right, eyePosition);
		up.w = -Vector3Dot(up, eyePosition);
		look.w = -Vector3Dot(look, eyePosition);

		Matrix result =
		{
			right,
			up,
			look,
			Vector::UnitW
		};

		return MatrixTranspose(result);
	}

	Matrix OrthographicMatrix(float ViewWidth, float ViewHeight, float nearZ, float farZ)
	{
		// 마소 XMMatrixOrthographicLH 함수 참조
		float fRange = 1.0f / (farZ - nearZ);

		return Matrix
		{
			2.0f / ViewWidth, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / ViewHeight, 0.0f, 0.0f,
			0.0f, 0.0f, fRange, 0.0f,
			0.0f, 0.0f, -fRange * nearZ, 1.0f
		};
	}

	Matrix OrthographicOffCenterMatrix(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		float reciprocalWidth = 1.0f / (right - left);
		float reciprocalHeight = 1.0f / (top - bottom);
		float fRange = 1.0f / (farZ - nearZ);

		return Matrix
		{
			2.0f * reciprocalWidth, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f * reciprocalHeight, 0.0f, 0.0f,
			0.0f, 0.0f, fRange, 0.0f,
			-(left + right) * reciprocalWidth, -(top + bottom) * reciprocalHeight, -fRange * nearZ, 1.0f
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
		Matrix temp = MatrixRotationFromVector(rotation);

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
			scale[0], 0.0f, 0.0f, 0.0f,
			0.0f, scale[1], 0.0f, 0.0f,
			0.0f, 0.0f, scale[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix MatrixRotationFromVector(Vector rotation)
	{
		Vector quaternion = ConvertEulerToQuaternion(ConvertDegreeToRadian(rotation));

		return QuaternionToRotationMatrix(quaternion);
	}

	Matrix MatrixTranslationFromVector(Vector translation)
	{
		return Matrix
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
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
		assert(!Vector3Equal(axis, Vector::Zero));
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

		//Vector quaternion;
		//float trace = matrix[0][0] + matrix[1][1] + matrix[2][2];

		//if (trace > 0.0f)
		//{
		//	float s = 0.5f / sqrtf(trace + 1.0f);

		//	quaternion.x = (matrix[2][1] - matrix[1][2]) * s;
		//	quaternion.y = (matrix[0][2] - matrix[2][0]) * s;
		//	quaternion.z = (matrix[1][0] - matrix[0][1]) * s;
		//	quaternion.w = 0.25f / s;
		//}
		//else
		//{
		//	if (matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2])
		//	{
		//		float s = 2.0f * sqrtf(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]);

		//		quaternion.x = 0.25f * s;
		//		quaternion.y = (matrix[0][1] + matrix[1][0]) / s;
		//		quaternion.z = (matrix[0][2] + matrix[2][0]) / s;
		//		quaternion.w = (matrix[2][1] - matrix[1][2]) / s;
		//	}
		//	else if (matrix[1][1] > matrix[2][2])
		//	{
		//		float s = 2.0f * sqrtf(1.0f - matrix[0][0] + matrix[1][1] - matrix[2][2]);

		//		quaternion.x = (matrix[0][1] + matrix[1][0]) / s;
		//		quaternion.y = 0.25f * s;
		//		quaternion.z = (matrix[0][2] + matrix[2][0]) / s;
		//		quaternion.w = (matrix[2][1] - matrix[1][2]) / s;
		//	}
		//	else
		//	{
		//		float s = 2.0f * sqrtf(1.0f - matrix[0][0] - matrix[1][1] + matrix[2][2]);

		//		quaternion.x = (matrix[0][2] + matrix[2][0]) / s;
		//		quaternion.y = (matrix[1][2] + matrix[2][1]) / s;
		//		quaternion.z = 0.25f * s;
		//		quaternion.w = (matrix[1][0] - matrix[0][1]) / s;
		//	}
		//}

		//return quaternion;
	}

	Vector ConvertQuaternionToEuler(const Vector& quaternion)
	{
		// Y
		float t1 = 2.0f * (quaternion[0] * quaternion[2] + quaternion[1] * quaternion[3]);
		float t2 = 1.0f - 2.0f * (quaternion[0] * quaternion[0] + quaternion[1] * quaternion[1]);

		// X
		float t0 = 2.0f * (quaternion[0] * quaternion[3] - quaternion[1] * quaternion[2]);

		if (t0 > 1.0f)
			t0 = 1.0f;
		else if (t0 < -1.0f)
			t0 = -1.0f;

		// Z
		float t3 = 2.0f * (quaternion[2] * quaternion[3] + quaternion[0] * quaternion[1]);
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

	Vector ConvertEulerToQuaternion(const Vector& euler)
	{
		// 마소 XMQuaternionRotationRollPitchYawFromVector
		Vector sign = { 1.0f, -1.0f, -1.0f, 1.0f };

		Vector halfAngles = euler * VectorReplicate(0.5f);

		Vector sinAngles = VectorSin(halfAngles);
		Vector cosAngles = VectorCos(halfAngles);

		Vector p0 = VectorPermute<PERMUTE_X0, PERMUTE_X1, PERMUTE_X1, PERMUTE_X1>(sinAngles, cosAngles);
		Vector y0 = VectorPermute<PERMUTE_Y1, PERMUTE_Y0, PERMUTE_Y1, PERMUTE_Y1>(sinAngles, cosAngles);
		Vector r0 = VectorPermute<PERMUTE_Z1, PERMUTE_Z1, PERMUTE_Z0, PERMUTE_Z1>(sinAngles, cosAngles);
		Vector p1 = VectorPermute<PERMUTE_X0, PERMUTE_X1, PERMUTE_X1, PERMUTE_X1>(cosAngles, sinAngles);
		Vector y1 = VectorPermute<PERMUTE_Y1, PERMUTE_Y0, PERMUTE_Y1, PERMUTE_Y1>(cosAngles, sinAngles);
		Vector r1 = VectorPermute<PERMUTE_Z1, PERMUTE_Z1, PERMUTE_Z0, PERMUTE_Z1>(cosAngles, sinAngles);

		Vector quaternion = p0 * y0;
		Vector q1 = p1 * sign;
		quaternion *= r0;
		q1 *= y1;

		quaternion += q1 * r1;

		return quaternion;
	}

	Vector ConvertDegreeToRadian(const Vector& degree)
	{
		return Vector
		{
			ConvertDegreeToRadian(degree.x),
			ConvertDegreeToRadian(degree.y),
			ConvertDegreeToRadian(degree.z),
			0.0f
		};
	}

	Vector ConvertRadianToDegree(const Vector& radian)
	{
		return Vector
		{
			ConvertRadianToDegree(radian.x),
			ConvertRadianToDegree(radian.y),
			ConvertRadianToDegree(radian.z),
			0.0f
		};
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