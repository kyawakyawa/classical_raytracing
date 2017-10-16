#pragma once

#include "Vec3.h"
#include "Material.h"
#include "Ray.h"
#include "Intersection_point.h"

struct Shape{
	Material material;

	Shape() = delete;
	Shape(Material m): material(m){};

	virtual Intersection_point* get_intersection(const Ray &ray) const = 0;

	virtual ~Shape() = default;
};
