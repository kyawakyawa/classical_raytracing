#pragma once

#include "Vec3.h"
#include "Lighting.h"

struct LightSource{
	inline constexpr LightSource() = default;

	inline virtual Lighting* lighting_at(const Vec3& pos) const = 0;

	virtual ~LightSource() = default;
};
