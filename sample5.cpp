#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLightSource.h"

int main(){
	Scene scene(FColor(0.10,0.10,0.10));

	scene.add(new Sphere(Vec3(-0.4,-0.65,2.5),0.35,Material(FColor(0.01,0.01,0.01),FColor(0.00,0.00,0.00),FColor(0.30,0.30,0.30),2,MT_PERFECT_REF,FColor(240.0 / 255,210.0 / 255,37.0 / 255))));
	scene.add(new Sphere(Vec3(0.5,-0.65,2),0.35,Material(FColor(0.01,0.01,0.01),FColor(0.1,0.1,0.1),FColor(0.30,0.30,0.30),30,MT_REFRACTION)));
	scene.add(new Plane(Vec3(0,1,0),Vec3(0,-1,0),PL_CHECKERBOARD_CHECK));
	scene.add(new Plane(Vec3(0,-1,0),Vec3(0,1,0),Material(FColor(0.01,0.01,0.01),FColor(100.0 / 255,149.0 / 255,237.0 / 255),FColor(0.30,0.30,0.30),8)));
	scene.add(new Plane(Vec3(-1,0,0),Vec3(1,0,0),Material(FColor(0.01,0.01,0.01),FColor(0.03,0.80,0.03),FColor(0.30,0.30,0.30),8)));
	scene.add(new Plane(Vec3(1,0,0),Vec3(-1,0,0),Material(FColor(0.01,0.01,0.01),FColor(0.80,0.03,0.03),FColor(0.30,0.30,0.30),8)));
	scene.add(new Plane(Vec3(0,0,-1),Vec3(0,0,5),Material(FColor(0.01,0.01,0.01),FColor(0.69,0.69,0.69),FColor(0.30,0.30,0.30),8)));

	scene.add(new PointLightSource(Vec3(0,0.1,2.5),FColor(0.50,0.50,0.50)));
	scene.add(new PointLightSource(Vec3(0,0.3,0.5),FColor(0.33,0.33,0.33)));
	
	scene.draw();
	return 0;
}
