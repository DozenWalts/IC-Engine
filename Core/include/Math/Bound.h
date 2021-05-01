#ifndef __BOUND_H__
#define __BOUND_H__

//inline bool inBBOX(float px, float py, float mnx, float mny, float mxx, float mxy){ return px >= mnx && px <= mxx && py >= mny && py <= mxy; };//ino
//inline bool inBBOX(const vec2 &p, const vec2 &mn, const vec2 &mx){ return p.x >= mn.x && p.x <= mx.x && p.y >= mn.y && p.y <= mx.y; };//ino2d
//inline bool inBBOX(const vec3 &p, const vec3 &mn, const vec3 &mx){ return p.x >= mn.x && p.x <= mx.x && p.y >= mn.y && p.y <= mx.y && p.z >= mn.z && p.z <= mx.z; };//ino3d
#include "Sys/DLL_API.h"
#include "Math/Maths.h"
//#include "vec2.h"
//#include "vec3.h"
//#include "mat4.h"
//#include "Origin.h"

//https://github.com/juj/MathGeoLib/blob/master/src/Geometry/AABB.cpp
struct DLL_API BBOX{
	union{
		struct{ vec3 mn, mx; };
		struct{ float v[6]; };
	};
	BBOX();
	BBOX(const vec3 &n, const vec3 &x);
	BBOX(const BBOX &box);
	//BBOX(const vec3 &n):mn(n),mx(n){}
	void init(float fmn = F32_MAX, float fmx = F32_MIN);
	void set(float w, float h);
	void set(const vec3 &iv);
	void add(const BBOX &bb,const Origin &org);
	void add(const BBOX &bb,const mat4 &mat);
	INLINE void add3(const vec3 &vec);
	INLINE void add2(const vec2 &vec);
	//sphere=(mx+mn)*0.5f;
	//sphere.w=len(mx-sphere);
	vec3 center()const;
	float rad()const;
	vec4 sphere()const;
	
	INLINE vec3 A(bool fore = false)const;//left up
	INLINE vec3 B(bool fore = false)const;//right up
	INLINE vec3 C(bool fore = false)const;//right down
	INLINE vec3 D(bool fore = false)const;//left down
	INLINE vec3 V(int i)const;

	bool in2d(const vec2 &p)const;// inBBOX
	bool in3d(const vec3 &p)const;

	BBOX operator*(const mat4 &RM)const;
	BBOX operator*(const Origin &O)const;
	void print(const char *tag);
	void draw(const mat4 &rm, bool solid = false)const;
	void drawSolid(const mat4 &rm)const;
	INLINE bool isValid()const;
	//bool intersect(const CBBOX &b){
	//  return !(mn.x > b.mx.x || 
	//           mx.x < b.mn.x || 
	//           mx.y > b.mn.y ||
	//           mn.y < b.mx.y);
	//}}
};
extern bool operator==(const BBOX &a, const BBOX &b);
//extern DLL_API const BBOX BBOX_EMPTY_NODE;// (-0.05f, 0.05f);
extern DLL_API const BBOX BBOX_INVERSE;// (inf, -inf)
#endif