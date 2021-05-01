#ifndef __RAY_H__
#define __RAY_H__
//=============================================================================
//#include "Math/Bound.h"
#include "Sys/DLL_API.h"
#include "vec3.h"
#include "mat4.h"
#include "Origin.h"
struct BBOX;//FD //#include "Bound.h"
//=============================================================================
struct DLL_API Ray{
	vec3 p,n,cn;//pos,normal,collision_normal
	float len;//ray length
	u32_t obj_id;// collided object id
	u32_t flags;//=CW|CCW|any|has_collision|?
	enum FLG{
		COLLIDED=1,
		CW=2,
		CCW=4,
		ANY=8
	};
//-----------------------------------------------------------------------------
	Ray();
	Ray(const vec3 &pos, const vec3 &normal);
	Ray(const vec3 &pos, const vec3 &normal, const float &nlen);
//-----------------------------------------------------------------------------
	void set(const vec3 &pos, const vec3 &dir, const float &length);
	void set(const vec3 &pos, const vec3 &dir);
	void normalize();
//-----------------------------------------------------------------------------
	INLINE vec3 at(const float &t)const;
	INLINE vec3 at()const;
//-----------------------------------------------------------------------------
	INLINE float ip_dist(const vec3 &N, const vec3 &A)const;//plane intersection point
	INLINE vec3  ip(const vec3 &N, const vec3 &A)const;//plane intersection distance
	INLINE float ip_dist(const vec4 &P)const; //plane intersection point
	INLINE vec3  ip(const vec4 &P)const; // plane intersection distance
	INLINE vec3  ip(const Ray &b)const;
	INLINE float ip_dist(const Ray &b)const;
//-----------------------------------------------------------------------------
	Ray operator*(const mat4 &M)const;//ray rez(M*p,M.Rotate(n*len));rez.normalize();return rez;}//ray R=ray*Mat; fix - saved len
	Ray operator*(const Origin &M)const;//ray R=ray*Mat;
//-----------------------------------------------------------------------------
	bool plane(const mat4 &m);
	bool plane(const Origin &org);
	bool plane(const vec3 &PN, const vec3 &PP);
	bool tri(const vec3 &A, const vec3 &B, const vec3 &C, bool back_face_cull = true);
	bool tri(const vec3 &A, const vec3 &B, const vec3 &C, const vec3 &N, bool back_face_cull = true);
//-----------------------------------------------------------------------------
//ray-quad http://people.cs.kuleuven.be/~ares.lagae/publications/LD05ERQIT/LD05ERQIT.pdf
	bool quad(const vec3 &A, const vec3 &B, const vec3 &C, const vec3 &D, bool back_face_cull = true);
//-----------------------------------------------------------------------------
	float ip(const BBOX &b)const;
 //float DistanceToLine(Ray ray, Vec3 point) { return Vector3.Cross(ray.direction, point - ray.origin).magnitude;}
//-----------------------------------------------------------------------------
	INLINE float distance(const vec3 &pt);
	INLINE vec3 closest(const vec3 &v, bool normlz = true);
	INLINE float closest_dist(const vec3 &v); // -normalize n ? ?
//-----------------------------------------------------------------------------
	INLINE float angle(const vec3 &v)const;//-1..1  - normalize n??
//-----------------------------------------------------------------------------
	INLINE float PlaneDist(const vec4 &P)const;//dot(vec4(N,-dot(N,A)),p)/-dot(N,n);
	INLINE float PlaneDist(const vec3 &N, const vec3 &A)const;
	INLINE vec4 Plane();//construct plane
//INLINE int PlaneSide(const vec3f &v){return (dot(n,v)>dot(n,p))?1:-1;}//?? plane dist
//-----------------------------------------------------------------------------
};
//=============================================================================
#endif
