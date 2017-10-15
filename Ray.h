#pragma once

#include "Vec3.h"

struct Ray{
	Vec3 start;
	Vec3 direction;

	Ray() = delete;
	Ray(Vec3 s,Vec3 d): start(s),direction(d.normalized()){};

	Vec3 get_point(const R t){
		return t * direction + start;
	}
};
