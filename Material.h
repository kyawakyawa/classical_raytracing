#pragma once

#include "FColor.h"

enum Material_type{
    MT_DEFAULT,
    MT_PERFECT_REF
};

struct Material{
    FColor ka;
    FColor kd;
    FColor ks;
    R alpha;
    Material_type type;

    Material() = delete;
    Material(FColor a,FColor d,FColor s,R al): ka(a),kd(d),ks(s),alpha(al),type(MT_DEFAULT){};
    Material(Material_type t): ka(FColor(0,0,0)),kd(ka),ks(ka),alpha(1),type(t){};
    Material(FColor a,FColor d,FColor s,R al,Material_type t): ka(a),kd(d),ks(s),alpha(al),type(t){};
};