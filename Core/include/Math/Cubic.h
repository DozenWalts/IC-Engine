#ifndef __CUBIC_H__
#define __CUBIC_H__

#include "Sys/DLL_API.h"
#include "Math/Maths.h"

struct DLL_API CubicSpline {// 4*12=48
	union {
		struct { vec3 A, B, C, D; };
		struct { vec3 v[4]; };
	};

	CubicSpline() {}
	CubicSpline(const vec3 &p1, const vec3 &p2, const vec3 &p3, const vec3 &p4) :A(p1), B(p2), C(p3), D(p4) {}
	void set(const vec3 &p1, const vec3 &p2, const vec3 &p3, const vec3 &p4) { A = p1, B = p2, C = p3, D = p4; }

	vec3 at(const float &t);
	vec3 at_cj(const float &t);
	vec3 at_cj_t0(const float &t);
	vec3 at_cj_t1(const float &t);
	vec3 at_cj_tan(const float &t);

	float bezierSpline(float p0, float p1, float p2, float p3, float t);
	vec3 firstder(const float &t);
	vec3 secondder(const float &t);

	float XIntercept(const vec2 *V, int degree);
	bool controlPolygonFlatEnough(const vec2 *V, int degree);
	int crossingCount(const vec2 *V, int degree);
	int findRoots(const vec2 *w, float *t, int depth = 0);
	void ToBezierForm(vec2 *w, const vec2 &P);
	float nearest_point_time(const vec2 &P);

	void cubicRoots2(double A, double B, double C, double D, double s[3]);
	int ips(const vec2 &p1, const vec2 &p2, vec2 *ip, float *t = nullptr);

	vec3 solve(const float &a, const float &b, const float &c);
	int getminmax(vec3 *mmp, bool XY = 0);

	void move_mid(vec3 newB, float t);
	void setup3parc(vec3 p1, vec3 p4, vec3 c);

	void setupCubicControls(vec3 p1, vec3 p2, vec3 p3, float t = 0.5f);
	bool setup4puv(vec3 p0, vec3 p1, vec3 p2, vec3 p3, double u = 1.0 / 3.0, double v = 2.0 / 3.0);

	void setup4p(vec3 p0, vec3 p1, vec3 p2, vec3 p3);

	void init_ffd(const u16_t NUM_STEPS = 40);
	void ffd_step();
	// usage:
	// int steps=40;
	// CubicSpline ffd(A,B,C,D);
	// ffd.init_ffd(steps);
	//
	// while(steps--){glVertex3fv(ffd.A);ffd_step()};//draw lines
	// -OR-
	// float len=0;vec3 pp;
	// while(steps--){pp=ffd.A;ffd.ffd.step();len+=len(ffd.A-pp);};//calc length
	//-----------------------------------------------------------------------------
};
#endif