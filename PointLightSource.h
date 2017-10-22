#pragma once

#include "LightSource.h"

struct PointLightSource : public LightSource{
	const Vec3 position;
	const FColor intensity;

	PointLightSource() = delete;
	inline constexpr PointLightSource(const Vec3 &p,const FColor &i): position(p),intensity(i){};

	inline Lighting* lighting_at(const Vec3& pos) const{
		return new Lighting((position - pos).abs(),intensity,Vec3(position - pos));
	}
};
