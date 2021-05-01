#ifndef __VEC2_H__
#define __VEC2_H__ 1
//=============================================================================
#include "BaseTypes.h"
//#include "Maths.h"
//=============================================================================
struct DLL_API Edge {
	union {
		struct { int x, y; };
		int v[2];
	};
	//-----------------------------------------------------------------------------
	INLINE Edge() :x(0), y(0) {}
	INLINE Edge(int a, int b) : x(a), y(b) {}
	INLINE Edge(const int *v) : x(v[0]), y(v[1]) {}
	INLINE Edge(const int f) : x(f), y(f) {}
	INLINE Edge(const Edge &v) : x(v.x), y(v.y) {}
	//-----------------------------------------------------------------------------
	INLINE operator int*() { return (int*)&x; }
	INLINE operator const int*()const { return (int*)&x; }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct DLL_API vec2q {//u64_t
	union {
		struct { u64_t x, y; };
		u64_t v[2];
	};
	//-----------------------------------------------------------------------------
	INLINE vec2q() :x(0), y(0) {}
	INLINE vec2q(u64_t a, u64_t b) : x(a), y(b) {}
	INLINE vec2q(const u64_t *v) : x(v[0]), y(v[1]) {}
	INLINE vec2q(const u64_t f) : x(f), y(f) {}
	INLINE vec2q(const vec2q &v) : x(v.x), y(v.y) {}
	//-----------------------------------------------------------------------------
	INLINE const vec2q operator*(u64_t f)const { return vec2q(x*f, y*f); }
	INLINE const vec2q operator/(u64_t f)const { return vec2q(x / f, y / f); }
	INLINE const vec2q operator+(const vec2q &v)const { return vec2q(x + v.x, y + v.y); }
	INLINE const vec2q operator-(const vec2q &v)const { return vec2q(x - v.x, y - v.y); }//unsigned
	//INLINE const vec2q operator-()const{return vec2q(-x,-y);} unsigned
	INLINE const vec2q operator*(const vec2q &v)const { return vec2q(x*v.x, y*v.y); }
	//----------------------------------------------------------------------------- 
	INLINE vec2q &operator*=(u64_t f) { return *this = *this*f; }
	INLINE vec2q &operator/=(u64_t f) { return *this = *this / f; }
	INLINE vec2q &operator+=(const vec2q &v) { return *this = *this + v; }
	INLINE vec2q &operator-=(const vec2q &v) { return *this = *this - v; }
	INLINE vec2q &operator*=(const vec2q &v) { return *this = *this*v; }
	//-----------------------------------------------------------------------------
	INLINE operator u64_t*() { return (u64_t*)&x; }
	INLINE operator const u64_t*()const { return (u64_t*)&x; }
	INLINE void set(const u64_t &a, const u64_t &b) { x = a; y = b; }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct DLL_API vec2u {
	union {
		struct { u32_t x, y; };
		u32_t v[2];
	};
	//-----------------------------------------------------------------------------
	INLINE vec2u() :x(0), y(0) {}
	INLINE vec2u(u32_t a, u32_t b) : x(a), y(b) {}
	INLINE vec2u(const u32_t *v) : x(v[0]), y(v[1]) {}
	INLINE vec2u(const u32_t f) : x(f), y(f) {}
	INLINE vec2u(const vec2u &v) : x(v.x), y(v.y) {}
	//-----------------------------------------------------------------------------
	INLINE const vec2u operator*(u32_t f)const { return vec2u(x*f, y*f); }
	INLINE const vec2u operator/(u32_t f)const { return vec2u(x / f, y / f); }
	INLINE const vec2u operator+(const vec2u &v)const { return vec2u(x + v.x, y + v.y); }
	INLINE const vec2u operator-(const vec2u &v)const { return vec2u(x - v.x, y - v.y); }//unsigned
	//INLINE const vec2u operator-()const{return vec2u(-x,-y);} unsigned
	INLINE const vec2u operator*(const vec2u &v)const { return vec2u(x*v.x, y*v.y); }
	//----------------------------------------------------------------------------- 
	INLINE vec2u &operator*=(u32_t f) { return *this = *this*f; }
	INLINE vec2u &operator/=(u32_t f) { return *this = *this / f; }
	INLINE vec2u &operator+=(const vec2u &v) { return *this = *this + v; }
	INLINE vec2u &operator-=(const vec2u &v) { return *this = *this - v; }
	INLINE vec2u &operator*=(const vec2u &v) { return *this = *this*v; }
	//-----------------------------------------------------------------------------
	INLINE operator u32_t*() { return (u32_t*)&x; }
	INLINE operator const u32_t*()const { return (u32_t*)&x; }
	INLINE void set(const u32_t &a, const u32_t &b) { x = a; y = b; }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct vec3;//FD
struct vec4;//FD
//=============================================================================
struct DLL_API vec2 {//8
	union {
		struct { float x, y; };
		float v[2];
	};
	//-----------------------------------------------------------------------------
	INLINE vec2(){}// :x(0), y(0) 
	INLINE vec2(float a, float b) : x(a), y(b) {}
	INLINE vec2(const float *v) : x(v[0]), y(v[1]) {}
	INLINE vec2(const float f) : x(f), y(f) {}
	INLINE vec2(const vec2 &v) : x(v.x), y(v.y) {}
	INLINE vec2(const vec3 &v);//FD
	INLINE vec2(const vec4 &v);//FD
	//-----------------------------------------------------------------------------
	INLINE const vec2 operator*(float f)const { return vec2(x * f, y * f); }
	INLINE const vec2 operator/(float f)const { return vec2(x / f, y / f); }
	INLINE const vec2 operator-()const { return vec2(-x, -y); }
	//INLINE const vec2 operator=(const float f)const{return vec2(f,f);}
	INLINE const vec2 operator+(const vec2 &v)const { return vec2(x + v.x, y + v.y); }
	INLINE const vec2 operator-(const vec2 &v)const { return vec2(x - v.x, y - v.y); }
	INLINE const vec2 operator*(const vec2 &v)const { return vec2(x * v.x, y * v.y); }
	INLINE const vec2 operator/(const vec2 &v)const { return vec2(x / v.x, y / v.y); }
	//----------------------------------------------------------------------------- 
	INLINE vec2 &operator*=(float f) { return *this = *this * f; }
	INLINE vec2 &operator/=(float f) { return *this = *this / f; }
	INLINE vec2 &operator+=(const vec2 &v) { return *this = *this + v; }
	INLINE vec2 &operator-=(const vec2 &v) { return *this = *this - v; }
	INLINE vec2 &operator*=(const vec2 &v) { return *this = *this * v; }
	INLINE vec2 &operator/=(const vec2 &v) { return *this = *this / v; }
	//-----------------------------------------------------------------------------
	INLINE operator float*() { return (float*)&x; }
	INLINE operator const float*()const { return (float*)&x; }
	//-----------------------------------------------------------------------------
	INLINE float mag()const { return x * x + y * y; }
	INLINE float len()const { return sqrt(x * x + y * y); }
	//-----------------------------------------------------------------------------
	INLINE vec2 &norm() {
		const float len = sqrt(x * x + y * y);
		if (len > EPSILON) {
			const float ilen = 1.0f / len;
			x *= ilen; y *= ilen;
		}
		return *this;
	}
	//-----------------------------------------------------------------------------
	INLINE void set(const float &a, const float &b) { x = a; y = b; }
	INLINE void set(const float &a) { x = a; y = a; }
	//-----------------------------------------------------------------------------
	INLINE vec2 rotZ(float rad) { return vec2(x*cos(rad) - y * sin(rad), x*sin(rad) + y * cos(rad)); }//normal=tangent.rotZ(-HPI);
	INLINE vec2 rotZ90() { return vec2(-y, x); }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
INLINE  vec2 floor2(const vec2 &v) { return vec2(floor(v.x), floor(v.y)); }
INLINE  vec2 fract2(const vec2 &v) { return vec2(fract(v.x), fract(v.y)); }
//=============================================================================
INLINE float dot2(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
INLINE float len2(const vec2 &v) { return sqrt(v.x*v.x + v.y*v.y); }
INLINE vec2 abs2(const vec2 &a) { return vec2(fabs(a.x), fabs(a.y)); }
INLINE vec2 sincos(float a) { return vec2(sin(a), cos(a)); }
//=============================================================================
INLINE vec2 lerp2(const vec2 &a, const vec2 &b, const float &t) { return a + (b - a)*t; }
//=============================================================================
//INLINE vec2 cross(const vec2 &a,const vec2 &b){return vec2(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);}
//=============================================================================
INLINE float mag2(const vec2 &p) { return p.mag(); }
//=============================================================================
INLINE vec2 norm2(const vec2 &a) {
	const float len = sqrt(a.x*a.x + a.y*a.y);
	if (len > EPSILON) {
		const float ilen = 1.0f / len;
		return vec2(a.x*ilen, a.y*ilen);
	}
	return a;
}
//=============================================================================
INLINE bool LineSide(const vec2 &a, const vec2 &b, const vec2 &c) {//return isLeft(v[a],v[b],v[c]);
	vec2 N(b.y - a.y, a.x - b.x);// vec3f N;N.normal(v[a],v[b],viewer);
	return dot2(N, c) > dot2(N, a);
}
//=============================================================================
#endif
