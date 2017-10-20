#pragma once

#include "Shape.h"

struct Sphere : public Shape{
	Vec3 center;
	R radius;

	Sphere() = delete;
	Sphere(Vec3 c,R r,Material m): Shape(m),center(c),radius(r){};
	
	Intersection_point* get_intersection(const Ray &ray) const{
		const Vec3 &d = ray.direction;
		const Vec3 s = ray.start - center;
		const R A = d.abs_square();
		const R B = 2 * (s * d);
		const R C = s.abs_square() - radius * radius;
		const R D = B * B - 4.0 * A * C;
		
		if(D < 0.0)
			return nullptr;

		const R sqrt_d = std::sqrt(D);
		R t = (-B - sqrt_d) * 0.5 / A;
		//R nd = 1.0;
		if(t < 0.0){
			t += sqrt_d / A;
			if(t < 0.0)
				return nullptr;
			//nd *= -1.0;
		}

		return new Intersection_point(t,ray.start + t * d,/*nd * */(s + t * d).normalized());
	}

	Material get_material(Vec3 &position) const {
		return material;
	}
};
