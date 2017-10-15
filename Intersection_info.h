#pragma once

#include "Shape.h"
#include "Intersection_point.h"

struct Intersection_info{
    Shape *shape;
    Intersection_point *intersection_point;

    Intersection_info(): shape(nullptr),intersection_point(nullptr){};
    Intersection_info(Shape *s,Intersection_point *i): shape(s),intersection_point(i){};

    void rewrite(Shape *s,Intersection_point *i){
        delete intersection_point;
        shape = s;
        intersection_point = i;
    }

    ~Intersection_info(){
        delete intersection_point;
    }
};