#pragma once

#include "Vec3.h"
#include "LightSource.h"

struct DirectionalLightSource {
	Vec3 direction;
	FColor intensity;
};
