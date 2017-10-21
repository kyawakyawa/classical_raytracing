#pragma once

#include "FColor.h"

enum Material_type{
    MT_DEFAULT,//通常
    MT_PERFECT_REF,//完全鏡面反射
    MT_REFRACTION//屈折
};

struct Material{
    FColor ka;//環境光反射係数
    FColor kd;//拡散光反射係数
    FColor ks;//鏡面反射係数
    R alpha;//光沢度(>=1)
    Material_type type;//通常　完全鏡面反射 屈折
    R n;//絶対屈折率
    FColor kf;//完全鏡面反射・屈折係数

    Material() = delete;
    Material(FColor a,FColor d,FColor s,R al): ka(a),kd(d),ks(s),alpha(al),type(MT_DEFAULT),kf(FColor(1,1,1)){};
    Material(Material_type t): ka(FColor(0,0,0)),kd(ka),ks(ka),alpha(1),type(t),n(1.51),kf(FColor(1,1,1)){};
    Material(FColor a,FColor d,FColor s,R al,Material_type t): ka(a),kd(d),ks(s),alpha(al),type(t),n(1.51),kf(FColor(1,1,1)){};
    Material(FColor a,FColor d,FColor s,R al,R _n): ka(a),kd(d),ks(s),alpha(al),type(MT_REFRACTION),n(_n),kf(FColor(1,1,1)){};
    Material(FColor a,FColor d,FColor s,R al,Material_type t,FColor f): ka(a),kd(d),ks(s),alpha(al),type(t),n(1.51),kf(f){};
};