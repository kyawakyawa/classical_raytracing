#pragma once

#include "LightSource.h"

struct PointLightSource : public LightSource{
	Vec3 position;
	FColor intensity;

	PointLightSource() = delete;
	PointLightSource(Vec3 p,FColor i): position(p),intensity(i){};

	Lighting* lighting_at(Vec3& pos) const{
		/*R distance = (position - pos).abs();
		Vec3 direction = (position - pos).normalized();*/
		return new Lighting((position - pos).abs(),intensity,Vec3(position - pos));
	}
};
