#pragma once

#include "Shape.h"

enum Plane_type{
	PL_DEFAULT,//通常
	PL_CHECKERBOARD_CHECK//チェッカーボード・チェック xz平面に垂直な平面である必要あり
};

struct Plane: public Shape{
	const Vec3 normal;
	const Vec3 position;
	const  Plane_type type;
	const R edge = 0.25;//チェックの一辺の長さ

	Plane() = delete;
	inline Plane(Vec3 n,Vec3 p,Material m): Shape(m),normal(n.normalized()),position(p),type(PL_DEFAULT){};
	inline Plane(Vec3 n,Vec3 p,Plane_type t): Shape(Material(MT_DEFAULT)),normal(n.normalized()),position(p),type(t){};
	
	inline Intersection_point* get_intersection(const Ray &ray) const{//交点と距離を取得
		const Vec3 &d = ray.direction;
		Vec3 s2;

		////平面上のもう一つの天を取得
		if(std::abs(normal.x) > 1e-9)
			s2 = Vec3(-(normal.y + normal.z) / normal.x,1,1);
		else if(std::abs(normal.y) > 1e-9)
			s2 = Vec3(1,-(normal.x + normal.z) / normal.y,1);
		else
			s2 = Vec3(1,1,-(normal.x + normal.y) / normal.z);

		const Vec3 s = ray.start - (s2 + position);

		if(d * normal == 0)//レイと平面が並行
			return nullptr;

		const R t = -(s * normal) / (d * normal);

		if(t < 0.0)//平面が視線の後側
			return nullptr;

		return new Intersection_point(t,ray.start + t * d,normal);
	}

	inline Material get_material(const Vec3 &position) const {
		if(type == PL_CHECKERBOARD_CHECK){
			const Vec3 d = (this->position - position) / edge;
			const int x = (d.x < 0.0) ? d.x - 1.0:d.x;
			const int z = (d.z < 0.0) ? d.z - 1.0:d.z;
			bool even_x,even_z;
			even_x = (x % 2 == 0);
			even_z = (z % 2  == 0);

			return (even_x == even_z) ? Material(FColor(0.01,0.01,0.01),FColor(0.69,0.69,0.69),FColor(0.30,0.30,0.30),8) : Material(FColor(0.01,0.01,0.01),FColor(0.0,0.0,0.0),FColor(0.30,0.30,0.30),8);
		}
		return material;
	}
};
