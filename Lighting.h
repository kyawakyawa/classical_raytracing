#pragma once

#include "Vec3.h"
#include "FColor.h"

struct Lighting{//光源についての情報
	const R distance;//光源までの距離
	const FColor intensity;//光の強さ
	const Vec3 direction;//光源への方向
	Lighting() = delete;
	inline constexpr Lighting(const R d,const FColor &i,const Vec3 &_d) : distance(d),intensity(i),direction(_d.normalized()){};
};
