#ifndef __MATHS_H__
#define __MATHS_H__

#include "BaseTypes.h"
#include "Sys/DLL_API.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
INLINE void sincos(float rad_ang, float &s, float &c) {
	s = sin(rad_ang);
	c = cos(rad_ang);
}

INLINE void sincos3(const vec3 &rad_ang, vec3 &s, vec3 &c);/* {
	s.set(sin(rad_ang.x), sin(rad_ang.y), sin(rad_ang.z));
	c.set(cos(rad_ang.x), cos(rad_ang.y), cos(rad_ang.z));
}*/
#include "mat4.h"
#include "quat.h"
#include "Origin.h"

#include "Bound.h"
#include "ray.h"
#include "Sys/Profiler.h"


mat4 EulerXYZ(const vec3 &xyz);
mat4 EulerXZY(const vec3 &xyz);
mat4 EulerYXZ(const vec3 &xyz);
mat4 EulerYZX(const vec3 &xyz);
mat4 EulerZXY(const vec3 &xyz);
mat4 EulerZYX(const vec3 &xyz);
//=============================================================================
enum COLOR{//12 colors + grey,black,white	  odd(R,Y,G,C,B,M) even(RY,YG,GC,CB,BM,MR)	 (x & 1)?odd:even  0,1,2,3,4,5 -> 0,2,4,6,8,10 => ODD((x+x)%11) 
	Red=0,//R
		RedYellow,//orange 2RG
	Yellow,//RG
		YellowGreen,//R2G
	Green,//G
		GreenCyan,//2GB
	Cyan,//GB
		CyanBlue,//azure G2B
	Blue,//B
		BlueMagenta,//violet 2BR
	Magenta,//BR
		MagentaRed,//rose B2R

	Grey,
	Black,
	White
};
//=============================================================================
INLINE vec3 color(u8_t cl){//ROYGCBM
	switch(cl){
		case Red		:return vec3(1  ,0  ,0  );//Red
		case Green		:return vec3(0  ,1  ,0  );//Green
		case Blue		:return vec3(0  ,0  ,1  );//Blue
		case CyanBlue   :return vec3(0  ,0.5,1  );//CB = (C+B)/2
		case BlueMagenta:return vec3(0.5,0  ,1  );//BM = (B+M)/2
		case GreenCyan  :return vec3(0  ,1  ,0.5);//GC = (G+C)/2 
		case Grey		:return vec3(0.5,0.5,0.5);//Grey
		case MagentaRed :return vec3(1  ,0  ,0.5);//MR = (B+M)/2
		case YellowGreen:return vec3(0.5,1  ,0  );//YG = (Y+G)/2 
		case RedYellow  :return vec3(1  ,0.5,0  );//RY = (R+Y)/2 
		case Yellow		:return vec3(1  ,1  ,0  );//Yellow = R+G
		case Magenta	:return vec3(1  ,0  ,1  );//Magenta = R+B
		case Cyan		:return vec3(0  ,1  ,1  );//Cyan = G+B
		case White		:return vec3(1  ,1  ,1  );//White
		case Black		:return vec3(0  ,0  ,0  );//Black
	}
	LOG::err("color not found");
	return vec3(1,0,0);
}
//=============================================================================
INLINE vec4 color(u8_t cl,float alpha){//ROYGCBM
	return vec4(color(cl),alpha);
}
//0=(1,0,0)
//1=(0,1,0)
//2=(0,0,1)
//3=(-1,0,0)
//4=(0,-1,0)
//5=(0,0,-1)
INLINE vec3 i2cubev(u8_t i){return vec3(float(i==0?1:i==3?-1:0), float(i==1?1:i==4?-1:0), float(i==2?1:i==5?-1:0));}//i[0..6]

// 1.0f and 0.999999f -> 0.0f so 
const float packEpsilon = 0.00001f;

INLINE float RGB2Float(vec3 c){
	PROFILER(0);// PF(FUNC_NAME);// 9k 0.1ms
	const float n6 = 256.0f;
	float _a = floor(clamp(c.x,0.0f,1.0f-packEpsilon)*n6);
	float _b = floor(clamp(c.y,0.0f,1.0f-packEpsilon)*n6);
	float _c = floor(clamp(c.z,0.0f,1.0f-packEpsilon)*n6);
	return _a + _b*n6 + _c*(n6*n6);
}

INLINE vec3 Float2RGB(float cc){
	const float n6 = 256.0f;
	float _c = floor(cc/(n6*n6));
	float _b = floor((cc-(_c*(n6*n6)))/n6);
	float _a = floor(cc-_b*n6-_c*(n6*n6));
	return vec3(_a,_b,_c)/n6;
}

//INLINE u32_t RGBA2u32(vec4 rgba){
//	u32_t c = 
//	return c;
//}

DLL_API vec4 u32ToRGBA(u32_t c);//FD

INLINE float FMA_test(float x, float y, float z){
	return x * y + z;
}

INLINE bool clockwise(const vec2 &a, const vec2 &b, const vec2 &c){
	const vec2 e0(b - a), e1(c - a);
	return (e0.x*e1.y - e0.y*e1.x) < 0.0f;
}

DLL_API float SegIntersectsf(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d);
DLL_API bool SegIntersects(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d);
DLL_API bool Circle2(const vec3 &b, const vec3 &c, vec3 &center);
DLL_API vec3 Circle2_helper(const vec3 &a, const vec3 &b, const vec3 &c);
DLL_API void CircleCircleIntersection2D(vec3 c1, vec3 c2, vec2 &p1, vec2 &p2);

#endif
