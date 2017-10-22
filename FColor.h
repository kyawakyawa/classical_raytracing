#pragma once
#include<cstdio>
#include<algorithm>

typedef double R;

struct FColor{
    R red;
    R green;
    R blue;

    FColor() = default;
    inline constexpr FColor(R r,R g,R b): red(r),green(g),blue(b) {};

    inline void set(R r,R g,R b){//セッター
        red = r;green = g;blue = b;
    }

    inline void print255() const{//出力
        int r = 255 * red;
        int g = 255 * green;
        int b = 255 * blue;
        r = std::max(0,r);r = std::min(255,r);
        g = std::max(0,g);g = std::min(255,g);
        b = std::max(0,b);b = std::min(255,b);

        printf("%d %d %d\n",r,g,b);
    }

    /*inline FColor fix(){
        R r = std::max(0.0,red);r = std::min(1.0,red);
        R g = std::max(0.0,green);g = std::min(1.0,green);
        R b = std::max(0.0,blue);b = std::min(1.0,blue);
        return FColor(r,g,b);
    }*/

    inline constexpr FColor operator + (const FColor &obj) const{// 2項+ ex a + b
        return FColor(this->red + obj.red,this->green + obj.green,this->blue + obj.blue);
    }
    inline constexpr FColor operator - (const FColor &obj) const{// 2項- ex a - b
        return FColor(this->red- obj.red,this->green - obj.green,this->blue - obj.blue);
    }
    inline constexpr FColor operator * (const FColor &obj) const{// 要素同士の掛け算
        return FColor(this->red * obj.red, this->green * obj.green , this->blue * obj.blue);
    }

    inline constexpr FColor operator * (const R r) const{//要素同士の掛け算
        return FColor(red * r,green * r,blue * r);
    }

    inline FColor& operator +=(const FColor& obj){
        red += obj.red;
        green += obj.green;
        blue += obj.blue;
        return *this;
    }
    inline FColor& operator -=(const FColor& obj){
        red -= obj.red;
        green += obj.green;
        blue += obj.blue;
        return *this;
    }
    inline FColor& operator *=(const FColor& obj){
        red *= obj.red;
        green *= obj.green;
        blue *= obj.blue;
        return *this;
    }
    inline FColor& operator *=(const R r){
        red *= r;
        green *= r;
        blue *= r;
        return *this;
    }
};

inline constexpr FColor operator *(const R s,const FColor& v){//スカラー*ベクトル
	return {s * v.red,s * v.green,s * v.blue};
}