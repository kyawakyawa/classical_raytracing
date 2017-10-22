#pragma once

#include "Shape.h"

struct Sphere : public Shape{
	const Vec3 center;
	const R radius;

	Sphere() = delete;
	inline constexpr Sphere(const Vec3 &c,const R &r,const Material &m): Shape(m),center(c),radius(r){};
	
	inline Intersection_point* get_intersection(const Ray &ray) const{
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
		if(t < 0.0){
			t += sqrt_d / A;
			if(t < 0.0)
				return nullptr;
		}

		return new Intersection_point(t,ray.start + t * d,s + t * d);
	}

	inline Material get_material(const Vec3 &position) const {
		return material;
	}
};
