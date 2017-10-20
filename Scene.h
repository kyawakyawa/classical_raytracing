#pragma once

#include <list>
#include "Shape.h"
#include "LightSource.h"
#include "Intersection_info.h"

struct Scene{
	std::list<Shape*> shapes;
	std::list<LightSource*> light_sources;
	FColor Ia;
	const int HEIGHT = 512;
	const int WIDTH = 512;
	const R INF = 1000000000.0;
	const FColor back;
	const R epsilon = 1.0 / 512;
	const int MAX_DEPTH = 100;

	Scene() = delete;
	Scene(FColor ia): Ia(ia),back(FColor(100.0 / 255,149.0 / 255,237.0 / 255)){};

	void add_shape(Shape *shape){
		shapes.push_back(shape);
	}

	void add_light_source(LightSource *light_source){
		light_sources.push_back(light_source);
	}

	Intersection_info* get_intersection_of_nearest(const Ray &ray) const{
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
	bool is_shadow(const Ray &ray,const R max_t) const {
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

	void recursive_raytrace(FColor &L,const Ray &ray,const FColor &kf,const int depth) const{
		if(depth > MAX_DEPTH)
			return;
		Intersection_info *intersection_info = get_intersection_of_nearest(ray);

		if(intersection_info == nullptr){
			L += back;
			return;
		}

		Intersection_point *intersection = intersection_info->intersection_point;
		Shape *intersection_shape = intersection_info->shape;
		Material material = intersection_shape->get_material(intersection->position);

		L += kf * material.ka * Ia;

		///////////交点の色の計算/////////
		for(LightSource* light_source : light_sources){
			Lighting* ltg = light_source->lighting_at(intersection->position);

			Ray shadow_ray(intersection->position + epsilon * ltg->direction,ltg->direction);
			if(is_shadow(shadow_ray,ltg->distance - epsilon)){
				delete ltg;
				continue;
			}

			FColor &Ii = ltg->intensity;
			R nl = (intersection->normal * ltg->direction);

			if(nl >= 0.0)
				L += kf * material.kd * Ii * nl;

			const R vr = (-ray.direction) * (2 * nl * intersection->normal - ltg->direction);

			if(vr >= 0.0)
				L += kf * material.ks * Ii * std::pow(vr,material.alpha);

			delete ltg;
		}
		///////////////////////////////

		if(material.type == MT_PERFECT_REF){
			Vec3 p = intersection->position + epsilon * (-2.0 * (intersection->normal * ray.direction) * intersection->normal + ray.direction);
			recursive_raytrace(L,Ray(p,-2.0 * (intersection->normal * ray.direction) * intersection->normal + ray.direction),material.kf,depth + 1);
		}
		delete intersection_info;
	}
	void draw() const{
		printf("P3\n%d %d\n255\n", WIDTH,HEIGHT);

		for(int i = 0;i < HEIGHT;i++){
			for(int j = 0;j < WIDTH;j++){
				Ray ray(Vec3(0,0,-5),Vec3(2.0 * j / (WIDTH - 1) - 1,-2.0 * i / (HEIGHT - 1) + 1,5));
				Intersection_info *intersection_info = get_intersection_of_nearest(ray);

				if(intersection_info == nullptr){
					back.print255();
					continue;
				}

				Intersection_point *intersection = intersection_info->intersection_point;
				Shape *intersection_shape = intersection_info->shape;
				Material material = intersection_shape->get_material(intersection->position);

				FColor Ls = material.ka * Ia;

				///////////交点の色の計算/////////
				for(LightSource* light_source : light_sources){
					Lighting* ltg = light_source->lighting_at(intersection->position);

					Ray shadow_ray(intersection->position + epsilon * ltg->direction,ltg->direction);
					if(is_shadow(shadow_ray,ltg->distance - epsilon)){
						delete ltg;
						continue;
					}

					FColor &Ii = ltg->intensity;
					R nl = (intersection->normal * ltg->direction);

					if(nl >= 0.0)
						Ls += material.kd * Ii * nl;

					const R vr = (-ray.direction) * (2 * nl * intersection->normal - ltg->direction);

					if(vr >= 0.0)
						Ls += material.ks * Ii * std::pow(vr,material.alpha);

					delete ltg;
				}
				///////////////////////////////
				if(material.type == MT_PERFECT_REF){
					Vec3 p = intersection->position + epsilon * (-2.0 * (intersection->normal * ray.direction) * intersection->normal + ray.direction);
					recursive_raytrace(Ls,Ray(p,-2.0 * (intersection->normal * ray.direction) * intersection->normal + ray.direction),material.kf,1);
				}


				Ls.print255();
				delete intersection_info;
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
