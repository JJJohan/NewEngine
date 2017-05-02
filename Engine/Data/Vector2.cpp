#include "Vector2.h"

namespace Engine
{
	const Vector2& Vector2::One = Vector2(1, 1);
	const Vector2& Vector2::Zero = Vector2(0, 0);
	const Vector2& Vector2::Up = Vector2(0, 1);
	const Vector2& Vector2::Down = Vector2(0, -1);
	const Vector2& Vector2::Left = Vector2(-1, 0);
	const Vector2& Vector2::Right = Vector2(1, 0);

	Vector2::Vector2()
		: X(0.0f)
		  , Y(0.0f)
	{
	}

	Vector2::Vector2(float x, float y)
		: X(x)
		  , Y(y)
	{
	}

	Vector2::Vector2(int x, int y)
		: X(float(x))
		  , Y(float(y))
	{
	}

	Vector2::Vector2(const Vector2& rhs)
		: X(rhs.X)
		  , Y(rhs.Y)
	{
	}

	Vector2 Vector2::operator+(const Vector2& rhs) const
	{
		return Vector2(X + rhs.X, Y + rhs.Y);
	}

	Vector2 Vector2::operator*(const Vector2& rhs) const
	{
		return Vector2(X * rhs.X, Y * rhs.Y);
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return Vector2(X - rhs.X, Y - rhs.Y);
	}

	Vector2 Vector2::operator/(const Vector2& rhs) const
	{
		return Vector2(X / rhs.X, Y / rhs.Y);
	}

	void Vector2::operator=(const Vector2& rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
	}

	Vector2 Vector2::operator*(const float& rhs) const
	{
		return Vector2(X * rhs, Y * rhs);
	}

	Vector2 Vector2::operator/(const float& rhs) const
	{
		return Vector2(X / rhs, Y / rhs);
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;

		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& rhs)
	{
		X *= rhs.X;
		Y *= rhs.Y;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& rhs)
	{
		X /= rhs.X;
		Y /= rhs.Y;

		return *this;
	}

	Vector2& Vector2::operator*=(const float& rhs)
	{
		X *= rhs;
		Y *= rhs;

		return *this;
	}

	Vector2& Vector2::operator/=(const float& rhs)
	{
		X /= rhs;
		Y /= rhs;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;

		return *this;
	}
}
