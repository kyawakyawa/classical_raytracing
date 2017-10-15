#pragma once

#include "FColor.h"

struct Material{
    FColor ka;
    FColor kd;
    FColor ks;
    R alpha;

    Material() = delete;
    Material(FColor a,FColor d,FColor s,R al): ka(a),kd(d),ks(s),alpha(al){};
};