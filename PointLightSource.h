#pragma once

#include "LightSource.h"

struct PointLightSource : public LightSource{//点光源
	const Vec3 position;//光源の位置
	const FColor intensity;//強さ

	PointLightSource() = delete;
	inline constexpr PointLightSource(const Vec3 &p,const FColor &i): position(p),intensity(i){};

	inline Lighting* lighting_at(const Vec3& pos) const{
		return new Lighting((position - pos).abs(),intensity,Vec3(position - pos));
	}
};
