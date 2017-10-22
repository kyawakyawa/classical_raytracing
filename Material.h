#pragma once

#include "FColor.h"

enum Material_type{
    MT_DEFAULT,//通常
    MT_PERFECT_REF,//完全鏡面反射
    MT_REFRACTION//屈折
};

struct Material{
    const FColor ka;//環境光反射係数
    const FColor kd;//拡散光反射係数
    const FColor ks;//鏡面反射係数
    const R alpha;//光沢度(>=1)
    const Material_type type;//通常　完全鏡面反射 屈折
    const R n = 1.51;//絶対屈折率
    const FColor kf;//完全鏡面反射・屈折係数

    inline Material() = delete;
    inline Material(const FColor &a,const FColor &d,const FColor &s,R al): ka(a),kd(d),ks(s),alpha(al),type(MT_DEFAULT),kf(FColor(1,1,1)){};
    inline Material(Material_type t): ka(FColor(0,0,0)),kd(ka),ks(ka),alpha(1),type(t),n(1.51),kf(FColor(1,1,1)){};
    inline Material(const FColor &a,const FColor &d,const FColor &s,R al,Material_type t): ka(a),kd(d),ks(s),alpha(al),type(t),n(1.51),kf(FColor(1,1,1)){};
    inline Material(const FColor &a,const FColor &d,const FColor &s,R al,R _n): ka(a),kd(d),ks(s),alpha(al),type(MT_REFRACTION),n(_n),kf(FColor(1,1,1)){};
    inline Material(const FColor &a,const FColor &d,const FColor &s,R al,Material_type t,FColor f): ka(a),kd(d),ks(s),alpha(al),type(t),n(1.51),kf(f){};
};