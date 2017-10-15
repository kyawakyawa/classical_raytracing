#pragma once

#include "Vec3.h"

struct Intersection_point{
	R distance;//交点までの距離
	Vec3 position;//交点座標
	Vec3 normal;//交点における法線

	Intersection_point() = default;
	Intersection_point(R d,Vec3 p,Vec3 n): distance(d),position(p),normal(n){};
};
