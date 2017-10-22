#pragma once

#include <vector>
#include "Shape.h"
#include "LightSource.h"
#include "Intersection_info.h"

struct Scene{
	std::vector<Shape*> shapes;
	std::vector<LightSource*> light_sources;
	const FColor Ia;
	const int HEIGHT = 900;
	const int WIDTH = 900;
	const R INF = 1000000000.0;
	const FColor back;
	const R epsilon = 1.0 / 512;
	const int MAX_DEPTH = 5;

	Scene() = delete;
	inline Scene(const FColor &ia): Ia(ia),back(FColor(100.0 / 255,149.0 / 255,237.0 / 255)){};

	inline void add(Shape *shape){
		shapes.push_back(shape);
	}

	inline void add(LightSource *light_source){
		light_sources.push_back(light_source);
	}

	inline Intersection_info* get_intersection_of_nearest(const Ray &ray) const{
		R min_t = INF;
		Intersection_info *intersection_info = new Intersection_info();

		for(Shape *shape : shapes){
			Intersection_point *intersection = shape->get_intersection(ray);

			if(intersection != nullptr && min_t > intersection->distance){
				intersection_info->rewrite(shape,intersection);
				min_t = intersection->distance;
			}else
				delete intersection;
		}

		if(intersection_info->shape == nullptr)
			return nullptr;

		return intersection_info;
	}
	inline bool is_shadow(const Ray &ray,const R max_t) const {
		for(Shape *shape : shapes){
			Intersection_point *intersection = shape->get_intersection(ray);
			if(intersection != nullptr && max_t > intersection->distance){
				delete intersection;
				return true;
			}
			delete intersection;
		}
		return false;
	}

	inline FColor recursive_raytrace(const Ray &ray,const int depth) const{
		FColor L(0,0,0);
		if(depth > MAX_DEPTH)
			return L;
		const Intersection_info *intersection_info = get_intersection_of_nearest(ray);

		if(intersection_info == nullptr){
			L += back;
			return L;
		}

		const Intersection_point *intersection = intersection_info->intersection_point;
		const Shape *intersection_shape = intersection_info->shape;
		const Material material = intersection_shape->get_material(intersection->position);
		const Vec3 normal = ((ray.direction * intersection->normal < 0.0) ? 1.0 : -1.0) * intersection->normal;

		L += material.ka * Ia;

		///////////交点の色の計算/////////
		for(LightSource* light_source : light_sources){
			const Lighting* ltg = light_source->lighting_at(intersection->position);

			const Ray shadow_ray(intersection->position + epsilon * ltg->direction,ltg->direction);
			if(is_shadow(shadow_ray,ltg->distance - epsilon)){
				delete ltg;
				continue;
			}

			const FColor &Ii = ltg->intensity;
			const R nl = (normal * ltg->direction);

			if(nl >= 0.0)
				L += material.kd * Ii * nl;

			const R vr = (-ray.direction) * (2 * nl * normal - ltg->direction);

			if(vr >= 0.0)
				L += material.ks * Ii * std::pow(vr,material.alpha);

			delete ltg;
		}
		///////////////////////////////

		if(material.type == MT_PERFECT_REF){
			const Vec3 r = -2.0 * (normal * ray.direction) * normal + ray.direction;
			const Vec3 p = intersection->position + epsilon * r;
			L += material.kf * recursive_raytrace(Ray(p,r),depth + 1);
		}

		if(material.type == MT_REFRACTION){
			const R n = ((ray.direction * intersection->normal < 0.0) ? 1.0 / material.n : material.n);
			const R nr = 1.0 / n;

			const R cos1 = -(ray.direction * normal);
			const R cos2 = n * std::sqrt(nr * nr - (1.0 - cos1 * cos1));
			const R omega = nr * cos2 - cos1;

			const R p1 = (nr  * cos1 - cos2) / (nr * cos1 + cos2);
			const R p2 = -omega / (nr * cos2 + cos1);
			const R cr = 0.5 * (p1 * p1 + p2 * p2);

			const Vec3 fe = n * ray.direction - n * omega * normal;

			const Vec3 r = -2.0 * (normal * ray.direction) * normal + ray.direction;
			const Vec3 p = intersection->position + epsilon * r;
			L += cr * material.kf * recursive_raytrace(Ray(p,r),depth + 1);
			L += (1.0 - cr) * material.kf * recursive_raytrace(Ray(intersection->position + epsilon * fe,fe),depth + 1);
		}
		delete intersection_info;
		return L;
	}

	void draw() const{
		printf("P3\n%d %d\n255\n", WIDTH,HEIGHT);

		for(int i = 0;i < HEIGHT;i++){
		#pragma omp parallel for schedule(dynamic, 1) num_threads(4)
			for(int j = 0;j < WIDTH;j++){
				const Ray ray(Vec3(0,0,-5),Vec3(2.0 * j / (WIDTH - 1) - 1,-2.0 * i / (HEIGHT - 1) + 1,5));
				(recursive_raytrace(ray,0)).print255();
			}
		}

	}

	~Scene(){
		for(Shape *shape : shapes)
			delete shape;
		for(LightSource *light_source : light_sources)
			delete light_source;
	}
};
