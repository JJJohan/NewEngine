#include "Vector2.h"
#include "Vector3.h"

namespace Engine
{
	const Vector3& Vector3::One = Vector3(1, 1, 1);
	const Vector3& Vector3::Zero = Vector3(0, 0, 0);
	const Vector3& Vector3::Up = Vector3(0, 1, 0);
	const Vector3& Vector3::Forward = Vector3(0, 0, 1);
	const Vector3& Vector3::Right = Vector3(1, 0, 0);

	Vector3::Vector3()
		: X(0.0f)
		  , Y(0.0f)
		  , Z(0.0f)
	{
	}

	Vector3::Vector3(float x, float y, float z)
		: X(x)
		  , Y(y)
		  , Z(z)
	{
	}

	Vector3::Vector3(int x, int y, int z)
		: X(float(x))
		  , Y(float(y))
		  , Z(float(z))
	{
	}

	Vector3::Vector3(const Vector3& rhs)
		: X(rhs.X)
		  , Y(rhs.Y)
		  , Z(rhs.Z)
	{
	}

	Vector3::Vector3(const Vector2& rhs)
		: X(rhs.X)
		  , Y(rhs.Y)
		  , Z(0.0f)
	{
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
	}

	Vector3 Vector3::operator*(const Vector3& rhs) const
	{
		return Vector3(X * rhs.X, Y * rhs.Y, Z * rhs.Z);
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
	}

	Vector3 Vector3::operator/(const Vector3& rhs) const
	{
		return Vector3(X / rhs.X, Y / rhs.Y, Z / rhs.Z);
	}

	void Vector3::operator=(const Vector3& rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
	}

	Vector3 Vector3::operator*(const float& rhs) const
	{
		return Vector3(X * rhs, Y * rhs, Z * rhs);
	}

	Vector3 Vector3::operator/(const float& rhs) const
	{
		return Vector3(X / rhs, Y / rhs, Z / rhs);
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;

		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& rhs)
	{
		X *= rhs.X;
		Y *= rhs.Y;
		Z *= rhs.Z;

		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& rhs)
	{
		X /= rhs.X;
		Y /= rhs.Y;
		Z /= rhs.Z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;

		return *this;
	}

	Vector3& Vector3::operator*=(const float& rhs)
	{
		X *= rhs;
		Y *= rhs;
		Z *= rhs;

		return *this;
	}

	Vector3& Vector3::operator/=(const float& rhs)
	{
		X /= rhs;
		Y /= rhs;
		Z /= rhs;

		return *this;
	}
}
