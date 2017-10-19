#pragma once

#include "Shape.h"

struct Plane: public Shape{
	Vec3 normal;
	Vec3 position;

	Plane() = delete;
	Plane(Vec3 n,Vec3 p,Material m): Shape(m),normal(n.normalized()),position(p){};
	
	Intersection_point* get_intersection(const Ray &ray) const{
		const Vec3 &d = ray.direction;
		Vec3 s2;

		if(std::abs(normal.x) > 1e-9)
			s2 = Vec3(-(normal.y + normal.z) / normal.x,1,1);
		else if(std::abs(normal.y) > 1e-9)
			s2 = Vec3(1,-(normal.x + normal.z) / normal.y,1);
		else
			s2 = Vec3(1,1,-(normal.x + normal.y) / normal.z);

		const Vec3 s = ray.start - (s2 + position);

		if(d * normal == 0)
			return nullptr;

		const R t = -(s * normal) / (d * normal);

		if(t < 0.0)
			return nullptr;

		const R nd = (ray.direction * normal < 0.0) ? 1.0 : -1.0; 

		return new Intersection_point(t,ray.start + t * d,nd * normal);
	}

	Material get_material(Vec3 &position) const {
		return material;
	}
};
