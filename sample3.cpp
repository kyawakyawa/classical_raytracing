#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLightSource.h"

int main(){
	Scene scene(FColor(0.10,0.10,0.10));

	scene.add_shape(new Sphere(Vec3(0,0,-4),1.5,Material(FColor(0.01,0.01,0.01),FColor(0.00,0.00,0.69),FColor(0.30,0.30,0.30),8)));

	scene.add_light_source(new PointLightSource(Vec3(0,0.9,-4),FColor(1.00,1.00,1.00)));
	
	scene.draw();
	return 0;
}
