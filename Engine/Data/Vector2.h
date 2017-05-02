#pragma once
#include "../Core/Common.h"

namespace Engine
{
	class Vector2
	{
	public:
		ENGINE_API Vector2();
		ENGINE_API Vector2(const Vector2& rhs);
		ENGINE_API Vector2(float x, float y);
		ENGINE_API Vector2(int x, int y);

		ENGINE_API Vector2 operator+(const Vector2& rhs) const;
		ENGINE_API Vector2 operator*(const Vector2& rhs) const;
		ENGINE_API Vector2 operator-(const Vector2& rhs) const;
		ENGINE_API Vector2 operator/(const Vector2& rhs) const;
		ENGINE_API Vector2 operator*(const float& rhs) const;
		ENGINE_API Vector2 operator/(const float& rhs) const;
		ENGINE_API void operator=(const Vector2& rhs);

		ENGINE_API Vector2& operator+=(const Vector2& rhs);
		ENGINE_API Vector2& operator*=(const Vector2& rhs);
		ENGINE_API Vector2& operator-=(const Vector2& rhs);
		ENGINE_API Vector2& operator/=(const Vector2& rhs);
		ENGINE_API Vector2& operator*=(const float& rhs);
		ENGINE_API Vector2& operator/=(const float& rhs);

		static ENGINE_API const Vector2& Zero;
		static ENGINE_API const Vector2& One;
		static ENGINE_API const Vector2& Up;
		static ENGINE_API const Vector2& Left;
		static ENGINE_API const Vector2& Right;
		static ENGINE_API const Vector2& Down;

		float X;
		float Y;
	};
}
