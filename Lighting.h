#pragma once

#include "Vec3.h"
#include "FColor.h"

struct Lighting{
	R distance;
	FColor intensity;
	Vec3 direction;
	Lighting() = delete;
	Lighting(R d,FColor i,Vec3 _d) : distance(d),intensity(i),direction(_d.normalized()){};
};
