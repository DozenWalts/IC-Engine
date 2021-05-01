#ifndef __VEC3_H__
#define __VEC3_H__

//#include "DLL_API.h"
//#include "Maths.h"
//#define Y_UP

#include "vec2.h"
//#include "Sys/HashTable.h"
//#include <unordered_set>
//struct DLL_API vec3{
//	union{
//		struct{float x,y,z;};
//		float v[3];
//	};
//	vec3() {}
//	vec3(const float f) :x(f), y(f), z(f) {}
//	vec3(float a, float b, float c) :x(a), y(b), z(c) {}
//	void set(const float &a, const float &b, const float &c) { x = a; y = b; z = c; }
//
//	INLINE const vec3 operator+(float f)const { return vec3(x + f, y + f, z + f); }
//	INLINE const vec3 operator+(const vec3 &a)const { return vec3(x + a.x, y + a.y, z + a.z); }
//	INLINE vec3 &operator+=(const vec3 &a) { return *this = *this + a; }
//
//	INLINE const vec3 operator*(float f)const { return vec3(x*f, y*f, z*f); }
//	INLINE const vec3 operator*(const vec3 &a)const { return vec3(x*a.x, y*a.y, z*a.z); }
//	INLINE vec3 &operator*=(float f) { return *this = *this*f; }
//
//	INLINE const vec3 operator-(float f)const { return vec3(x - f, y - f, z - f); }
//	INLINE const vec3 operator-(const vec3 &a)const { return vec3(x - a.x, y - a.y, z - a.z); }
//	INLINE const vec3 operator-()const { return vec3(-x, -y, -z); }
//	INLINE vec3 &operator-=(const vec3 &a) { return *this = *this - a; }
//
//};

//INLINE float dot(const vec3 &a, const vec3 &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }//3mul:2add:1set
//=============================================================================
struct DLL_API Face3 {
	union {
		struct { u32_t x, y, z; };
		u32_t v[3];
	};
	//-----------------------------------------------------------------------------
	INLINE Face3() :x(0), y(0), z(0) {}											//c++11 - ?no?(?
	INLINE Face3(const u32_t &a, const u32_t &b, const u32_t &c) :x(a), y(b), z(c) {}//:v{a,b,c}{}//
	INLINE Face3(const u32_t *v) :x(v[0]), y(v[1]), z(v[2]) {}
	//-----------------------------------------------------------------------------
	INLINE operator u32_t*() { return (u32_t*)&x; }
	INLINE operator const u32_t*()const { return (u32_t*)&x; }
	//-----------------------------------------------------------------------------
	INLINE void set(const u32_t &a, const u32_t &b, const u32_t &c) { x = a; y = b; z = c; }
	INLINE void set(const u32_t &a) { x = a; y = a; z = a; }
	INLINE void flip() { u32_t tv = x; x = y; y = tv; }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct vec3;//FD
struct DLL_API vec3i {
	union {
		struct { int x, y, z; };
		int v[3];
	};
	//-----------------------------------------------------------------------------
	INLINE vec3i() :x(0), y(0), z(0) {}
	INLINE vec3i(int a, int b, int c) : x(a), y(b), z(c) {}
	INLINE vec3i(int a) : x(a), y(a), z(a) {}
	INLINE vec3i(const int *v) : x(v[0]), y(v[1]), z(v[2]) {}
	INLINE vec3i(const vec3i &v) : x(v.x), y(v.y), z(v.z) {}
	//INLINE vec3i(const float *f):x(FtoI(f[0])),y(FtoI(f[1])),z(FtoI(f[2])){}
	INLINE vec3i(const vec3 &v);//FD :x(FtoI(v.x)),y(FtoI(v.y)),z(FtoI(v.z)){}
	INLINE void set(const int &a, const int &b, const int &c) { x = a; y = b; z = c; }
	INLINE void set(const int &a) { x = a; y = a; z = a; }
	//-----------------------------------------------------------------------------
	INLINE operator int*() { return (int*)&x; }
	INLINE operator const int*()const { return (int*)&x; }
	//-----------------------------------------------------------------------------
	INLINE const vec3i operator*(int f)const { return vec3i(x*f, y*f, z*f); }
	INLINE const vec3i operator/(int f)const { return vec3i(x / f, y / f, z / f); }
	INLINE const vec3i operator+(int f)const { return vec3i(x + f, y + f, z + f); }
	INLINE const vec3i operator-(int f)const { return vec3i(x - f, y - f, z - f); }
	INLINE const vec3i operator+(const vec3i &v)const { return vec3i(x + v.x, y + v.y, z + v.z); }
	INLINE const vec3i operator-(const vec3i &v)const { return vec3i(x - v.x, y - v.y, z - v.z); }
	INLINE const vec3i operator-()const { return vec3i(-x, -y, -z); }
	INLINE const vec3i operator*(const vec3i &v)const { return vec3i(x*v.x, y*v.y, z*v.z); }
	//-----------------------------------------------------------------------------
	INLINE vec3i &operator*=(int f) { return *this = *this*f; }
	INLINE vec3i &operator/=(int f) { return *this = *this / f; }
	INLINE vec3i &operator+=(const vec3i &v) { return *this = *this + v; }
	INLINE vec3i &operator-=(const vec3i &v) { return *this = *this - v; }
	INLINE vec3i &operator*=(const vec3i &v) { return *this = *this*v; }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct vec4;//FD
//=============================================================================
//struct vec3;//FD
//=============================================================================
vec3 cross(const vec3 &a, const vec3 &b);
//=============================================================================
//http://www.codersnotes.com/notes/maths-lib-2016/
//=============================================================================
struct DLL_API vec3 {
	union {//http://stackoverflow.com/questions/1972003/how-to-use-anonymous-structs-unions-in-c
		struct { float x, y, z; };
		float v[3];
	};
	//-----------------------------------------------------------------------------
	INLINE vec3() {}
	INLINE vec3(float a, float b, float c) :x(a), y(b), z(c) {}
	INLINE vec3(const float f) :x(f), y(f), z(f) {}
	INLINE vec3(const float *f) :x(f[0]), y(f[1]), z(f[2]) {}
	INLINE vec3(const vec2 &v) :x(v.x), y(v.y), z(0) {}
	INLINE vec3(const vec2 &v, const float &vz) :x(v.x), y(v.y), z(vz) {}
	//vec3(const float &vx, const vec2 &v) :x(vx), y(v.x), z(v.y) {}
	INLINE vec3(const float &vx, const float &vy) :x(vx), y(vy), z(0) {}
	INLINE vec3(const vec3i &v) :x((float)v.x), y((float)v.y), z((float)v.z) {}
	INLINE vec3(const vec4 &v);//FD
	//-----------------------------------------------------------------------------
	INLINE void set(const float &a, const float &b, const float &c) { x = a; y = b; z = c; }
	INLINE void set(const vec2 &ab, const float &c) { x = ab.x; y = ab.y; z = c; }
	INLINE void set(const float &a) { x = a; y = a; z = a; }
	INLINE vec3 inv() const{ return vec3(1.0f / x, 1.0f / y, 1.0f / z); }
	INLINE float mag()const { return x * x + y * y + z * z; }
	INLINE float len()const { return sqrt(x*x + y * y + z * z); }
	//-----------------------------------------------------------------------------
	INLINE void norm() {
		const float len = sqrt(x*x + y * y + z * z);
		if (len > EPSILON) {
			const float ilen = 1.0f / len;
			x *= ilen; y *= ilen; z *= ilen;
		}
		//return *this;
	}
	//-----------------------------------------------------------------------------
	INLINE void normal(const vec3 &a, const vec3 &b, const vec3 &c) {
		//*this=cross(b-a,c-a);
		*this = cross(c - a, b - a);
		this->norm();
	}
	//-----------------------------------------------------------------------------
	INLINE void normal(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d) {//quad
		//*this=cross(b-a,c-a)+cross(c-a,d-a);
		*this = cross(c - a, b - a) + cross(d - a, c - a);
		this->norm();
	}
	//-----------------------------------------------------------------------------
	INLINE operator float*() { return (float*)&x; }
	INLINE operator const float*()const { return (float*)&x; }
	//-----------------------------------------------------------------------------
	INLINE bool operator ==(const vec3 &a)const { return (equal(x, a.x) && equal(y, a.y) && equal(z, a.z)); }
	INLINE bool operator !=(const vec3 &a)const { return !(*this == a); }
	//-----------------------------------------------------------------------------
	INLINE const vec3 operator-(float f)const { return vec3(x - f, y - f, z - f); }
	INLINE const vec3 operator-(const vec3 &a)const { return vec3(x - a.x, y - a.y, z - a.z); }
	INLINE const vec3 operator-()const { return vec3(-x, -y, -z); }
	INLINE vec3 &operator-=(const vec3 &a) { return *this = *this - a; }
	//-----------------------------------------------------------------------------
	INLINE const vec3 operator+(float f)const { return vec3(x + f, y + f, z + f); }
	INLINE const vec3 operator+(const vec3 &a)const { return vec3(x + a.x, y + a.y, z + a.z); }
	INLINE vec3 &operator+=(const vec3 &a) { return *this = *this + a; }
	//-----------------------------------------------------------------------------
	INLINE const vec3 operator*(float f)const { return vec3(x*f, y*f, z*f); }
	INLINE const vec3 operator*(const vec3 &a)const { return vec3(x*a.x, y*a.y, z*a.z); }
	INLINE vec3 &operator*=(float f) { return *this = *this*f; }
	//INLINE vec3 &operator*=(const vec3 &v){return *this=*this*v;}
	//-----------------------------------------------------------------------------
	INLINE const vec3 operator/(float f)const { return vec3(x / f, y / f, z / f); }
	INLINE vec3 &operator/=(float f) { return *this = *this / f; }
	//-----------------------------------------------------------------------------
	//INLINE const vec3 operator=(const float f)const{return vec3(f,f,f);} pos=0.0f -> pos=NULL ???
	//INLINE vec3 &operator=(const float &f){return vec3(f,f,f);}
	//-----------------------------------------------------------------------------
	INLINE vec3 ang2dir() {
		float sp, sy, cp, cy;
		sy = sin(v[YAW] * D2R); cy = cos(v[YAW] * D2R);
		sp = sin(v[PITCH] * D2R); cp = cos(v[PITCH] * D2R);
		//sr=sin(v[ROLL ]*D2R);cr=cos(v[ROLL ]*D2R);
		return vec3(cp*cy, cp*sy, -sp);
	}
	//-----------------------------------------------------------------------------
	INLINE vec3 ang2right() {
		float sr, sp, sy, cr, cp, cy;
		sy = sin(v[YAW] * D2R); cy = cos(v[YAW] * D2R);
		sp = sin(v[PITCH] * D2R); cp = cos(v[PITCH] * D2R);
		sr = sin(v[ROLL] * D2R); cr = cos(v[ROLL] * D2R);
		return vec3(sr*sp*cy + cr * -sy, sr*sp*sy + cr * cy, sr*cp);
	}
	//-----------------------------------------------------------------------------
	INLINE vec3 ang2up() {
		float sr, sp, sy, cr, cp, cy;
		sy = sin(v[YAW] * D2R); cy = cos(v[YAW] * D2R);
		sp = sin(v[PITCH] * D2R); cp = cos(v[PITCH] * D2R);
		sr = sin(v[ROLL] * D2R); cr = cos(v[ROLL] * D2R);
		return vec3(cr*sp*cy - sr * -sy, cr*sp*sy - sr * cy, cr*cp);
	}
	//-----------------------------------------------------------------------------
	INLINE vec3 rotZ(float rad)const { return vec3(x*cos(rad) - y * sin(rad), x*sin(rad) + y * cos(rad), z); }//normal=tangent.rotZ(-HPI);
	//-----------------------------------------------------------------------------
	INLINE vec3 rotZ90()const { return vec3(-y, x, z); }
	//-----------------------------------------------------------------------------
	INLINE vec3 rotY90()const { return vec3(z, y, -x); }
	//-----------------------------------------------------------------------------
	INLINE float yaw() {//float yaw=norm(pos1-pos2).yaw();
		return atan2(z, x);//y up
	}
	//-----------------------------------------------------------------------------
	INLINE float angle()const { return atan2(-y, x); }//+HPI???
	//-----------------------------------------------------------------------------
	////https://github.com/g-truc/glm/blob/master/glm/gtx/hash.inl
	//INLINE u32_t hash() const{
	//	size_t seed = 0;
	//	//std::hash<float> hasher;
	//	//hash_combine(seed, hash32(x));
	//	//hash_combine(seed, hash32(y));
	//	//hash_combine(seed, hash32(z));
	//	return hash_bytes(this, 12);// seed; //
	//}
	//-----------------------------------------------------------------------------
};
//=============================================================================
INLINE vec3 sph2cart(const vec3 &sph) {//spherical2cartesian
	return vec3(cos(sph.y) * sin(sph.x) *sph.z,
		sin(sph.y) * sin(sph.x) *sph.z,
		cos(sph.x) *sph.z
	);
}
INLINE vec3 sph_to_car(const vec3 &sph) {//nw	 http://webcache.googleusercontent.com/search?q=cache:2Pgp_yRhnqsJ:citeseerx.ist.psu.edu/viewdoc/download%3Fdoi%3D10.1.1.50.1583%26rep%3Drep1%26type%3Dpdf+&cd=9&hl=ru&ct=clnk&gl=ru
	float	u = sph.x < 0.0f ? -vec2(sph).len() : vec2(sph).len(),
			u2 = sph.x < 0.0f ? -sph.len() : sph.len();
	return vec3(u2,
		asin(sph.y / u) / HPI,
		asin(sph.z / u2) / HPI
	);
}
INLINE vec3 cart2sph(const vec3 &cart) {//cartesian2spherical
	float p = atan2(cart.y, cart.x);
	return vec3(acos(clamp(cart.z, -1.0f, 1.0f)),//theta
		((p < 0) ? p + PI * 2 : p), // phi
		sqrt(cart.mag())//rad
	);
}
INLINE vec3 car_to_sph(const vec3 &car) {//nw
	float u = car.x, v = car.y*HPI, w = car.z*HPI;
	float a = sin(v), b = sin(w);	w = cos(w);
	return vec3(u*v*w,
		u*a*w,
		u*b
	);
}
//=============================================================================
INLINE vec3 floor3(const vec3 &v) { return vec3(floor(v.x), floor(v.y), floor(v.z)); }
INLINE vec3 fract3(const vec3 &v) { return vec3(fract(v.x), fract(v.y), fract(v.z)); }
INLINE vec2::vec2(const vec3 &v) :x(v.x), y(v.y) {}
INLINE vec3 sincos_xy0(float a) { return vec3(sin(a), cos(a), 0); }
//=============================================================================
INLINE vec3 norm(const vec3 &a) {
	const float len = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	if (len > EPSILON) {
		const float ilen = 1.0f / len;
		return vec3(a.x*ilen, a.y*ilen, a.z*ilen);
	}
	return a;//or 0.0f?
}
//=============================================================================
INLINE vec3 norm_fast(const vec3 &a) {
	const float len = Q_rsqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	//const float len = ssqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	if (len > EPSILON) {
		const float ilen = 1.0f / len;
		return vec3(a.x*ilen, a.y*ilen, a.z*ilen);
	}
	return a;//or 0.0f?
}
//=============================================================================
INLINE vec3 normRAD(const vec3 &a) { return vec3(normRAD(a.x), normRAD(a.y), normRAD(a.z)); }
//=============================================================================
INLINE vec3 normDEG(const vec3 &a) { return vec3(normDEG(a.x), normDEG(a.y), normDEG(a.z)); }
//=============================================================================
INLINE float len(const vec3 &v) {return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);}
INLINE float dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }//3mul:2add:1set
INLINE vec3 ortho_norm(const vec3 &a, const vec3 &n) { return norm(a - n * dot(a, n)); }
INLINE vec3 lerp3(const vec3 &a, const vec3 &b, const float &t) { return a + (b - a)*t; }
INLINE vec3 cross(const vec3 &a, const vec3 &b) { return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }//6mul:3sub:3set
INLINE vec3 normal(const vec3 &a, const vec3 &b, const vec3 &c) { return norm(cross(c - a, b - a)); }
INLINE vec3 normal(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d) { return norm(cross(c - a, b - a) + cross(d - a, c - a)); }//a = ((P0n -P00) + (Pnn -Pn0)) x ((Pn0 -P00) + (Pnn -P0n))   http://research.microsoft.com/en-us/um/people/cloop/niessner2015survey.pdf
INLINE vec3 reflect(const vec3 &N, const vec3 &V) { return V - N * (dot(N, V)*2.0f); }//reflect direction
extern float dot4(const vec4 &a, const vec3 &b);//FD
INLINE vec3 reflect4(const vec4 &P, const vec3 &V) { return V - vec3(P)*(dot4(P, V)*2.0f); }//reflect position
INLINE vec3 abs3(const vec3 &a) { return vec3(fabs(a.x), fabs(a.y), fabs(a.z)); }
INLINE vec3 max3(const vec3 &a, const vec3 &b) { return vec3(mmax(a.x, b.x), mmax(a.y, b.y), mmax(a.z, b.z)); }
INLINE vec3 min3(const vec3 &a, const vec3 &b) { return vec3(mmin(a.x, b.x), mmin(a.y, b.y), mmin(a.z, b.z)); }
INLINE vec3 snap3(const vec3 &a, const float &sv) { return vec3(snap(a.x, sv), snap(a.y, sv), snap(a.z, sv)); }
//=============================================================================
INLINE void swapf(float *a, float *b, u8_t n) {
	float t;
	loop0i(n)t = a[i], a[i] = b[i], b[i] = t;
}
//=============================================================================
INLINE vec3 perpendicular(const vec3 &src) {
	vec3 dst(0, 0, 0);
	if (src[0]) {
		if (src[1]) {
			if (src[2]) {
				int pos = 0;
				float minelem = fabs(src[0]);
				if (fabs(src[1]) < minelem) { pos = 1; minelem = fabs(src[1]); }
				if (fabs(src[2]) < minelem)pos = 2;
				dst[pos] = 1;
				dst[0] -= src[pos] * src[0];
				dst[1] -= src[pos] * src[1];
				dst[2] -= src[pos] * src[2];
				dst.norm();
			}
			else dst[2] = 1.0;
		}
		else dst[1] = 1.0;
	}
	else dst[0] = 1.0;
	return dst;
}
//=============================================================================
INLINE vec3 perpendicular2(const vec3 &src) {
	float min = 1.0f;
	vec3 tv, v1;
	for (int i = 0; i < 3; i++)if (min > fabs(src[i])) { min = fabs(src[i]); tv[i] = 1.0f; }
	v1 = cross(src, tv);
	return cross(v1, src);
}
//=============================================================================
INLINE vec3 orthogonal(const vec3 &v) {//Doesn’t require the input to be normalised. Doesn’t normalise the output.		 http://lolengine.net/blog/2013/09/21/picking-orthogonal-vector-combing-coconuts
	return fabs(v.x) > fabs(v.z) ? vec3(-v.y, v.x, 0.0)
		: vec3(0.0, -v.z, v.y);
}
//=============================================================================
//vec3 orthogonal(const vec3 &v){//Requires the input to be normalised. Doesn’t normalise the output.	 http://lolengine.net/blog/2013/09/21/picking-orthogonal-vector-combing-coconuts
//	float k = fract(abs(v.x) + 0.5);
//	return vec3(-v.y, v.x - k * v.z, k * v.y);
//}
//=============================================================================
INLINE void ANG2VEC_DEG_ZUP(const vec3 &a, float *f, float *r, float *u) {//to test
	float sy = sin(a[1] * D2R), cy = cos(a[1] * D2R),
		sp = sin(a[2] * D2R), cp = cos(a[2] * D2R),
		sr = sin(a[0] * D2R), cr = cos(a[0] * D2R);
	if (f) { f[0] = cp * cy;			 f[1] = cp * sy;			f[2] = -sp; }
	if (r) { r[0] = sr * sp*cy + cr * -sy;   r[1] = sr * sp*sy + cr * cy;   r[2] = sr * cp; }
	if (u) { u[0] = (cr*sp*cy + -sr * -sy); u[1] = (cr*sp*sy + -sr * cy); u[2] = cr * cp; }
}
//=============================================================================
INLINE void ANG2VEC_DEG_YUP(const vec3 &a, float *f, float *r, float *u) {//blender y-up
	float cx = cos(a[0] * D2R), sx = sin(a[0] * D2R),
		cy = cos(a[1] * D2R), sy = sin(a[1] * D2R),
		cz = cos(a[2] * D2R), sz = sin(a[2] * D2R),
		cc = cx * cz, cs = cx * sz, sc = sx * cz, ss = sx * sz;
	if (r) { r[0] = cy * cz;   r[1] = cy * sz;   r[2] = -sy; } //transposed?
	if (u) { u[0] = sy * sc - cs; u[1] = sy * ss + cc; u[2] = cy * sx; }
	if (f) { f[0] = sy * cc + ss; f[1] = sy * cs - sc; f[2] = cy * cx; }
}
//=============================================================================
//vec3 slerp2(vec3 p1, vec3 p2, float delta) {
//  float omega = acos( dot(p1, p2) );
//  float sinOmega = sin( omega );
//  vec3 n1 = sin( (1.0 - delta) * omega ) /   p1*sinOmega;	 ???
//  vec3 n2 = sin( delta * omega ) /   p2*sinOmega;???
//  return n1 + n2;
//}
//=============================================================================
INLINE vec3 slerp(const vec3 &a, const vec3 &b, float k) {//shortest slerp angle
	float dp = dot(a, b);// 0 - perpendicular 1- parallel
	//if(fabs(dp)>(1.0-EPSILON))return norm(perpendicular2(a)); ???? cross(a,viewer.pos)
	float omega = acos(dp);
	float ooo = 1.0f / sin(omega);//sin(0)==0
	if (fabs(sin(omega)) < EPSILON) ooo = 1.0f;//return vec3(0.0);
	return (a*sin((1.0f - k)*omega) + b * sin(k*omega)) * ooo;
}//  */
//=============================================================================
INLINE vec3 slerp_(vec3 start, vec3 end, float percent) {//http://blog.demofox.org/page/2/
	float d = dot(start, end);// Dot product - the cosine of the angle between 2 vectors.
	d = clamp(d, -1.0, 1.0);// Clamp it to be in the range of Acos() This may be unnecessary, but floating point precision can be a fickle mistress.
	float theta = acos(d)*percent;// Acos(dot) returns the angle between start and end, And multiplying that by percent returns the angle between start and the final result.
	vec2 RelativeVec = norm(end - start * d); // Orthonormal basis
	return ((start*cos(theta)) + (RelativeVec*sin(theta)));// The final result.
}
//=============================================================================
/*vec3 slerp( vec3 p0,  vec3 p1, float t){
			float theta = acos( dot(p0,p1) );
			vec3 s = ( (p0*sin(1.0-t)*theta) + p1*sin(t*theta) ) / sin(theta);
			return s * ( p0.len()+p1.len() ) * 0.5;
}	*/
//============================================================================= to test
INLINE vec3 OrthoNorm(vec3 normal, vec3 tangent) { return norm(cross(normal, tangent)); }//must be unit?
INLINE vec3 OrthoNorm2(vec3 normal, vec3 tangent) {//can be not unit
	norm(normal);// D3DXVec3Normalize( normal, normal );
	vec3 proj = tangent - normal * dot(tangent, normal);//   D3DXVECTOR3 proj;   D3DXVec3Scale( &proj, normal, D3DXVec3Dot( tangent, normal) );  D3DXVec3Subtract( tangent, tangent, proj );
	return norm(proj);//   D3DXVec3Normalize( tangent, tangent );
}
//=============================================================================
//get angle in degrees
INLINE float angle(float w, float len) { return atan2(w, 2 * len) * 2 * R2D; }//atan2(len(H1 - H2),2*len((H1+H2)*0.5))*2*R2D
//float angle(const vec3 &p1,const vec3 &p2){return atan2(len(cross(p1,p2)), dot(p1,p2))*R2D;}
//float signed_angle(const vec3 &q,const vec3 &w,const vec3 &dir=vec3(0,1,0)){return acos(dot(q,w))*(dot(dir,cross(q,w))<0?1:-1);}//*(dot(dir,cross(q,w))<0?1:-1);}// SIGNED ANGLE
//float angle2(const vec3 &z,const vec3 &d){return acosf( clamp( dot( z, d ), -1.0f, 1.0f ) );}
//float angler(const vec3 &p1,const vec3 &p2){return atan2(len(cross(p1,p2)), dot(p1,p2));}
	//float dota=dot(norm(proj_on_plane(UNIT_UP,cam.pos)),UNIT_DR);
	//float lena=-dot(UNIT_UP,cross(norm(proj_on_plane(UNIT_UP,cam.pos)),UNIT_DR));
	//ang[YAW]=acos(dota)*sign(lena);
	//ang[YAW]=atan2(lena, dota);
INLINE float angle(const vec3 &a, const vec3 &b, const vec3 &N) { return atan2(dot(N, cross(b, a)), dot(b, a)); }//atan2//a=norm(proj_on_plane(N,a))
INLINE float angle2(const vec3 &a, const vec3 &b, const vec3 &N) { return acos(dot(b, a)) * sign(dot(N, cross(b, a))); }//acos
//vec3 ProjectToPlane(vec3 V, vec3 PlanePoint, vec3 PlaneNormal){return (V - PlaneNormal*dot(V - PlanePoint, PlaneNormal) );}
INLINE vec3 proj_on_vec(const vec3 &N, const vec3 &delta) { return N * dot(N, delta); }
INLINE vec3 proj_on_plane(const vec3 &N, const vec3 &delta) { return delta - N * dot(N, delta); }//return delta-proj_on_vec(N,delta);} EXAMPLE:vec3 ppos=proj_on_plane(RM.F,pos-RM.T)+RM.T;//proj cam pos on edit plane
INLINE float angle_on_plane(const vec3 &trg, const vec3 &dir, const vec3 &N) { vec3 a(norm(proj_on_plane(N, trg))); return atan2(dot(N, cross(dir, a)), dot(dir, a)); }//on plane
//=============================================================================
INLINE vec2 v30v2(const vec3 &in) {//vec3 (x,0,z) to vec2(x,z)
	return in.x == 0.0 ? vec2(in.y, in.z) : in.y == 0.0 ? vec2(in.x, in.z) : vec2(in.x, in.y);
}
//=============================================================================
INLINE bool LineSide3(const vec3 &a, const vec3 &b, const vec3 &viewer, const vec3 &c) {
	vec3 N; N.normal(a, b, viewer);
	return dot(N, c) > dot(N, a);
}
//=============================================================================
//if(SameSide3(V[RTvs[0]],V[RTvs[1]],cam->pos,V[i],V[c])){skip_face=true;break;} model.h
INLINE bool SameSide3(const vec3 &a, const vec3 &b, const vec3 &viewer, const vec3 &c, const vec3 &p) {
	const vec3 N = normal(a, b, viewer);
	const float dotNa = dot(N, a);
	return dot(N, c) > dotNa == dot(N, p) > dotNa;
}
//=============================================================================
INLINE int VecTriSide(const vec3 &S, const vec3 &D, const vec3 &A, const vec3 &B, const vec3 &C) {
	vec3 N; N.normal(A, B, C);
	float d = dot(N, A);
	float dist = dot(N, S) - d;
	float len = -dot(N, D);
	float t = dist / len;
	vec3 PIP = S + D * t, f;
	f = cross(N, B - A); if (dot(PIP - A, f) > 0.0f)return 0;
	f = cross(N, C - B); if (dot(PIP - B, f) > 0.0f)return 1;
	f = cross(N, A - C); if (dot(PIP - C, f) > 0.0f)return 2;
	return -1;
}
//=============================================================================
INLINE int VecQdSide(const vec3 &S, const vec3 &D, const vec3 &A, const vec3 &B, const vec3 &C, const vec3 &E) {//ray quad sides in
	vec3 N; N.normal(A, B, C, E);
	float d = dot(N, A);
	float dist = dot(N, S) - d;
	float len = -dot(N, D);
	float t = dist / len;
	vec3 PIP = S + D * t;
	if (dot(PIP - A, cross(N, B - A)) > 0.0f)return 0;
	if (dot(PIP - B, cross(N, C - B)) > 0.0f)return 1;
	if (dot(PIP - C, cross(N, E - C)) > 0.0f)return 2;
	if (dot(PIP - E, cross(N, A - E)) > 0.0f)return 3;
	return -1;
}
//=============================================================================
INLINE void branchlessONB(const vec3 &n, vec3 &b1, vec3 &b2) {	   // OrthoNormalBasis  http://graphics.pixar.com/library/OrthonormalB/paper.pdf
	float sign = copysignf(1.0f, n.z);
	const float a = -1.0f / (sign + n.z);
	const float b = n.x * n.y * a;
	b1 = vec3(1.0f + sign * n.x * n.x * a, sign * b, -sign * n.x);
	b2 = vec3(b, sign + n.y * n.y * a, -n.y);
}
//=============================================================================
INLINE vec3i::vec3i(const vec3 &v) :x(int(v.x)), y(int(v.y)), z(int(v.z)) {}
#ifdef Y_UP
	extern DLL_API const vec3 UNIT_RT;// (1, 0, 0);
	extern DLL_API const vec3 UNIT_UP;// (0, 1, 0);
	extern DLL_API const vec3 UNIT_DR;// (0, 0, 1);
#endif

#ifdef Z_UP
	extern DLL_API const vec3 UNIT_DR;// (1, 0, 0);
	extern DLL_API const vec3 UNIT_RT;// (0, 1, 0);
	extern DLL_API const vec3 UNIT_UP;// (0, 0, 1);
#endif

extern DLL_API const vec3 vec3_zero;// (0.0f);

//=============================================================================	  https://www.opengl.org/discussion_boards/showthread.php/162035-GLSL-packing-a-normal-in-a-single-float
//#include <stdio.h>
//#include <math.h>
// 
////Helper method to emulate GLSL
//float fract(float value)
//{
//	return (float)fmod(value, 1.0f);
//}
// 
////Helper method to go from a float to packed char
//unsigned char ConvertChar(float value)
//{
//	//Scale and bias
//	value = (value + 1.0f) * 0.5f;
//	return (unsigned char)(value*255.0f);
//}
// 
////Pack 3 values into 1 float
//float PackToFloat(unsigned char x, unsigned char y, unsigned char z)
//{
//	unsigned int packedColor = (x << 16) | (y << 8) | z;
//	return (float)packedColor;
//}
// 
////UnPack 3 values from 1 float
//void UnPackFloat(float src, float &amp;r, float &amp;g, float &amp;b)
//{
//	// Unpack to the 0-255 range
//	r = floor(src/65536.0f);
//	g = floor(fmod(src, 65536.0f)/256.0f);
//	b = fmod(src, 256.0f);
// 
//	//Unpack to the -1..1 range
//	r = (r/255.0f * 2.0f) - 1.0f;
//	g = (g/255.0f * 2.0f) - 1.0f;
//	b = (b/255.0f * 2.0f) - 1.0f;
//}
// 
////Test pack/unpack 3 values
//void DoTest(float r, float g, float b)
//{
//	float outR, outG, outB;
// 
//	printf("Testing %f %f %f\n",r, g, b);
// 
//	//Pack
//	float result = PackToFloat(ConvertChar(r), ConvertChar(g), ConvertChar(b));
// 
//	//Unpack
//	UnPackFloat(result, outR, outG, outB);
// 
//	printf("Result %f %f %f\n",outR, outG, outB); 
//	printf("Diff   %f %f %f\n\n",r-outR, g-outG, b-outB); 
//}
// 
// 
//int main(int argc, char* argv[])
//{
// 
//	DoTest(1.0f,1.0f,1.0f);
//	DoTest(0.0f,0.0f,0.0f);
//	DoTest(0.5f,0.5f,0.5f);
// 
//	DoTest(-1.0f,-1.0f,-1.0f);
//	DoTest(-0.5f,-0.5f,-0.5f);
// 
//	DoTest(-0.2f,-0.3f,-0.4f);
//	DoTest(0.2f,0.3f,0.4f);
//	return 0;
//}
#endif
