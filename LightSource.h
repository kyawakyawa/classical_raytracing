#pragma once

#include "Vec3.h"
#include "Lighting.h"

struct LightSource{//光源の抽象クラス
	inline constexpr LightSource() = default;

	inline virtual Lighting* lighting_at(const Vec3& pos) const = 0;//引数の位置からの光源の距離、強さ、方向を返す

	virtual ~LightSource() = default;
};
