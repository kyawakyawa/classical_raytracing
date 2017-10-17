#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLightSource.h"

int main(){
	Scene scene(FColor(0.10,0.10,0.10));

	scene.add_shape(new Sphere(Vec3(3,0,25),1,Material(FColor(0.01,0.01,0.01),FColor(0.69,0.00,0.00),FColor(0.30,0.30,0.30),8)));
	scene.add_shape(new Sphere(Vec3(2,0,20),1,Material(FColor(0.01,0.01,0.01),FColor(0.00,0.69,0.00),FColor(0.30,0.30,0.30),8)));
	scene.add_shape(new Sphere(Vec3(1,0,15),1,Material(FColor(0.01,0.01,0.01),FColor(0.00,0.00,0.69),FColor(0.30,0.30,0.30),8)));
	scene.add_shape(new Sphere(Vec3(0,0,10),1,Material(FColor(0.01,0.01,0.01),FColor(0.00,0.69,0.69),FColor(0.30,0.30,0.30),8)));
	scene.add_shape(new Sphere(Vec3(-1,0,5),1,Material(FColor(0.01,0.01,0.01),FColor(0.69,0.00,0.69),FColor(0.30,0.30,0.30),8)));
	scene.add_shape(new Plane(Vec3(0,1,0),Vec3(0,-1,0),Material(FColor(0.01,0.01,0.01),FColor(0.69,0.69,0.69),FColor(0.30,0.30,0.30),8)));

	scene.add_light_source(new PointLightSource(Vec3(-5,5,-5),FColor(1,1,1)));
	//scene.add_light_source(new PointLightSource(Vec3(5,0,-5),FColor(0.50,0.50,0.50)));
	//scene.add_light_source(new PointLightSource(Vec3(5,20,-5),FColor(0.50,0.50,0.50)));
	
	scene.draw();
	return 0;
}
