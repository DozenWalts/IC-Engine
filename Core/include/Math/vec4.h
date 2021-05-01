#ifndef __VEC4_H__
#define __VEC4_H__ 1

#include "vec3.h"

//struct DLL_API vec4{
//	union{
//		struct{float x,y,z,w;}
//		float v[4];
//	}
//	//vec4() {} // pod have no constructor to use with union in mat4 by gcc
//	INLINE void set(const float &a, const float &b, const float &c, const float &d) { x = a; y = b; z = c; w = d; }
//	INLINE void set(const int &a, const int &b, const int &c, const int &d) { x = (float)a; y = (float)b; z = (float)c; w = (float)d; }
//	INLINE void set(const vec3 &a, const float &b) { x = a.x; y = a.y; z = a.z; w = b; }
//	INLINE void set(const float &a) { x = a; y = a; z = a; w = a; }
//}
//==============================================================================
struct DLL_API Face4 {
	union {
		struct { u32_t x, y, z, w; };
		u32_t v[4];
	};
	//------------------------------------------------------------------------------
	INLINE Face4() :x(0), y(0), z(0), w(0) {}
	//------------------------------------------------------------------------------
	INLINE Face4(const u32_t &a, const u32_t &b, const u32_t &c, const u32_t &d) :x(a), y(b), z(c), w(d) {}
	//------------------------------------------------------------------------------
	INLINE operator u32_t*() { return (u32_t*)&x; }
	INLINE operator const u32_t*()const { return (u32_t*)&x; }
	//------------------------------------------------------------------------------
	INLINE void set(const u32_t &a, const u32_t &b, const u32_t &c, const u32_t &d) { x = a; y = b; z = c; w = d; }
	INLINE void set(const u32_t &a) { x = a; y = a; z = a; w = a; }
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
};
//==============================================================================
struct DLL_API vec4i {
	union {
		struct { int x, y, z, w; };
		int v[4];
	};
	//------------------------------------------------------------------------------
	INLINE vec4i() :x(0), y(0), z(0), w(0) {}
	INLINE vec4i(const vec3i &p) :x(p.x), y(p.y), z(p.z), w(0) {}
	//------------------------------------------------------------------------------
	INLINE operator int*() { return (int*)&x; }
	INLINE operator const int*()const { return (int*)&x; }
	//------------------------------------------------------------------------------
	INLINE void set(const int &a, const int &b, const int &c, const int &d) { x = a; y = b; z = c; w = d; }
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
};
//==============================================================================
struct DLL_API vec4 {//16
	union {
		struct { float x, y, z, w; };
		float v[4];
	};
	//------------------------------------------------------------------------------
	INLINE vec4(){}// =default;//
	INLINE vec4(const float &a, const float &b, const float &c, const float &d) :x(a), y(b), z(c), w(d) {}
	INLINE vec4(const int &a, const int &b, const int &c, const int &d) :x((float)a), y((float)b), z((float)c), w((float)d) {}
	INLINE vec4(const u32_t &a, const u32_t &b, const u32_t &c, const u32_t &d) :x((float)a), y((float)b), z((float)c), w((float)d) {}
	INLINE vec4(const float &f) :x(f), y(f), z(f), w(f) {}
	INLINE vec4(const float *f) :x(f[0]), y(f[1]), z(f[2]), w(f[3]) {}
	INLINE vec4(const vec2 &p) :x(p.x), y(p.y), z(0), w(0) {}
	INLINE vec4(const vec3 &p) :x(p.x), y(p.y), z(p.z), w(0) {}//4mat w=0!!!!!!!!!!!!!!!!!????????????????????
	INLINE vec4(const vec3 &p, const float &f) :x(p.x), y(p.y), z(p.z), w(f) {}
	//------------------------------------------------------------------------------
	INLINE void set(const float &a, const float &b, const float &c, const float &d) { x = a; y = b; z = c; w = d; }
	//INLINE void set(const int &a, const int &b, const int &c, const int &d) { x = (float)a; y = (float)b; z = (float)c; w = (float)d; }// matching proto fith upper
	INLINE void set(const vec3 &a, const float &b) { x = a.x; y = a.y; z = a.z; w = b; }
	INLINE void set(const float &a) { x = a; y = a; z = a; w = a; }
	//------------------------------------------------------------------------------
	INLINE float mag()const { return x*x + y*y + z*z + w*w; }
	INLINE float len()const { return sqrt(x*x + y*y + z*z + w*w); }
	//------------------------------------------------------------------------------
	INLINE void norm() {
		const float len = sqrt(x*x + y*y + z*z + w*w);
		if (len > EPSILON) {
			const float ilen = 1.0f / len;
			x *= ilen; y *= ilen; z *= ilen; w *= ilen;
		}
		//return *this;
	}
	//------------------------------------------------------------------------------
	INLINE operator float*() { return (float*)&x; }
	INLINE operator const float*()const { return (float*)&x; }
	//------------------------------------------------------------------------------
	INLINE bool operator ==(const vec4 &a)const { return (equal(x, a.x) && equal(y, a.y) && equal(z, a.z) && equal(w, a.w)); }
	INLINE bool operator !=(const vec4 &a)const { return !(*this == a); }
	//------------------------------------------------------------------------------ 
	//vec4 operator=(const vec3 &v) { return vec4(v,0.0f); }// vec4 ret; ret.set(v, 0); return ret;
	//------------------------------------------------------------------------------
	INLINE const vec4 operator-(float f)const { return vec4(x - f, y - f, z - f, w - f); }//w-f??
	INLINE const vec4 operator-(const vec4 &a)const { return vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
	INLINE const vec4 operator-()const { return vec4(-x, -y, -z, -w); }
	//INLINE const vec4 operator-(float f)const { vec4 ret;ret.set(x - f, y - f, z - f, w - f);return ret; }//w-f??
	//INLINE const vec4 operator-(const vec4 &a)const { vec4 ret;ret.set(x - a.x, y - a.y, z - a.z, w - a.w);return ret; }
	//INLINE const vec4 operator-()const { vec4 ret;ret.set(-x, -y, -z, -w);return ret; }
	INLINE vec4 &operator-=(const vec4 &a) { return *this = *this - a; }
	//------------------------------------------------------------------------------
	INLINE const vec4 operator+(float f)const { return vec4(x + f, y + f, z + f, w + f); }
	INLINE const vec4 operator+(const vec4 &a)const { return vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
	//INLINE const vec4 operator+(float f)const { vec4 ret;ret.set(x + f, y + f, z + f, w + f);return ret; }
	//INLINE const vec4 operator+(const vec4 &a)const { vec4 ret;ret.set(x + a.x, y + a.y, z + a.z, w + a.w);return ret; }
	//INLINE vec4 &operator+=(const vec4 &a) { return *this = *this + a; }
	//------------------------------------------------------------------------------
	INLINE const vec4 operator*(float f)const { return vec4(x*f, y*f, z*f, w*f); }
	//INLINE const vec4 operator*(float f)const { vec4 ret;ret.set(x*f, y*f, z*f, w*f);return ret; }
	//INLINE const vec4 operator*(const vec4 &a)const{return vec4(x*a.x,y*a.y,z*a.z,w*a.w);}// dot4?
	INLINE vec4 &operator*=(float f) { return *this = *this*f; }
	//INLINE vec4 &operator*=(const vec4 &v){return *this=*this*v;}
	//------------------------------------------------------------------------------
	INLINE const vec4 operator/(float f)const { return vec4(x / f, y / f, z / f, w / f); }
	//INLINE const vec4 operator/(float f)const { vec4 ret;ret.set(x / f, y / f, z / f, w / f);return ret; }
	INLINE vec4 &operator/=(float f) { return *this = *this / f; }
	//INLINE vec3 intPlane(const vec3 &S,const vec3 &D)const;//FD dot {return S+D*dot(this,S)/-dot(N,D);}
	//------------------------------------------------------------------------------
	//INLINE const vec4 operator=(const float f)const{return vec4(f,f,f,f);}
	//INLINE vec4 &operator=(const float &f){return vec4(f,f,f,f);}
	//------------------------------------------------------------------------------
	INLINE const vec2 operator*(const vec2 &f)const {//mat2*vec2
		return vec2(x*f.x + y * f.y, z*f.x + w * f.y);
		//return vec2(x*f.x + z*f.y, y*f.x + w*f.y); - no
	}
	//------------------------------------------------------------------------------
	INLINE void identity() {// 2d rotation matrix
		x = z = 1.0f;
		y = w = 0.0f;
	}
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
};//end vec4
//==============================================================================
INLINE vec4 floor4(const vec4 &v) { return vec4(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w)); }
INLINE vec4 fract4(const vec4 &v) { return vec4(fract(v.x), fract(v.y), fract(v.z), fract(v.w)); }
//static vec4 floor4(const vec4 &v) { vec4 ret;ret.set(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w));return ret; }
//static vec4 fract4(const vec4 &v) { vec4 ret;ret.set(fract(v.x), fract(v.y), fract(v.z), fract(v.w));return ret; }
//==============================================================================
INLINE vec4 lerp4(const vec4 &a, const vec4 &b, const float &t) { return a + (b - a)*t; }
//==============================================================================
INLINE float dot4(const vec4 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w; }//dot4
INLINE float dot4(const vec4 &a, const vec4 &b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }//dot4
//float dot4(const vec3 &a,const vec4 &b){return a.x*b.x+a.y*b.y+a.z*b.z;}//dot3
//==============================================================================
INLINE vec3 cross4(const vec4 &a, const vec4 &b) { return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }//6mul:3sub:3set
//==============================================================================
//==============================================================================
INLINE vec4 norm4(const vec4 &a) {// is it usable??????
	const float len = sqrt(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
	if (len > EPSILON) {
		const float ilen = 1.0f / (len);
		return vec4(a.x*ilen, a.y*ilen, a.z*ilen, a.w*ilen);
		//vec4 ret;ret.set(a.x*ilen, a.y*ilen, a.z*ilen, a.w*ilen);return ret;
	}
	return a;
}
//==============================================================================
//float t=sqrtf(F[0]*F[0]+F[1]*F[1]+F[2]*F[2]);\
//if(t<=0)t=1;t=1/t;\
//F[0]*=t;F[1]*=t;F[2]*=t;F[3]*=t;
INLINE vec4 norm3(const vec4 &a) {//aka normPlane()
	const float len = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	if (len > EPSILON) {
		const float ilen = 1.0f / len;
		return vec4(a.x*ilen, a.y*ilen, a.z*ilen, a.w*ilen);
		//vec4 ret;ret.set(a.x*ilen, a.y*ilen, a.z*ilen, a.w*ilen);return ret;
	}
	return a;
}
//==============================================================================
INLINE vec4 computePlane(const vec3 &v1, const vec3 &v2, const vec3 &v3) {// used in sprite.h
	return vec4(v1.y*(v2.z - v3.z) + v2.y*(v3.z - v1.z) + v3.y*(v1.z - v2.z),
		v1.z*(v2.x - v3.x) + v2.z*(v3.x - v1.x) + v3.z*(v1.x - v2.x),
		v1.x*(v2.y - v3.y) + v2.x*(v3.y - v1.y) + v3.x*(v1.y - v2.y),
		-(v1.x*(v2.y*v3.z - v3.y*v2.z) + v2.x*(v3.y*v1.z - v1.y*v3.z) + v3.x*(v1.y*v2.z - v2.y*v1.z)));
//	vec4 ret;ret.set(v1.y*(v2.z - v3.z) + v2.y*(v3.z - v1.z) + v3.y*(v1.z - v2.z),
//		v1.z*(v2.x - v3.x) + v2.z*(v3.x - v1.x) + v3.z*(v1.x - v2.x),
//		v1.x*(v2.y - v3.y) + v2.x*(v3.y - v1.y) + v3.x*(v1.y - v2.y),
//		-(v1.x*(v2.y*v3.z - v3.y*v2.z) + v2.x*(v3.y*v1.z - v1.y*v3.z) + v3.x*(v1.y*v2.z - v2.y*v1.z)));
//	return ret;
}
//==============================================================================
INLINE bool isVisible(const vec4 &p, const vec3 &v) { return (p.x*v.x + p.y*v.y + p.z*v.z + p.w) > 0; }
//==============================================================================
//static INLINE vec4 calcPlane(const vec3 &N, const vec3 &A) { return vec4(N, -dot(N, A)); }
INLINE vec4 calcPlane(const vec3 &N, const vec3 &A) { vec4 ret;ret.set(N, -dot(N, A));return ret; }
INLINE float distPlane(const vec4 &P, const vec3 &V) { return dot(P, V) + P.w; }
INLINE void clipPlane(const vec4 &Plane, vec3 &point, float distance ) {//used 4?
	const float d = dot(Plane, point);
	if (d < distance)point -= vec3(Plane.v)*d;
}
//==============================================================================
INLINE vec3 intPlane(const vec3 &S, const vec3 &D, const vec3 &N, const vec3 &A) { return S + D * (dot(N, S) - dot(N, A)) / -dot(N, D); }
//INLINE vec3 vec4::intPlane(const vec3 &S,const vec3 &D)const{return vec3(S+D*(dot4(*this,S)/-dot(vec3(*this),D)));}
// bool intersectPlane(const vec3 &S, const vec3 &D,const vec3 &N, const vec3 &A, float &t){//new
// float denom = dot(N,D);if(fabs(denom)<EPSILON)return false;
// t = dot(A-S,N) / denom;
// return (t>=0);
//}
//==============================================================================
INLINE float distPlane(const vec3 &S, const vec3 &D, const vec3 &N, const vec3 &A) {
	float dist = dot(N, S) - dot(N, A);//if(dist<EPSILON)return 0;
	float len = -dot(N, D);//if(fabs(len)<EPSILON)return -len;//??
	float rez = dist / len;
	return F_NAN(rez) ? 0 : rez;//dist/len;//qnan
}
//==============================================================================
INLINE float distPlane(const vec3 &S, const vec3 &DN, const vec3 &A) { return dot(DN, S) - dot(DN, A); }
//==============================================================================
INLINE u32_t color_c(const vec4 &c) {
	return (u32_t(c.w * 255) << 24) | (u32_t(c.z * 255) << 16) | (u32_t(c.y * 255) << 8) | u32_t(c.x * 255);
}
//==============================================================================
INLINE vec4 color_a(u32_t c) {
	return vec4((c & 0x000000FF) >> 0,
		(c & 0x0000FF00) >> 8,
		(c & 0x00FF0000) >> 16,
		(c & 0xFF000000) >> 24);
//	vec4 ret;ret.set((c & 0x000000FF) >> 0,
//		(c & 0x0000FF00) >> 8,
//		(c & 0x00FF0000) >> 16,
//		(c & 0xFF000000) >> 24);
//	return ret;
}
//==============================================================================
//a = (color >> 24) & 255;
//r = (color >> 16) & 255;
//g = (color >> 8) & 255;
//b = color & 255;
INLINE vec4 color_b(u32_t c) {
	return vec4(c & u32_t(0xFF000000),
		c & u32_t(0x00FF0000),
		c & u32_t(0x0000FF00),
		c & u32_t(0x000000FF));
//	vec4 ret;ret.set(c & u32_t(0xFF000000),
//		c & u32_t(0x00FF0000),
//		c & u32_t(0x0000FF00),
//		c & u32_t(0x000000FF));
//	return ret;
}
//==============================================================================

#endif
