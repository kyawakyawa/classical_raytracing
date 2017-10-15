#pragma once

#include "Vec3.h"
#include "Lighting.h"

struct LightSource{
	constexpr LightSource() = default;

	virtual Lighting* lighting_at(Vec3& pos) const = 0;

	virtual ~LightSource() = 0;
};
