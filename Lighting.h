#pragma once

#include "Vec3.h"
#include "FColor.h"

struct Lighting{
	const R distance;
	const FColor intensity;
	const Vec3 direction;
	Lighting() = delete;
	inline constexpr Lighting(const R d,const FColor &i,const Vec3 &_d) : distance(d),intensity(i),direction(_d.normalized()){};
};
