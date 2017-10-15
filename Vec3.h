#pragma once

#include<iostream>
#include<cmath>

typedef double R;

//https://qiita.com/Reputeless/items/96226cfe1282a014b147#5-%E3%83%A1%E3%83%B3%E3%83%90%E9%96%A2%E6%95%B0%E3%82%92%E4%BD%9C%E3%82%8D%E3%81%86
struct Vec3{
		R x;
		R y;
		R z;

		Vec3() = default;//: x(0.0),y(0.0),z(0.0){};
		constexpr Vec3(const R _x,const R _y,const R _z): x(_x),y(_y),z(_z){};

		constexpr Vec3 operator +() const{//　単項+   ex +a
			return *this;
		}
		constexpr Vec3 operator -() const{//  単項-   ex -a
			return{ -x,-y,-z};
		}

		constexpr Vec3 operator + (const Vec3 &obj) const{// 2項+ ex a + b
			return Vec3(this->x + obj.x,this->y + obj.y,this->z + obj.z);
		}
		constexpr Vec3 operator - (const Vec3 &obj) const{// 2項- ex a - b
			return Vec3(this->x - obj.x,this->y - obj.y,this->z - obj.z);
		}

		constexpr R operator * (const Vec3 &obj) const{// 内積 
			return this->x * obj.x + this->y * obj.y + this->z * obj.z;
		}


		constexpr Vec3 operator * (const R a) const{//スカラー積（後ろがスカラー)
			return Vec3(this->x * a,this->y * a,this->z * a);
		}
		constexpr Vec3 operator / (const R a) const{//スカラー除
			return Vec3(this->x / a,this->y / a,this->z / a);
		}

		Vec3& operator +=(const Vec3& obj){
			x += obj.x;
			y += obj.y;
			z += obj.z;
			return *this;
		}
		Vec3& operator -=(const Vec3& obj){
			x -= obj.x;
			y += obj.y;
			z += obj.z;
			return *this;
		}
		Vec3& operator *=(const R a){
			x *= a;
			y *= a;
			z *= a;
			return *this;
		}
		Vec3& operator /=(const R a){
			x /= a;
			y /= a;
			z /= a;
			return *this;
		}

	 	R abs() const{
			return std::sqrt(x * x + y * y + z * z);
		}
		constexpr R abs_square() const{
			return x * x + y * y + z * z;
		}
		Vec3 normalized() const {//正規化（ベクトルの長さを1にする)ベクトル
			R l = abs();
			return { x / l,y / l , z / l};
		}
};

inline constexpr Vec3 operator *(R s,const Vec3& v){//スカラー*ベクトル
	return {s * v.x,s * v.y,s * v.z};
}

template <class Char> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const Vec3& v){
    return os << Char('(') << v.x << Char(',') <<v.y << Char(',') << v.z << Char(')');
}

template <class Char> // 入力ストリーム (x,y,z) と入力する
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, Vec3& v){
    Char unused;
    return is >> unused >> v.x >> unused >> v.y >> unused >> v.z >> unused;
}
