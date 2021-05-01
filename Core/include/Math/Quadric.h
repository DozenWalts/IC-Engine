//=============================================================================
#include <float.h>         //ips::cubicRoots2::cube_root::approximately_zero_cubed::FLT_EPSILON_CUBED::FLT_EPSILON
const double FLT_EPSILON_CUBED = FLT_EPSILON * FLT_EPSILON * FLT_EPSILON;//ips::cubicRoots2::cube_root::approximately_zero_cubed::FLT_EPSILON_CUBED
//=============================================================================
struct QuadricSpline{// 4*12=48
	union{
		struct{vec3 A,B,C;};
		struct{vec3 v[3];};
	};
//-----------------------------------------------------------------------------
	QuadricSpline(){};
	QuadricSpline(const vec3 &p1,const vec3 &p2,const vec3 &p3):A(p1),B(p2),C(p3){};
	void set(const vec3 &p1,const vec3 &p2,const vec3 &p3){A=p1,B=p2,C=p3;};
//-----------------------------------------------------------------------------
vec3 at(const float &t){//vertex position at t
	//float tt=t*t, ttt=tt*t;
	//return A*(1-3*t+3*tt-ttt) + B*(3*t-6*tt+3*ttt) + C*(3*tt-3*ttt) + D*ttt;
	float u=1.0f-t;//b
	float tt=t*t;//aa
	float uu=u*u;//bb
	return A*(uu*u) + B*(3*uu*t) + C*(3*u*tt) + D*(tt*t);
// //return p0*(b*b*b) + p1*(3*b*b*a) + p2*(3*b*a*a) + p3*(a*a*a);
// //A*(1-t)^3 + B*3*(1-t)^2*t + C*3*(1-t)*t^2 + D*t^3;
	double Ax = x0 - 2 * x1 + x2;
	double Ay = y0 - 2 * y1 + y2;
	double Bx = 2 * (x1 - x0);
	double By = 2 * (y1 - y0);
	double Cx = x0;
	double Cy = y0;

	*x = Ax * t * t + Bx * t + Cx;
	*y = Ay * t * t + By * t + Cy;
	return a * tt + B * t + c;
};
//-----------------------------------------------------------------------------
//static void cubic_to_quadratic(const double c[8], double q[6])
//{
//	q[0] = c[0];
//	q[1] = c[1];
//	q[2] = (3 * (c[2] + c[4]) - (c[0] + c[6])) / 4;
//	q[3] = (3 * (c[3] + c[5]) - (c[1] + c[7])) / 4;
//	q[4] = c[6];
//	q[5] = c[7];
//}
};
//=============================================================================