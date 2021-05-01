#ifndef __QUAT_H__
#define __QUAT_H__
#include "Sys/DLL_API.h"
//#include "mat4.h"
//=============================================================================
//float ReciprocalSqrt( float x ) {
// long i;
// float y, r;
// y = x * 0.5f;
// i = *(long *)( &x );
// i = 0x5f3759df - ( i >> 1 );
// r = *(float *)( &i );
// r = r * ( 1.5f - r * r * y );
// return r;
//} 
struct Origin;//FD for QUAT*ORIGIN
struct vec3;//FD
//struct mat4;//FD

void sincos(float rad_ang, float &s, float &c);//FD
void sincos3(const vec3&, vec3&, vec3&);//FD
//=============================================================================
struct DLL_API quat{//16 a rotation 2*acos(w) about the axis (x,y,z).
	union{
		struct{float x,y,z,w;};
		float v[4];
	};
//-----------------------------------------------------------------------------
	INLINE quat():x(0.0f),y(0.0f),z(0.0f),w(1.0f){}
	INLINE quat(const float &a,const float &b,const float &c,const float &d):x(a),y(b),z(c),w(d){}
	//quat(const float *f):x(f[0]),y(f[1]),z(f[2]),w(f[3]){}//??
	//quat(const vec3 &p):x(p.x),y(p.y),z(p.z),w(0){}
	INLINE quat(const vec3 &p,const float f):x(p.x),y(p.y),z(p.z),w(f){}
	//quat(const vec4 &p):x(p.x),y(p.y),z(p.z),w(p.w){} norm(vec4|quat) - ambigous; use quat a=vec4(x);
	INLINE quat(const mat4 &m){*this=m;}//!!!!!!!!!!!!!!!!!! else quat q(mat4 m)->fail but compilable >:(
//-----------------------------------------------------------------------------
	INLINE void set(const float &a,const float &b,const float &c,const float &d){x=a;y=b;z=c;w=d;}
	INLINE void set(const vec4 &d){x=d.x;y=d.y;z=d.z;w=d.w;}
	//INLINE void set(const float &a){x=a;y=a;z=a;w=a;}???
//-----------------------------------------------------------------------------
	INLINE float mag()const{return x*x + y*y + z*z + w*w;}
	INLINE float len()const{return sqrt(x*x + y*y + z*z + w*w);}
//-----------------------------------------------------------------------------
INLINE quat &norm(){
	const float len = sqrt(x*x + y*y + z*z + w*w);
	if(len>EPSILON){
		const float ilen = 1.0f/len;
		x*=ilen;y*=ilen;z*=ilen;w*=ilen;
	}else{x=0;y=0;z=0;w=1;}//!
	return *this;
}
//-----------------------------------------------------------------------------
INLINE operator float*(){return (float*)&x;}
INLINE operator const float*()const{return (float*)&x;}
//-----------------------------------------------------------------------------
INLINE bool operator==(const quat &a)const{return (equal(x,a.x) && equal(y,a.y) && equal(z,a.z) && equal(w,a.w));}
INLINE bool operator!=(const quat &a)const{return !(*this==a);}
//-----------------------------------------------------------------------------
//INLINE const quat operator-(float f)const{return quat(x-f,y-f,z-f,w-f);}//w-f??
INLINE const quat operator-()const{return quat(-x,-y,-z,-w);}
INLINE const quat operator-(const quat &q)const{return quat(x-q.x,y-q.y,z-q.z,w-q.w);}
INLINE quat &operator-=(const quat &q){return *this=*this-q;}
//-----------------------------------------------------------------------------
INLINE const quat operator+(const quat &q)const{return quat(x+q.x,y+q.y,z+q.z,w+q.w);}
INLINE quat &operator+=(const quat &q){return *this=*this+q;}
//-----------------------------------------------------------------------------
INLINE const quat operator*(const float &q)const{return quat(x*q,y*q,z*q,w*q);}
INLINE quat &operator*=(const float &f){return *this=*this*f;}
INLINE quat operator*(const quat &q)const{
	return quat(w*q.x+x*q.w+y*q.z-z*q.y,
				w*q.y-x*q.z+y*q.w+z*q.x,
				w*q.z+x*q.y-y*q.x+z*q.w,
				w*q.w-x*q.x-y*q.y-z*q.z);}
//-----------------------------------------------------------------------------  
INLINE Origin operator*(const Origin &o);//FD for QUAT*ORIGIN
//-----------------------------------------------------------------------------  
INLINE vec3 operator*(const vec3 &vec)const{//http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	//vec3 xyz(x,y,z);//v=v+cross(2r,cross(r,v)+w*v);
	//return vec3(vec + cross(xyz,cross(xyz,vec)+vec*w)*2.0f);
	return vec3(vec + cross(vec3(v) * 2, cross(vec3(v), vec) + vec * w));
}
//-----------------------------------------------------------------------------
INLINE quat &operator*=(const quat &q){return *this=*this*q;}
//-----------------------------------------------------------------------------
//INLINE quat &operator =(const float &f){return quat(f,f,f,0);}
//INLINE quat &operator =(const int &f){return quat(f,f,f,0);}
//-----------------------------------------------------------------------------
INLINE quat conjugate()const{return quat(-x, -y, -z, w);}
//-----------------------------------------------------------------------------
INLINE vec3 rotate_vector_by_quaternion(const vec3& v){//http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	vec3 u(x,y,z);// Extract the vector part of the quaternion
	return vec3( u*dot(u, v)*2.0f + v*(w*w-dot(u, u)) + cross(u, v)*(2.0f*w));
}
//-----------------------------------------------------------------------------
INLINE vec3 Rotate(const vec3 &vec)const{
	vec3 yzw(x,y,z);//  6	 6	 3	3 = 12+6 = 18mul
	return vec3(vec + cross(yzw,cross(yzw,vec)+vec*w)*2.0f);
}// */
//----------------------------------------------------------------------------- fast version of transform vector by quaternion
INLINE vec3 operator^(const vec3 &q)const{//28mul
	return vec3( quat(w*q.x+y*q.z-z*q.y, w*q.y+z*q.x-x*q.z, w*q.z+x*q.y-y*q.x, -x*q.x-y*q.y-z*q.z) * quat(-x, -y, -z, w));
}//totest */
//-----------------------------------------------------------------------------
INLINE quat(float angle, const vec3 &axis){//set
	const float ha = angle * 0.5f;
	const float s = (float)sin(ha);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	w = cos(ha);
}
//-----------------------------------------------------------------------------
INLINE void from_angleAxsis(float angle, const vec3 &axis){//set	is it work?
	const float ha = angle * 0.5f;
	const float s = (float)sin(ha);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	w = cos(ha);
	//float s=sin(angle*0.5f),c=cos(angle*0.5f);
	////Math::sincosf(angle * DEG2RAD * 0.5f,s,c);
	//float ilength = 1.0f/sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	//x = axis.x * ilength * s;
	//y = axis.y * ilength * s;
	//z = axis.z * ilength * s;
	//w = c; 
}
//-----------------------------------------------------------------------------
INLINE void angleAxis(float &angle, vec3 &axis)const{//get   // to test http://math.stackexchange.com/questions/291110/numerically-stable-extraction-of-axis-angle-from-unit-quaternion
	const float len = x*x + y*y + z*z;
	if(len>EPSILONSQ){
		angle = 2.0f * (float)acos(w);
		const float ilen = 1.0f / (float)pow(len, 0.5f);
		axis.x = x * ilen;
		axis.y = y * ilen;
		axis.z = z * ilen;
	}else{
		angle = 0.0f;
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
	}
}
//-----------------------------------------------------------------------------
quat RotateX(float rad_ang){
	float sina, cosa;
	sincos(0.5f * rad_ang, sina, cosa);
	return quat(sina, 0.0f, 0.0f, cosa);
}
quat RotateY(float rad_ang){
	float sina, cosa;
	sincos(0.5f * rad_ang, sina, cosa);
	return quat(0.0f, sina, 0.0f, cosa);
}
quat RotateZ(float rad_ang){
	float sina, cosa;
	sincos(0.5f * rad_ang, sina, cosa);
	return quat(0.0f, 0.0f, sina, cosa);
}
//-----------------------------------------------------------------------------
//float Angle(const vec3 &axis)const{
//	vec3 v0=*this^axis;
//	vec3 v1=norm(v0+axis);
//	float angle = dot(axis,v1);
//	if(fabsf(angle) > EPSILON){
//		quat q0;q0.set(-cross(v0,axis,v1));
//		q0.w = angle;
//		quat q1=(q0*(*this));q1.norm();
//		q1.get(v0,angle);
//	} else {
//		get(v0,angle);
//	}
//	if(dot(v0,axis) < 0.0f) angle = -angle;
//	return angle;
//} 
//-----------------------------------------------------------------------------
INLINE vec3 toEuler(const vec3 *old_euler = nullptr)const {
	mat4 rm = *this;
	return rm.toEuler(old_euler);
}
//https://github.com/kmammou/v-hacd/blob/master/src/VHACD_Lib/src/FloatMath.inl fm_quatToEuler
//-----------------------------------------------------------------------------
void fromEuler(const vec3 &a, RotationOrder order = RotationOrder::Default) {
	float c1 = cos(a.x / 2);
	float c2 = cos(a.y / 2);
	float c3 = cos(a.z / 2);

	float s1 = sin(a.x / 2);
	float s2 = sin(a.y / 2);
	float s3 = sin(a.z / 2);

	if (order == RotationOrder::XYZ) {
		x = s1 * c2 * c3 + c1 * s2 * s3;
		y = c1 * s2 * c3 - s1 * c2 * s3;
		z = c1 * c2 * s3 + s1 * s2 * c3;
		w = c1 * c2 * c3 - s1 * s2 * s3;
	} else if (order == RotationOrder::YXZ) {
		x = s1 * c2 * c3 + c1 * s2 * s3;
		y = c1 * s2 * c3 - s1 * c2 * s3;
		z = c1 * c2 * s3 - s1 * s2 * c3;
		w = c1 * c2 * c3 + s1 * s2 * s3;
	} else if (order == RotationOrder::ZXY) {
		x = s1 * c2 * c3 - c1 * s2 * s3;
		y = c1 * s2 * c3 + s1 * c2 * s3;
		z = c1 * c2 * s3 + s1 * s2 * c3;
		w = c1 * c2 * c3 - s1 * s2 * s3;
	} else if (order == RotationOrder::ZYX) {
		x = s1 * c2 * c3 - c1 * s2 * s3;
		y = c1 * s2 * c3 + s1 * c2 * s3;
		z = c1 * c2 * s3 - s1 * s2 * c3;
		w = c1 * c2 * c3 + s1 * s2 * s3;
	} else if (order == RotationOrder::YZX) {
		x = s1 * c2 * c3 + c1 * s2 * s3;
		y = c1 * s2 * c3 + s1 * c2 * s3;
		z = c1 * c2 * s3 - s1 * s2 * c3;
		w = c1 * c2 * c3 - s1 * s2 * s3;
	} else if (order == RotationOrder::XZY) {
		x = s1 * c2 * c3 - c1 * s2 * s3;
		y = c1 * s2 * c3 - s1 * c2 * s3;
		z = c1 * c2 * s3 + s1 * s2 * c3;
		w = c1 * c2 * c3 + s1 * s2 * s3;
	}
}
//-----------------------------------------------------------------------------
INLINE void operator=(const mat4 &m){// scale not handled !!!! 
	float fourX = m[0*4+0] - m[1*4+1] - m[2*4+2]; //glm quat_cast
	float fourY = m[1*4+1] - m[0*4+0] - m[2*4+2];
	float fourZ = m[2*4+2] - m[0*4+0] - m[1*4+1];
	float fourBiggest = m[0*4+0] + m[1*4+1] + m[2*4+2];
	int idx = 0;
	if(fourX > fourBiggest){fourBiggest = fourX;idx = 1;}
	if(fourY > fourBiggest){fourBiggest = fourY;idx = 2;}
	if(fourZ > fourBiggest){fourBiggest = fourZ;idx = 3;}
	float biggestVal = sqrt(fourBiggest + 1.0f)*0.5f;
	float mult = 0.25f/biggestVal;
	switch(idx){
		case 0:	w = biggestVal; 
				x = (m[1*4+2] - m[2*4+1])*mult;
				y = (m[2*4+0] - m[0*4+2])*mult;
				z = (m[0*4+1] - m[1*4+0])*mult;break;
		case 1:	w = (m[1*4+2] - m[2*4+1])*mult;
				x = biggestVal;
				y = (m[0*4+1] + m[1*4+0])*mult;
				z = (m[2*4+0] + m[0*4+2])*mult;break;
		case 2:	w = (m[2*4+0] - m[0*4+2])*mult;
				x = (m[0*4+1] + m[1*4+0])*mult;
				y = biggestVal;
				z = (m[1*4+2] + m[2*4+1])*mult;break;
		case 3:	w = (m[0*4+1] - m[1*4+0])*mult;
				x = (m[2*4+0] + m[0*4+2])*mult;
				y = (m[1*4+2] + m[2*4+1])*mult;
				z = biggestVal;break;
	}// */
}
//-----------------------------------------------------------------------------
void fromMat4(const mat4 &m) {
	// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)
	float m11 = m[0], m12 = m[4], m13 = m[8];
	float m21 = m[1], m22 = m[5], m23 = m[9];
	float m31 = m[2], m32 = m[6], m33 = m[10];
	
	float trace = m11 + m22 + m33;
	float s;

	if (trace > 0.0f) {
		s = 0.5f / sqrt(trace + 1.0f);
		w = 0.25f / s;
		x = (m32 - m23) * s;
		y = (m13 - m31) * s;
		z = (m21 - m12) * s;
	} else if (m11 > m22 && m11 > m33) {
		s = 2.0f * sqrt(1.0f + m11 - m22 - m33);
		w = (m32 - m23) / s;
		x = 0.25f * s;
		y = (m12 + m21) / s;
		z = (m13 + m31) / s;
	} else if (m22 > m33) {
		s = 2.0f * sqrt(1.0f + m22 - m11 - m33);
		w = (m13 - m31) / s;
		x = (m12 + m21) / s;
		y = 0.25f * s;
		z = (m23 + m32) / s;
	} else {
		s = 2.0f * sqrt(1.0f + m33 - m11 - m22);
		w = (m21 - m12) / s;
		x = (m13 + m31) / s;
		y = (m23 + m32) / s;
		z = 0.25f * s;
	}
}
//-----------------------------------------------------------------------------
#ifdef Y_UP
	INLINE vec3 right()const{return vec3(1-2*(y*y+z*z),  2*(x*y+w*z),  2*(x*z-w*y));}
	INLINE vec3	up()const{return vec3(  2*(x*y-w*z),1-2*(x*x+z*z),  2*(y*z+w*x));}
	INLINE vec3   dir()const{return vec3(  2*(x*z+w*y),  2*(y*z-w*x),1-2*(x*x+y*y));}
	//http://www.flipcode.com/documents/matrfaq.html#Q54
#endif
#ifdef Z_UP
	INLINE vec3   dir()const{return vec3(1-2*(y*y+z*z),  2*(x*y+w*z),  2*(x*z-w*y));}
	INLINE vec3 right()const{return vec3(  2*(x*y-w*z),1-2*(x*x+z*z),  2*(y*z+w*x));}
	INLINE vec3	up()const{return vec3(  2*(x*z+w*y),  2*(y*z-w*x),1-2*(x*x+y*y));}
#endif
//-----------------------------------------------------------------------------
//INLINE vec3 T()const{return vec3(1-2*(y*y+z*z),  2*(x*y+w*z),  2*(x*z-w*y));}
//INLINE vec3 B()const{return vec3(  2*(x*y-w*z),1-2*(x*x+z*z),  2*(y*z+w*x));}
//INLINE vec3 N()const{return vec3(  2*(x*z+w*y),  2*(y*z-w*x),1-2*(x*x+y*y));}
//void lookat1(const vec3 &eye,const vec3 &at,const vec3 &up){//not work for Zup?
// mat4 LAM(1);
// LAM.lookat(eye,at,up);
// *this=LAM;
//}
//-----------------------------------------------------------------------------
INLINE void turn_to(const vec3 &dir){//iterative
	// s is a scaling factor to ensure quat remains unit length
	float const s = sqrt( (1.f-w*w) / (dir.x*dir.x+dir.y*dir.y+dir.z*dir.z) );
	x = x*s;
	y = y*s;
	z = z*s;
}
//-----------------------------------------------------------------------------
//quat inv()const{const float n = len();return quat(-x/n, -y/n, -z/n, w/n);}
INLINE quat inv()const{return quat(-x, -y, -z, w);}//unit
//quat.invert = function(out, a) {
//	var a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3],
//		dot = a0*a0 + a1*a1 + a2*a2 + a3*a3,
//		invDot = dot ? 1.0/dot : 0;
//	// TODO: Would be faster to return [0,0,0,0] immediately if dot == 0
//	out[0] = -a0*invDot;
//	out[1] = -a1*invDot;
//	out[2] = -a2*invDot;
//	out[3] = a3*invDot;
//	return out;
//}
//void inv(quat &r)const{const float n = len();r = quat(-x/n, -y/n, -z/n, w/n);}
//-----------------------------------------------------------------------------
//quat.calculateW = function (out, a) {	  https://github.com/flowtsohg/mdx-m3-viewer/blob/v4/external/gl-matrix/quat.js
//	var x = a[0], y = a[1], z = a[2];
//	out[0] = x;
//	out[1] = y;
//	out[2] = z;
//	out[3] = Math.sqrt(Math.abs(1.0 - x * x - y * y - z * z));
//	return out;
//}
//-----------------------------------------------------------------------------
};
//============================================================================= end quat
#ifdef Y_UP
INLINE quat lookat(const vec3 &at_eye,const vec3 &up){
	vec3 F = norm(at_eye),U(up);
	float UdotF=dot(U,F);
	if(UdotF> (1.0-EPSILON)){U= UNIT_DR;}//if F==U
	if(UdotF<-(1.0-EPSILON)){U=-UNIT_DR;}//if F==-U
	vec3 R = norm(cross(U,F)); U = norm(cross(F,R));
	return mat4(R,U,F);//M2Q
} 
#endif
#ifdef Z_UP
INLINE quat lookat(const vec3 &at_eye,const vec3 &up){//z_up
	vec3 F = norm(at_eye),U(up);
	float UdotF=dot(U,F);
	if(UdotF> (1.0-EPSILON)){U=-UNIT_RT;}//if F==U
	if(UdotF<-(1.0-EPSILON)){U= UNIT_RT;}//if F==-U
	vec3 R = norm(cross(U,F)); U = norm(cross(F,R));
	return mat4(F,R,U);//M2Q
}
#endif
//=============================================================================
INLINE quat lookat(const vec3 &eye,const vec3 &at,const vec3 &up){return lookat(at-eye,up);}
INLINE quat lookat(const vec3 &at_eye){return lookat(at_eye,UNIT_UP);}
//quat lookrotf(const vec3 &at_eye){return lookat2(at_eye,UNIT_UP);}//inv sign
/*quat look_at(const vec3 &source,const vec3 &dest,const vec3 &up){//to test from http://stackoverflow.com/questions/12435671/quaternion-lookat-function nw
	const float d = dot(source, dest);
	if(fabs(d - (-1.0f)) < EPSILON){return quat(up,PI);} // vector a and b point exactly in the opposite direction, 
	if(fabs(d - (1.0f)) < EPSILON){return quat(0,0,0,1);}// vector a and b point exactly in the same direction
	return quat(acos(d), norm(cross(source, dest)));
}// */
//=============================================================================
INLINE quat norm(const quat &a){
	const float len = sqrt(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
	if(len>EPSILON){return quat(a.x/len,a.y/len,a.z/len,a.w/len);}
	return quat(0,0,0,1);//.norm();//?
} 
//============================================================================= rotation between two vectors
//quat dq=fromtwovectors(rot.dir(),trot.dir());
//rot=norm(rot*dq);
INLINE  quat fromtwovectors(vec3 u, vec3 v){// to test http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors
	return norm(quat(cross(u, v),1.0f + dot(u, v)));//xyz=cross w=1+dot
}
INLINE  quat fromtwovectors2(vec3 u, vec3 v){//not so good
	float m = sqrt(2.f + 2.f * dot(u, v));
	return quat(cross(u, v) * (1.f / m), m*0.5f);////vec3 w = cross(u, v) * (1.f / m); return quat(0.5f * m, w.x, w.y, w.z);
}
//=============================================================================
//=============================================================================
INLINE  mat4 ModelView(const quat &q,const vec3 &t){
	//return mat4(q, t);//.inv();

	vec3 r(q.right()),u(q.up()),f(q.dir());
#ifdef Y_UP
	r=-r;
	f=-f;
	return mat4(	r.x,	u.x,	f.x,		0,
					r.y,	u.y,	f.y,		0,
					r.z,	u.z,	f.z,		0,
				-dot(t,r),-dot(t,u),-dot(t,f),	1);
#endif
#ifdef Z_UP
	mat4 ZU(vec3(0,0,-1),vec3(-1,0,0),vec3(0,1,0));//optimize?
	//mat4 RM=q,TM(0.0,-t);
	//return ZU*RM.inv()*TM;
	return ZU*mat4(	f.x,	r.x,	u.x,		0,
					f.y,	r.y,	u.y,		0,
					f.z,	r.z,	u.z,		0,
				-dot(t,f),-dot(t,r),-dot(t,u),	1);
#endif
}
//=============================================================================
INLINE quat slerp(const quat &a, const quat &b, float t){//assert(t>=0);assert(t<=1);	worse than bottom slerp collinear(right==left)
	float flip = 1.0f;
	float cosine = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
	if(cosine<0){cosine = -cosine;flip = -1.0f;}//flip broken? 
	if((1.0f-cosine)<EPSILON)return a * (1.0f-t) + b * (t*flip); 
	float theta = (float)acos(cosine); 
	float sine = (float)sin(theta); 
	float beta = (float)sin((1.0f-t)*theta) / sine; 
	float alpha = (float)sin(t*theta) / sine * flip; 
	return a * beta + b * alpha; 
}
//=============================================================================
INLINE quat slerp2(const quat &q1,const quat &q,const float &interp){ //better thn above slerp collinear(right!=left)
	int i;
	float a=0,b=0;
	quat ret;
	quat q2(q);
	for(i=0;i<4;i++){
		a+=(q1[i]-q2[i])*(q1[i]-q2[i]);
		b+=(q1[i]+q2[i])*(q1[i]+q2[i]);
	}
	if(a>b){q2.inv();}
	float cosom=q1[0]*q2[0]+q1[1]*q2[1]+q1[2]*q2[2]+q1[3]*q2[3];
	double sclq1,sclq2;
	if((1.0f+cosom)>EPSILON){
		if((1.0f-cosom)>EPSILON){//0.00000001
			double omega=acos(cosom);
			double sinom=sin(omega);
			sclq1=sin((1.0f-interp)*omega)/sinom;
			sclq2=sin(interp*omega)/sinom;
		}else{
			sclq1=1.0-interp;
			sclq2=interp;
		}
		for(i=0;i<4;i++){ret.v[i]=(float)(sclq1*q1[i]+sclq2*q2[i]);}
	}else{
		ret.x=-q1[1];//??but works
		ret.y= q1[0];
		ret.z=-q1[3];
		ret.w= q1[2];
		sclq1=sin((1.0f-interp)*0.5*PI);
		sclq2=sin(interp*0.5*PI);
		for(i=0;i<3;i++){ret.v[i]=(float)(sclq1*q1[i]+sclq2*ret.v[i]);}
	}
	return ret;
}
//=============================================================================
INLINE vec3 decomposeRotationXYZ(mat4 transform){
	vec3 r = 0.0f;
	if (transform.m[0*4+2] < 1.0f){
		if (transform.m[0*4+2] > -1.0f){
			r.x = atan2(-transform.m[1*4+2], transform.m[2*4+2]);
			r.y = asin(transform.m[0*4+2]);
			r.z = atan2(-transform.m[0*4+1], transform.m[0*4+0]);
		}else{
			r.x = -atan2(transform.m[1*4+0], transform.m[1*4+1]);
			r.y = -HPI;
		}
	}else{
		r.x = atan2(transform.m[1*4+0], transform.m[1*4+1]);
		r.y = HPI;
	}
	return r;
}
//=============================================================================
union DLL_API Dquat{
	//union{
		struct {quat q;vec4 t;};
		struct {float x,y,z,w, ix,iy,iz,iw;};
		float v[8];
	//};
//-----------------------------------------------------------------------------
INLINE Dquat():x(0),y(0),z(0),w(1), ix(0),iy(0),iz(0),iw(1){}
INLINE Dquat(float x,float y,float z,float w, float ix,float iy,float iz,float iw):x(x),y(y),z(z),w(w), ix(ix),iy(iy),iz(iz),iw(iw){}
INLINE Dquat(float x):x(x),y(x),z(x),w(x), ix(x),iy(x),iz(x),iw(x){}
//-----------------------------------------------------------------------------
//INLINE Dquat(const vec3 &a){q.Rot(a);t.set(0,0,0,1);}
//INLINE Dquat(const vec3 &a,const vec3 &p){q.Rot(a);Trans(p);}
//INLINE Dquat(const Dquat &q1,const Dquat &q2,const float time){slerp(q1.q,q2.q,time);}
//-----------------------------------------------------------------------------
INLINE const Dquat operator*(const float &a)const{return Dquat(x*a,y*a,z*a,w*a, ix*a,iy*a,iz*a,iw*a);}
INLINE const Dquat operator+(const Dquat &a)const{return Dquat(x+a.x,y+a.y,z+a.z,w+a.w, ix+a.ix,iy+a.iy,iz+a.iz,iw+a.iw);}
INLINE const Dquat operator-(const Dquat &a)const{return Dquat(x-a.x,y-a.y,z-a.z,w-a.w, ix-a.ix,iy-a.iy,iz-a.iz,iw-a.iw);}
INLINE Dquat &operator+=(const Dquat &a){return *this=*this+a;}
INLINE Dquat &operator-=(const Dquat &a){return *this=*this-a;}
//-----------------------------------------------------------------------------
//INLINE void Trans(const vec3 &p){//translation for dquat
// v[4] = 0.5f * ( p[0]*w + p[1]*z - p[2]*y ) ; //5
// v[5] = 0.5f * (-p[0]*z + p[1]*w + p[2]*x ) ; //6
// v[6] = 0.5f * ( p[0]*y - p[1]*x + p[2]*w ) ; //7
// v[7] =-0.5f * ( p[0]*x + p[1]*y + p[2]*z ) ; //4
//}
//-----------------------------------------------------------------------------
INLINE void operator=(const mat4 &m){
	float trace=m[0]+m[5]+m[10];
	if(trace>0.0f){
		float s=sqrt(trace+1.0f);
		v[3]=0.5f*s;
		s=0.5f/s;
		v[0]=(m[6] - m[9])*s;
		v[1]=(m[8] - m[2])*s;
		v[2]=(m[1] - m[4])*s;
	}else{
		static int next[3]={1,2,0};
		int i=0;
		if(m[5]>m[0])i=1;
		if(m[10]>m[4*i+i])i=2;
		int j=next[i];//(i+1)%3;
		int k=next[j];//(j+1)%3;
		float s=sqrt(m[4*i+i] - m[4*j+j] - m[4*k+k] + 1.0f);
		v[i]=0.5f*s;
		if(s!=0)s=0.5f/s;
		v[3]=(m[4*j+k] - m[4*k+j])*s;
		v[j]=(m[4*i+j] + m[4*j+i])*s;
		v[k]=(m[4*i+k] + m[4*k+i])*s;
	}
	v[4] = 0.5f * ( m[12]*w + m[13]*z - m[14]*y ) ; //5
	v[5] = 0.5f * (-m[12]*z + m[13]*w + m[14]*x ) ; //6
	v[6] = 0.5f * ( m[12]*y - m[13]*x + m[14]*w ) ; //7
	v[7] = -0.5f * (m[12]*x + m[13]*y + m[14]*z ) ; //4
}
//-----------------------------------------------------------------------------
INLINE void norm(){
	float L=x*x+y*y+z*z+w*w;
	if(fabs(L)<0.000001f){
		x=y=z=0.0f;
		w=1.0f;
		return;// 1.0f;
	}
	L=1.0f/sqrt(L);
	for(int i=0;i<8;i++)v[i]*=L;
}
//-----------------------------------------------------------------------------
INLINE vec3 operator*(const vec3 &vec)const{
	vec3 xyz(x,y,z);
	vec3 ixyz(ix,iy,iz);
	return vec3(vec + cross(xyz,cross(xyz,vec)+vec*w)*2.0f + (ixyz*w-xyz*iw+cross(xyz,ixyz))*2.0f);
} 
//-----------------------------------------------------------------------------
INLINE vec3 Rotate(const vec3 &vec)const{
	vec3 yzw(x,y,z);
	return vec3(vec + cross(yzw,cross(yzw,vec)+vec*w)*2.0f);//14mul's
} 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};
//=============================================================================
INLINE float dotDQ(const Dquat &a,const Dquat &b){return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;}
INLINE float dotQ(const quat &a,const quat &b){return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;}
//=============================================================================
extern DLL_API const quat quat_identity;
#endif
