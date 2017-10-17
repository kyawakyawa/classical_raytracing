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
    
    Scene() = delete;
    Scene(FColor ia): Ia(ia),back(FColor(100.0 / 255,149.0 / 255,237.0 / 255)){};

    void add_shape(Shape *shape){
        shapes.push_back(shape);
    }

    void add_light_source(LightSource *light_source){
        light_sources.push_back(light_source);
    }

    Intersection_info* get_intersection_of_nearest(Ray ray){
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

    void draw(){
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

                FColor Ls = intersection_shape->material.ka * Ia;

                for(LightSource* light_source : light_sources){
                    Lighting* ltg = light_source->lighting_at(intersection->position);
                    FColor &Ii = ltg->intensity;
                    R nl = (intersection->normal * ltg->direction);

                    if(nl < 0.0)
                        continue;

                    Ls += intersection_shape->material.kd * Ii * nl;

                    const R vr = (-ray.direction) * (2 * nl * intersection->normal - ltg->direction);

                    if(vr < 0.0)
                        continue;

                    Ls += intersection_shape->material.ks * Ii * std::pow(vr,intersection_shape->material.alpha);
                    delete ltg;
                }

                Ls.print255();
                delete intersection;
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
