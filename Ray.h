#pragma once

#include "Vec3.h"

struct Ray{
	const Vec3 start;
	const Vec3 direction;

	Ray() = delete;
	inline Ray(Vec3 s,Vec3 d): start(s),direction(d.normalized()){};

};
