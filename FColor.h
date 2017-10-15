#pragma once
#include<cstdio>
#include<algorithm>

typedef double R;

struct FColor{
    R red;
    R green;
    R blue;

    FColor() = delete;
    constexpr FColor(R r,R g,R b): red(r),green(g),blue(b) {};

    void set(R r,R g,R b){
        red = r;green = g;blue = b;
    }

    void print255() const{
        int r = 255 * red;
        int g = 255 * green;
        int b = 255 * blue;
        r = std::max(0,r);r = std::min(255,r);
        g = std::max(0,g);g = std::min(255,g);
        b = std::max(0,b);b = std::min(255,b);

        printf("%d %d %d\n",r,g,b);
    }

    constexpr FColor operator + (const FColor &obj) const{// 2項+ ex a + b
        return FColor(this->red + obj.red,this->green + obj.green,this->blue + obj.blue);
    }
    constexpr FColor operator - (const FColor &obj) const{// 2項- ex a - b
        return FColor(this->red- obj.red,this->green - obj.green,this->blue - obj.blue);
    }
    constexpr FColor operator * (const FColor &obj) const{// 要素同士の掛け算
        return FColor(this->red * obj.red, this->green * obj.green , this->blue * obj.blue);
    }

    constexpr FColor operator * (const R r) const{
        return FColor(red * r,green * r,blue * r);
    }

    FColor& operator +=(const FColor& obj){
        red += obj.red;
        green += obj.green;
        blue += obj.blue;
        return *this;
    }
    FColor& operator -=(const FColor& obj){
        red -= obj.red;
        green += obj.green;
        blue += obj.blue;
        return *this;
    }
    FColor& operator *=(const FColor& obj){
        red *= obj.red;
        green *= obj.green;
        blue *= obj.blue;
        return *this;
    }
    FColor& operator *=(const R r){
        red *= r;
        green *= r;
        blue *= r;
        return *this;
    }
};

inline FColor operator *(const R s,const FColor& v){//スカラー*ベクトル
	return {s * v.red,s * v.green,s * v.blue};
}