#pragma once

#include <list>
#include "Shape.h"
#include "LightSource.h"
#include "Intersection_info.h"

struct Scene{
    std::list<Shape*> shapes;
    std::list<LightSource*> light_sources;
    FColor Ia;
    const R INF = 1000000000.0;
    
    Scene() = delete;
    Scene(FColor ia): Ia(ia){};

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
            }else
				delete intersection;
        }

        return intersection_info;
    }

    ~Scene(){
        for(Shape *shape : shapes)
            delete shape;
        for(LightSource *light_source : light_sources)
            delete light_source;
    }
};
