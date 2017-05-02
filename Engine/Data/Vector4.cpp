#include "Vector3.h"
#include "Vector4.h"

namespace Engine
{
	const Vector4& Vector4::One = Vector4(1, 1, 1, 1);
	const Vector4& Vector4::Zero = Vector4(0, 0, 0, 0);

	Vector4::Vector4()
		: X(0.0f)
		  , Y(0.0f)
		  , Z(0.0f)
		  , W(0.0f)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w)
		: X(x)
		  , Y(y)
		  , Z(z)
		  , W(w)
	{
	}

	Vector4::Vector4(int x, int y, int z, int w)
		: X(float(x))
		  , Y(float(y))
		  , Z(float(z))
		  , W(float(w))
	{
	}

	Vector4::Vector4(const Vector4& rhs)
		: X(rhs.X)
		  , Y(rhs.Y)
		  , Z(rhs.Z)
		  , W(rhs.W)
	{
	}

	Vector4::Vector4(const Vector3& rhs)
		: X(rhs.X)
		  , Y(rhs.Y)
		  , Z(rhs.Z)
		  , W(0.0f)
	{
	}

	Vector4 Vector4::operator+(const Vector4& rhs) const
	{
		return Vector4(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W);
	}

	Vector4 Vector4::operator*(const Vector4& rhs) const
	{
		return Vector4(X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W);
	}

	Vector4 Vector4::operator-(const Vector4& rhs) const
	{
		return Vector4(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W);
	}

	Vector4 Vector4::operator/(const Vector4& rhs) const
	{
		return Vector4(X / rhs.X, Y / rhs.Y, Z / rhs.Z, W / rhs.W);
	}

	void Vector4::operator=(const Vector4& rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
		W = rhs.W;
	}

	Vector4 Vector4::operator*(const float& rhs) const
	{
		return Vector4(X * rhs, Y * rhs, Z * rhs, W * rhs);
	}

	Vector4 Vector4::operator/(const float& rhs) const
	{
		return Vector4(X / rhs, Y / rhs, Z / rhs, W / rhs);
	}

	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		W += rhs.W;

		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& rhs)
	{
		X *= rhs.X;
		Y *= rhs.Y;
		Z *= rhs.Z;
		W *= rhs.W;

		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& rhs)
	{
		X /= rhs.X;
		Y /= rhs.Y;
		Z /= rhs.Z;
		W /= rhs.W;

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		W -= rhs.W;

		return *this;
	}

	Vector4& Vector4::operator*=(const float& rhs)
	{
		X *= rhs;
		Y *= rhs;
		Z *= rhs;
		W *= rhs;

		return *this;
	}

	Vector4& Vector4::operator/=(const float& rhs)
	{
		X /= rhs;
		Y /= rhs;
		Z /= rhs;
		W /= rhs;

		return *this;
	}
}
