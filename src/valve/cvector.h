#pragma once
#include <numbers>
#include <cstdint>
#include <cmath>
#include <random>

class CVector
{
public:
	constexpr CVector operator+(const CVector& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator-(const CVector& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr CVector operator*(const CVector& other) const noexcept
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	constexpr CVector operator/(const CVector& other) const noexcept
	{
		return { x / other.x, y / other.y, z / other.z };
	}

	constexpr CVector Scale(float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}

	inline CVector ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f 
		};
	}

	void Normalize() noexcept {
		x = std::clamp(x, -89.f, 89.f);
		y = Normalize180(y);
		z = 0.f;
	}

	float Length2D() const {
		return std::sqrtf(x * x + y * y);
	}

	static float Normalize180(float ang) noexcept {
		ang = fmodf(ang + 180, 360);

		if (ang < 0)
			ang += 360;

		return ang - 180;
	}

	float x{ }, y{ }, z{ };
};

__declspec(align(16)) class CVectorAligned : public CVector
{
public:
	constexpr CVectorAligned operator-(const CVectorAligned& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	float w{ };
};
