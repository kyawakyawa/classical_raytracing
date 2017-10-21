#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLightSource.h"

int main(){
	Scene scene(FColor(0.10,0.10,0.10));

	scene.add(new Sphere(Vec3(-0.4,-0.65,3),0.35,Material(MT_PERFECT_REF)));
	scene.add(new Sphere(Vec3(0.5,-0.65,2),0.35,Material(MT_REFRACTION)));
	scene.add(new Plane(Vec3(0,1,0),Vec3(0,-1,0),Material(FColor(0.00,0.00,0.00),FColor(1.00,1.00,1.00),FColor(0.00,0.00,0.00),8)));
	scene.add(new Plane(Vec3(0,-1,0),Vec3(0,1,0),Material(FColor(0.00,0.00,0.00),FColor(1.00,1.00,1.00),FColor(0.00,0.00,0.00),8)));
	scene.add(new Plane(Vec3(-1,0,0),Vec3(1,0,0),Material(FColor(0.00,0.00,0.00),FColor(0.00,1.00,0.00),FColor(0.00,0.00,0.00),8)));
	scene.add(new Plane(Vec3(1,0,0),Vec3(-1,0,0),Material(FColor(0.00,0.00,0.00),FColor(1.00,0.00,0.00),FColor(0.00,0.00,0.00),8)));
	scene.add(new Plane(Vec3(0,0,-1),Vec3(0,0,5),Material(FColor(0.00,0.00,0.00),FColor(1.00,1.00,1.00),FColor(0.00,0.00,0.00),8)));

	scene.add(new PointLightSource(Vec3(0,0.9,2.5),FColor(1.00,1.00,1.00)));
	
	scene.draw();
	return 0;
}
