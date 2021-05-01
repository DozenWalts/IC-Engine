#ifndef __MAT4_H__
#define __MAT4_H__
 //=============================================================================
struct quat;//FD
//#include "BaseTypes.h"
#include "vec4.h"
enum RotationOrder {
	XYZ = 0,// P*y*R "roll broken shooter"
	XZY,// P*r*Y "unusable_1?"
	YXZ,// Y*p*R "shooter"
	YZX,// Y*r*P "unusable_2?"
	ZXY,// R*p*Y "aircraft_1?"
	ZYX,// R*y*P "aircraft_2?"
	ZXZ,
	XZX,
	aircraft = ZYX,
	shooter = YXZ,
	Default = XYZ,// YXZ,// ZXY,
	treejs_default = XYZ
};

//#include "quat.h"
//=============================================================================
struct DLL_API mat4 {//64
	union {
#ifdef Y_UP
		struct { vec4 R, U, F, T; };//  vec4(4)*float(4)=byte(16*4=64)=u512_t
#endif
#ifdef Z_UP
		struct { vec4 F, R, U, T; };
#endif
		//GCC member 'R' with constructor not allowed in anonymous aggregate
		float m[16];
		struct {
			float m00, m10, m20, m30;
			float m01, m11, m21, m31;
			float m02, m12, m22, m32;
			float m03, m13, m23, m33;
		};
	};
	//-----------------------------------------------------------------------------
	//vec4 &R(){ return *(vec4*)&(m+0);}
	//vec4 &U(){ return *(vec4*)&(m+4);}
	//vec4 &F(){ return *(vec4*)&(m+8);}
	//vec4 &T(){ return *(vec4*)&(m+12);}

	//const vec4 &cR()const{ return *(vec4*)&(m+0);}
	//const vec4 &cU()const{ return *(vec4*)&(m+4);}
	//const vec4 &cF()const{ return *(vec4*)&(m+8);}
	//const vec4 &cT()const{ return *(vec4*)&(m+12);}
	//-----------------------------------------------------------------------------
	INLINE mat4() {}
	//-----------------------------------------------------------------------------
	INLINE mat4(const float &s) {
		m[0] = s; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = s; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = s; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}
	//-----------------------------------------------------------------------------
	INLINE mat4(float t1, float t2, float t3, float t4, float t5, float t6, float t7, float t8, float t9, float t10, float t11, float t12, float t13, float t14, float t15, float t16) {
		m[0] = t1; m[1] = t2; m[2] = t3; m[3] = t4;
		m[4] = t5; m[5] = t6; m[6] = t7; m[7] = t8;
		m[8] = t9; m[9] = t10; m[10] = t11; m[11] = t12;
		m[12] = t13; m[13] = t14; m[14] = t15; m[15] = t16;
	}
	//-----------------------------------------------------------------------------
	INLINE mat4(const vec4 &a, const vec4 &b, const vec4 &c, const vec4 &d) {//transposed???
		m[0] = a.x; m[1] = a.y; m[2] = a.z; m[3] = 0;
		m[4] = b.x; m[5] = b.y; m[6] = b.z; m[7] = 0;
		m[8] = c.x; m[9] = c.y; m[10] = c.z; m[11] = 0;
		m[12] = d.x; m[13] = d.y; m[14] = d.z; m[15] = 1;
	}
	//-----------------------------------------------------------------------------
	INLINE mat4(const vec3 &a, const vec3 &b, const vec3 &c) {//transposed???
		m[0] = a.x; m[1] = a.y; m[2] = a.z; m[3] = 0;
		m[4] = b.x; m[5] = b.y; m[6] = b.z; m[7] = 0;
		m[8] = c.x; m[9] = c.y; m[10] = c.z; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}
	//-----------------------------------------------------------------------------
	INLINE mat4(const float *d) {
		m[0] = d[0]; m[1] = d[1]; m[2] = d[2]; m[3] = d[3];
		m[4] = d[4]; m[5] = d[5]; m[6] = d[6]; m[7] = d[7];
		m[8] = d[8]; m[9] = d[9]; m[10] = d[10]; m[11] = d[11];
		m[12] = d[12]; m[13] = d[13]; m[14] = d[14]; m[15] = d[15];
	}
	//-----------------------------------------------------------------------------
	INLINE mat4(const quat &q) { *this = q; T.set(0.0f, 1.0f); }
	INLINE mat4(const quat &q, const vec3 &p) { (*this) = q; T = p; T.w = 1; }
	INLINE mat4(const quat &q, const vec3 &p, const vec3 &s) { (*this) = q; T = p; T.w = 1; set_scale(s); }//m[0]*=s.x;m[5]*=s.y;m[10]*=s.z;}	  ;mat4 SM(1.0f);SM.setDiag(s);(*this)*=SM;
	INLINE mat4(const vec3 &a, const vec3 &t) { RT(a, t); }
	//-----------------------------------------------------------------------------
	INLINE vec3 operator*(const vec3 &v)const {
		vec3 ret;
		ret.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
		ret.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
		ret.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE vec4 operator*(const vec4 &v)const {
		vec4 ret;
		ret[0] = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w;
		ret[1] = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w;
		ret[2] = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
		ret[3] = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE operator float*() { return (float*)&m[0]; }
	INLINE operator const float*()const { return (float*)&m[0]; }
	//-----------------------------------------------------------------------------
	INLINE mat4 operator*(const mat4 &t)const {
		//mat4 ret;
		//ret[ 0] = m[0]*t[ 0] + m[4]*t[ 1] + m[ 8]*t[ 2] + m[12]*t[ 3];
		//ret[ 1] = m[1]*t[ 0] + m[5]*t[ 1] + m[ 9]*t[ 2] + m[13]*t[ 3];
		//ret[ 2] = m[2]*t[ 0] + m[6]*t[ 1] + m[10]*t[ 2] + m[14]*t[ 3];
		//ret[ 3] = m[3]*t[ 0] + m[7]*t[ 1] + m[11]*t[ 2] + m[15]*t[ 3];
		//ret[ 4] = m[0]*t[ 4] + m[4]*t[ 5] + m[ 8]*t[ 6] + m[12]*t[ 7];
		//ret[ 5] = m[1]*t[ 4] + m[5]*t[ 5] + m[ 9]*t[ 6] + m[13]*t[ 7];
		//ret[ 6] = m[2]*t[ 4] + m[6]*t[ 5] + m[10]*t[ 6] + m[14]*t[ 7];
		//ret[ 7] = m[3]*t[ 4] + m[7]*t[ 5] + m[11]*t[ 6] + m[15]*t[ 7];
		//ret[ 8] = m[0]*t[ 8] + m[4]*t[ 9] + m[ 8]*t[10] + m[12]*t[11];
		//ret[ 9] = m[1]*t[ 8] + m[5]*t[ 9] + m[ 9]*t[10] + m[13]*t[11];
		//ret[10] = m[2]*t[ 8] + m[6]*t[ 9] + m[10]*t[10] + m[14]*t[11];
		//ret[11] = m[3]*t[ 8] + m[7]*t[ 9] + m[11]*t[10] + m[15]*t[11];
		//ret[12] = m[0]*t[12] + m[4]*t[13] + m[ 8]*t[14] + m[12]*t[15];
		//ret[13] = m[1]*t[12] + m[5]*t[13] + m[ 9]*t[14] + m[13]*t[15];
		//ret[14] = m[2]*t[12] + m[6]*t[13] + m[10]*t[14] + m[14]*t[15];
		//ret[15] = m[3]*t[12] + m[7]*t[13] + m[11]*t[14] + m[15]*t[15];
		mat4 ret;
		ret[0] = m[0] * t[0] + m[4] * t[1] + m[8] * t[2];
		ret[1] = m[1] * t[0] + m[5] * t[1] + m[9] * t[2];
		ret[2] = m[2] * t[0] + m[6] * t[1] + m[10] * t[2]; ret[3] = 0;
		ret[4] = m[0] * t[4] + m[4] * t[5] + m[8] * t[6];
		ret[5] = m[1] * t[4] + m[5] * t[5] + m[9] * t[6];
		ret[6] = m[2] * t[4] + m[6] * t[5] + m[10] * t[6]; ret[7] = 0;
		ret[8] = m[0] * t[8] + m[4] * t[9] + m[8] * t[10];
		ret[9] = m[1] * t[8] + m[5] * t[9] + m[9] * t[10];
		ret[10] = m[2] * t[8] + m[6] * t[9] + m[10] * t[10]; ret[11] = 0;
		ret[12] = m[0] * t[12] + m[4] * t[13] + m[8] * t[14] + m[12];
		ret[13] = m[1] * t[12] + m[5] * t[13] + m[9] * t[14] + m[13];
		ret[14] = m[2] * t[12] + m[6] * t[13] + m[10] * t[14] + m[14]; ret[15] = 1;
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE mat4 &operator*=(const mat4 &m) { return *this = *this*m; }
	//-----------------------------------------------------------------------------
	INLINE mat4 mul4(const mat4 &t)const {
		mat4 ret;
		ret[0] = m[0] * t[0] + m[4] * t[1] + m[8] * t[2] + m[12] * t[3];
		ret[1] = m[1] * t[0] + m[5] * t[1] + m[9] * t[2] + m[13] * t[3];
		ret[2] = m[2] * t[0] + m[6] * t[1] + m[10] * t[2] + m[14] * t[3];
		ret[3] = m[3] * t[0] + m[7] * t[1] + m[11] * t[2] + m[15] * t[3];
		ret[4] = m[0] * t[4] + m[4] * t[5] + m[8] * t[6] + m[12] * t[7];
		ret[5] = m[1] * t[4] + m[5] * t[5] + m[9] * t[6] + m[13] * t[7];
		ret[6] = m[2] * t[4] + m[6] * t[5] + m[10] * t[6] + m[14] * t[7];
		ret[7] = m[3] * t[4] + m[7] * t[5] + m[11] * t[6] + m[15] * t[7];
		ret[8] = m[0] * t[8] + m[4] * t[9] + m[8] * t[10] + m[12] * t[11];
		ret[9] = m[1] * t[8] + m[5] * t[9] + m[9] * t[10] + m[13] * t[11];
		ret[10] = m[2] * t[8] + m[6] * t[9] + m[10] * t[10] + m[14] * t[11];
		ret[11] = m[3] * t[8] + m[7] * t[9] + m[11] * t[10] + m[15] * t[11];
		ret[12] = m[0] * t[12] + m[4] * t[13] + m[8] * t[14] + m[12] * t[15];
		ret[13] = m[1] * t[12] + m[5] * t[13] + m[9] * t[14] + m[13] * t[15];
		ret[14] = m[2] * t[12] + m[6] * t[13] + m[10] * t[14] + m[14] * t[15];
		ret[15] = m[3] * t[12] + m[7] * t[13] + m[11] * t[14] + m[15] * t[15];
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE void identity() {
		m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}
	//-----------------------------------------------------------------------------
	INLINE void Comp(const vec3 &A, const vec3 &B, const vec3 &C) {//transposed???
		m[0] = A[0]; m[1] = A[1]; m[2] = A[2]; m[3] = 0;
		m[4] = B[0]; m[5] = B[1]; m[6] = B[2]; m[7] = 0;
		m[8] = C[0]; m[9] = C[1]; m[10] = C[2]; m[11] = 0;
	}
	//-----------------------------------------------------------------------------
	INLINE void Comp(const vec3 &A, const vec3 &B, const vec3 &C, const vec3 &D) {//transposed???
		m[0] = A[0]; m[1] = A[1]; m[2] = A[2]; m[3] = 0;
		m[4] = B[0]; m[5] = B[1]; m[6] = B[2]; m[7] = 0;
		m[8] = C[0]; m[9] = C[1]; m[10] = C[2]; m[11] = 0;
		m[12] = D[0]; m[13] = D[1]; m[14] = D[2]; m[15] = 1;
	}
	//-----------------------------------------------------------------------------
	INLINE vec3 Rotate(const vec3 &v)const {//9mul
		vec3 ret;
		ret.x = m[0] * v.x + m[4] * v.y + m[8] * v.z;
		ret.y = m[1] * v.x + m[5] * v.y + m[9] * v.z;
		ret.z = m[2] * v.x + m[6] * v.y + m[10] * v.z;
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE vec3 IRotate(const vec3 &v)const {
		vec3 ret;
		ret.x = m[0] * v.x + m[1] * v.y + m[2] * v.z;
		ret.y = m[4] * v.x + m[5] * v.y + m[6] * v.z;
		ret.z = m[8] * v.x + m[9] * v.y + m[10] * v.z;
		return ret;
	}
	//-----------------------------------------------------------------------------
	INLINE void RT(const quat &q, const vec3 &t) {
		*this = q;//rot_glm(a);
		m[3] = m[7] = m[11] = 0.0f;
		T = t;
		m[15] = 1.0f;
	}
	//-----------------------------------------------------------------------------
	INLINE void RT(const vec3 &a, const vec3 &t) {//matrix=(YAW*PITCH)*ROLL+trans
		fromEuler(a);
		m[3] = m[7] = m[11] = 0.0f;
		T = t;
		m[15] = 1.0f;//m[12]=t[0];m[13]=t[1];m[14]=t[2];
	}
	//-----------------------------------------------------------------------------
	INLINE void RTS(const vec3 &a, const vec3 &t, const vec3 &s) {
		fromEuler(a);
		//mat4 SM(1.0f);
		//(*this)*=SM;
		R *= s.x;
		U *= s.y;
		F *= s.z;
		T.set(t, 1.0f);
	}
	//-----------------------------------------------------------------------------
	INLINE void RTS(const quat &q, const vec3 &t, const vec3 &s) {
		*this = q;//rot_glm(a);
		//mat4 SM(1.0f);
		//(*this)*=SM;
		R *= s.x;
		U *= s.y;
		F *= s.z;
		T.set(t, 1.0f);
	}
	//-----------------------------------------------------------------------------
	INLINE void M2RT(vec3 &Ang, vec3 &Pos) {
		Ang = toEuler();
		Pos = T;
	}
	//-----------------------------------------------------------------------------
	INLINE void M2RTS(vec3 &a, vec3 &t, vec3 &s)const {
		a = toEuler();
		//s.set(R.len(),U.len(),F.len());
		s = get_scale();
		t = T;
	}
	//-----------------------------------------------------------------------------
	INLINE void M2RTS(quat &a, vec3 &t, vec3 &s);//FDconst{
	//-----------------------------------------------------------------------------
	//http://www.iri.upc.edu/files/scidoc/2083-A-Survey-on-the-Computation-of-Quaternions-from-Rotation-Matrices.pdf
	vec3 toEuler(const vec3 *old_euler = nullptr, int order = RotationOrder::Default) const{
		return toEulerDays();
		// assumes the upper 3x3 of m is a pure rotation matrix (unscaled)
		vec3 euler(0.0f);

		float m11 = m[0], m12 = m[4], m13 = m[8];
		float m21 = m[1], m22 = m[5], m23 = m[9];
		float m31 = m[2], m32 = m[6], m33 = m[10];

		if (order == RotationOrder::XYZ) {
			euler.y = asin(clamp(m13, -1.0f, 1.0f));
			if (fabs(m13) < 0.9999999f) {
				euler.x = atan2(-m23, m33);
				euler.z = atan2(-m12, m11);
			} else {
				euler.x = atan2(m32, m22);
			}
		} else if (order == RotationOrder::YXZ) {
			euler.x = asin(-clamp(m23, -1.0f, 1.0f));//atan2( U.z, F.z); //m32, m33);//
			if (fabs(m23) < 0.9999999f) {
				euler.y = atan2(m13, m33);
				euler.z = atan2(m21, m22);
			} else {
				euler.y = atan2(-m31, m11);
			}
			if (old_euler) {// 	//https://www.mecademic.com/resources/Euler-angles/Euler-angles?
				vec3 difa = vec3(fabs(RadAngleDiff(euler.x, (*old_euler).x)), fabs(RadAngleDiff(euler.y, (*old_euler).y)), fabs(RadAngleDiff(euler.z, (*old_euler).z)));
				if(((difa.x > PI*0.9f) + (difa.y > PI*0.9f) + (difa.z > PI*0.9f)) > 1) {
					//LOG::msg("ang [%f %f %f] -> [%f %f %f]", euler.x*R2D, euler.y*R2D, euler.z*R2D, (*old_euler).x*R2D, (*old_euler).y*R2D, (*old_euler).z*R2D); DEBUG_BREAK
					euler.x = HPI + (HPI - euler.x);
					euler.y += PI;
					euler.z += PI;
				}
			}
		} else if (order == RotationOrder::ZXY) {
			euler.x = asin(clamp(m32, -1.0f, 1.0f));
			if (fabs(m32) < 0.9999999f) {
				euler.y = atan2(-m31, m33);
				euler.z = atan2(-m12, m22);
			} else {
				euler.z = atan2(m21, m11);
			}
		} else if (order == RotationOrder::ZYX) {
			euler.y = asin(-clamp(m31, -1.0f, 1.0f));
			if (fabs(m31) < 0.9999999f) {
				euler.x = atan2(m32, m33);
				euler.z = atan2(m21, m11);
			} else {
				euler.z = atan2(-m12, m22);
			}
		} else if (order == RotationOrder::YZX) {
			euler.z = asin(clamp(m21, -1.0f, 1.0f));
			if (fabs(m21) < 0.9999999f) {
				euler.x = atan2(-m23, m22);
				euler.y = atan2(-m31, m11);
			} else {
				euler.y = atan2(m13, m33);
			}
		} else if (order == RotationOrder::XZY) {
			euler.z = asin(-clamp(m12, -1.0f, 1.0f));
			if (fabs(m12) < 0.9999999f) {
				euler.x = atan2(m32, m22);
				euler.y = atan2(m13, m11);
			} else {
				euler.x = atan2(-m23, m33);
			}
		} else {
			LOG::warn("mat4: toEuler() given unsupported order");
		}
		return euler;
	}
	//-----------------------------------------------------------------------------
	//https://pdfs.semanticscholar.org/6681/37fa4b875d890f446e689eea1e334bcf6bf6.pdf
	vec3 toEulerDays() const{
		float c = sqrt(operator()(0, 0)*operator()(0, 0) + operator()(1, 0)*operator()(1, 0));
		float a = atan2(operator()(2, 1), operator()(2, 2));
		float b = atan2(-operator()(2, 0), c);
		float g = atan2(sin(a)*operator()(0, 2) - cos(a)*operator()(0, 1), cos(a)*operator()(1, 1) - sin(a)*operator()(1, 2));
		return vec3(-a, -b, -g);
	}
	INLINE float &operator()(int i, int j){
		// assert(i>=0 && i<4);
		// assert(j>=0 && j<4);
		return m[4 * i + j];
	}
	INLINE float &M(int i, int j) {
		// assert(i>=0 && i<4);
		// assert(j>=0 && j<4);
		return m[4 * i + j];
	}
	INLINE float operator()(int i, int j) const{
		// assert(i>=0 && i<4);
		// assert(j>=0 && j<4);
		return m[4 * i + j];
	}
	INLINE vec4 col(int c)const{
		if (c < 0 || c>3)return vec4(0, 0, 0, 1);
		return vec4(m[0 + c], m[4 + c], m[4 * 2 + c], m[4 * 3 + c]);
	}
/*/// @brief Return the Euler angles composing the given rotation matrix.
/// @details Optional axes arguments describe in what order elementary rotations
/// are applied. Note that in our convention, XYZ means Rz * Ry * Rx.
/// Because we are using rows rather than columns to represent the
/// local axes of a coordinate frame, the interpretation from a local
/// reference point of view is to first rotate about the x axis, then
/// about the newly rotated y axis, and finally by the new local z axis.
/// From a fixed reference point of view, the interpretation is to
/// rotate about the stationary world z, y, and x axes respectively.
///
/// Irrespective of the Euler angle convention, in the case of distinct
/// axes, eulerAngles() returns the x, y, and z angles in the corresponding
/// x, y, z components of the returned Vec3. For the XZX convention, the
/// left X value is returned in Vec3.x, and the right X value in Vec3.y.
/// For the ZXZ convention the left Z value is returned in Vec3.z and
/// the right Z value in Vec3.y
///
/// Examples of reconstructing r from its Euler angle decomposition
///
/// v = eulerAngles(r, ZYX_ROTATION);
/// rx.setToRotation(Vec3d(1,0,0), v[0]);
/// ry.setToRotation(Vec3d(0,1,0), v[1]);
/// rz.setToRotation(Vec3d(0,0,1), v[2]);
/// r = rx * ry * rz;
///
/// v = eulerAngles(r, ZXZ_ROTATION);
/// rz1.setToRotation(Vec3d(0,0,1), v[2]);
/// rx.setToRotation (Vec3d(1,0,0), v[0]);
/// rz2.setToRotation(Vec3d(0,0,1), v[1]);
/// r = rz2 * rx * rz1;
///
/// v = eulerAngles(r, XZX_ROTATION);
/// rx1.setToRotation (Vec3d(1,0,0), v[0]);
/// rx2.setToRotation (Vec3d(1,0,0), v[1]);
/// rz.setToRotation  (Vec3d(0,0,1), v[2]);
/// r = rx2 * rz * rx1;
//*/
vec3 toEulerVDB(RotationOrder rotationOrder = RotationOrder::Default){
    float phi, theta, psi;

    switch(rotationOrder)
    {
		case RotationOrder::XYZ://XYZ_ROTATION:

			if (isApproxEqual(operator()(2,0), 1.0f)) {
				theta = TAU;
				phi = (0.5 * atan2(operator()(1,2), operator()(1,1)));
				psi = phi;
			} else if (isApproxEqual(operator()(2,0), (-1.0))) {
				theta = -TAU;
				phi = (0.5 * atan2(operator()(1,2), operator()(1,1)));
				psi = -phi;
			} else {
				psi = (atan2(-operator()(1,0),operator()(0,0)));
				phi = (atan2(-operator()(2,1),operator()(2,2)));
				theta = (atan2(operator()(2,0), sqrt( operator()(2,1)*operator()(2,1) + operator()(2,2)*operator()(2,2))));
			}
			return vec3(phi, theta, psi);

		case RotationOrder::ZXY://ZXY_ROTATION:

			if (isApproxEqual(operator()(1,2), (1.0))) {
				theta = (TAU);
				phi = (0.5 * atan2(operator()(0,1), operator()(0,0)));
				psi = phi;
			} else if (isApproxEqual(operator()(1,2), (-1.0))) {
				theta = (-PI/2);
				phi = (0.5 * atan2(operator()(0,1),operator()(2,1)));
				psi = -phi;
			} else {
				psi = (atan2(-operator()(0,2), operator()(2,2)));
				phi = (atan2(-operator()(1,0), operator()(1,1)));
				theta = (atan2(operator()(1,2), sqrt(operator()(0,2) * operator()(0,2) + operator()(2,2) * operator()(2,2))));
			}
			return vec3(theta, psi, phi);

		case RotationOrder::YZX://YZX_ROTATION:

			if (isApproxEqual(operator()(0,1), (1.0))) {
				theta = (TAU);
				phi = (0.5 * atan2(operator()(2,0), operator()(2,2)));
				psi = phi;
			} else if (isApproxEqual(operator()(0,1), (-1.0))) {
				theta = (-PI/2);
				phi = (0.5 * atan2(operator()(2,0), operator()(1,0)));
				psi = -phi;
			} else {
				psi = (atan2(-operator()(2,1), operator()(1,1)));
				phi = (atan2(-operator()(0,2), operator()(0,0)));
				theta = (atan2(operator()(0,1), sqrt(operator()(0,0) * operator()(0,0) + operator()(0,2) * operator()(0,2))));
			}
			return vec3(psi, phi, theta);

		case RotationOrder::XZX://XZX_ROTATION:

			if (isApproxEqual(operator()(0,0), (1.0))) {
				theta = (0.0);
				phi = (0.5 * atan2(operator()(1,2), operator()(1,1)));
				psi = phi;
			} else if (isApproxEqual(operator()(0,0), (-1.0))) {
				theta = (PI);
				psi = (0.5 * atan2(operator()(2,1), -operator()(1,1)));
				phi = - psi;
			} else {
				psi = (atan2(operator()(2,0), -operator()(1,0)));
				phi = (atan2(operator()(0,2), operator()(0,1)));
				theta = (atan2(sqrt(operator()(0,1) * operator()(0,1) + operator()(0,2) * operator()(0,2)), operator()(0,0)));
			}
			return vec3(phi, psi, theta);

		case RotationOrder::ZXZ://ZXZ_ROTATION:

			if (isApproxEqual(operator()(2,2), (1.0))) {
				theta = (0.0);
				phi = (0.5 * atan2(operator()(0,1), operator()(0,0)));
				psi = phi;
			} else if (isApproxEqual(operator()(2,2), (-1.0))) {
				theta = (PI);
				phi = (0.5 * atan2(operator()(0,1), operator()(0,0)));
				psi = -phi;
			} else {
				psi = (atan2(operator()(0,2), operator()(1,2)));
				phi = (atan2(operator()(2,0), -operator()(2,1)));
				theta = (atan2(sqrt(operator()(0,2) * operator()(0,2) + operator()(1,2) * operator()(1,2)), operator()(2,2)));
			}
			return vec3(theta, psi, phi);

		case RotationOrder::YXZ://YXZ_ROTATION:

			if (isApproxEqual(operator()(2,1), (1.0))) {
				theta = (-TAU);
				phi = (0.5 * atan2(-operator()(1,0), operator()(0,0)));
				psi = phi;
			} else if (isApproxEqual(operator()(2,1), (-1.0))) {
				theta = (TAU);
				phi = (0.5 * atan2(operator()(1,0), operator()(0,0)));
				psi = -phi;
			} else {
				psi = (atan2(operator()(0,1), operator()(1,1)));
				phi = (atan2(operator()(2,0), operator()(2,2)));
				theta = (atan2(-operator()(2,1), sqrt(operator()(0,1) * operator()(0,1) + operator()(1,1) * operator()(1,1))));
			}
			return vec3(theta, phi, psi);

		case RotationOrder::ZYX://ZYX_ROTATION:

			if (isApproxEqual(operator()(0,2), (1.0))) {
				theta = (-TAU);
				phi = (0.5 * atan2(-operator()(1,0), operator()(1,1)));
				psi = phi;
			} else if (isApproxEqual(operator()(0,2), (-1.0))) {
				theta = (TAU);
				phi = (0.5 * atan2(operator()(2,1), operator()(2,0)));
				psi = -phi;
			} else {
				psi = (atan2(operator()(1,2), operator()(2,2)));
				phi = (atan2(operator()(0,1), operator()(0,0)));
				theta = (atan2(-operator()(0,2), sqrt(operator()(0,1) * operator()(0,1) + operator()(0,0) * operator()(0,0))));
			}
			return vec3(psi, theta, phi);

		case RotationOrder::XZY://XZY_ROTATION:

			if (isApproxEqual(operator()(1,0), (-1.0))) {
				theta = (TAU);
				psi = (0.5 * atan2(operator()(2,1), operator()(2,2)));
				phi = -psi;
			} else if (isApproxEqual(operator()(1,0), (1.0))) {
				theta = (-TAU);
				psi = (0.5 * atan2(- operator()(2,1), operator()(2,2)));
				phi = psi;
			} else {
				psi = (atan2(operator()(2,0), operator()(0,0)));
				phi = (atan2(operator()(1,2), operator()(1,1)));
				theta = (atan2(- operator()(1,0), sqrt(operator()(1,1) * operator()(1,1) + operator()(1,2) * operator()(1,2))));
			}
			return vec3(phi, psi, theta);
    }

    LOG::err("Euler extraction sequence not implemented");
}
/*	mat4 RM(1);
	//RM.RPW_2_Mat(100,-90,-13); F old
	//RM.RPW_2_Mat(180, -170, -13); F all
	RM.fromEuler(vec3(-100.627935, -50.536531, -13.661434)*D2R,RotationOrder::XYZ);
	RM.print("_");
	vec3 r;
	RM.ToRPW(r);
	LOG::msg("----------------------------------r %f %f %f",r.x,r.y,r.z);
	r = RM.toEulerVDB()*R2D;
	LOG::msg("----------------------------------v %f %f %f", r.x, r.y, r.z);
	r = RM.toEulerDays()*R2D;
	LOG::msg("----------------------------------d %f %f %f", r.x, r.y, r.z);
*/
/*// @brief Return a rotation matrix that maps @a v1 onto @a v2
/// about the cross product of @a v1 and @a v2.
template<class MatType>
MatType
rotation(
	const Vec3<typename MatType::value_type>& _v1,
	const Vec3<typename MatType::value_type>& _v2,
	typename MatType::value_type eps=1.0e-8)
{
	typedef typename MatType::value_type T;
	Vec3<T> v1(_v1);
	Vec3<T> v2(_v2);

	// Check if v1 and v2 are unit length
	if (!isApproxEqual(1.0, v1.dot(v1), eps)) {
		v1.normalize();
	}
	if (!isApproxEqual(1.0, v2.dot(v2), eps)) {
		v2.normalize();
	}

	Vec3<T> cross;
	cross.cross(v1, v2);

	if (isApproxEqual(cross[0], 0.0, eps) &&
		isApproxEqual(cross[1], 0.0, eps) &&
		isApproxEqual(cross[2], 0.0, eps)) {


		// Given two unit vectors v1 and v2 that are nearly parallel, build a
		// rotation matrix that maps v1 onto v2. First find which principal axis
		// p is closest to perpendicular to v1. Find a reflection that exchanges
		// v1 and p, and find a reflection that exchanges p2 and v2. The desired
		// rotation matrix is the composition of these two reflections. See the
		// paper "Efficiently Building a Matrix to Rotate One Vector to
		// Another" by Tomas Moller and John Hughes in Journal of Graphics
		// Tools Vol 4, No 4 for details.

		Vec3<T> u, v, p(0.0, 0.0, 0.0);

		double x = Abs(v1[0]);
		double y = Abs(v1[1]);
		double z = Abs(v1[2]);

		if (x < y) {
			if (z < x) {
				p[2] = 1;
			} else {
				p[0] = 1;
			}
		} else {
			if (z < y) {
				p[2] = 1;
			} else {
				p[1] = 1;
			}
		}
		u = p - v1;
		v = p - v2;

		double udot = u.dot(u);
		double vdot = v.dot(v);

		double a = -2 / udot;
		double b = -2 / vdot;
		double c = 4 * u.dot(v) / (udot * vdot);

		MatType result;
		result.setIdentity();

		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++)
				result[i][j] =
					a * u[i] * u[j] + b * v[i] * v[j] + c * v[j] * u[i];
		}
		result[0][0] += 1.0;
		result[1][1] += 1.0;
		result[2][2] += 1.0;

		if(MatType::numColumns() == 4) padMat4(result);
		return result;

	} else {
		double c = v1.dot(v2);
		double a = (1.0 - c) / cross.dot(cross);

		double a0 = a * cross[0];
		double a1 = a * cross[1];
		double a2 = a * cross[2];

		double a01 = a0 * cross[1];
		double a02 = a0 * cross[2];
		double a12 = a1 * cross[2];

		MatType r;

		r[0][0] = c + a0 * cross[0];
		r[0][1] = a01 + cross[2];
		r[0][2] = a02 - cross[1],
		r[1][0] = a01 - cross[2];
		r[1][1] = c + a1 * cross[1];
		r[1][2] = a12 + cross[0];
		r[2][0] = a02 + cross[1];
		r[2][1] = a12 - cross[0];
		r[2][2] = c + a2 * cross[2];

		if(MatType::numColumns() == 4) padMat4(r);
		return r;

	}
}//*/
void ToRPW(vec3 &xyzwpr) const{
	double w, p, r;
	#define _m_ *4+
	if(m[2 _m_ 0] > (1.0 - 1e-6)){
		p = -PI * 0.5;
		r = 0;
		w = atan2(-m[1 _m_ 2], m[1 _m_ 1]);
	} else if(m[2 _m_ 0] < -1.0 + 1e-6){
		p = 0.5*PI;
		r = 0;
		w = atan2(m[1 _m_ 2], m[1 _m_ 1]);
	} else {
		p = atan2(-m[2 _m_ 0], sqrt(m[0 _m_ 0] * m[0 _m_ 0] + m[1 _m_ 0] * m[1 _m_ 0]));
		w = atan2(m[1 _m_ 0], m[0 _m_ 0]);
		r = atan2(m[2 _m_ 1], m[2 _m_ 2]);
	}
	#undef _m
	xyzwpr[0] = r * 180.0 / PI;
	xyzwpr[1] = p * 180.0 / PI;
	xyzwpr[2] = w * 180.0 / PI;
}
void RPW_2_Mat(double r, double p, double w){
	double a = r * PI / 180.0;
	double b = p * PI / 180.0;
	double c = w * PI / 180.0;
	float ca = cos(a);
	float sa = sin(a);
	float cb = cos(b);
	float sb = sin(b);
	float cc = cos(c);
	float sc = sin(c);
	*this = mat4(cb * cc, cc * sa * sb - ca * sc, sa * sc + ca * cc * sb, 0.0f,
				cb * sc, ca * cc + sa * sb * sc, ca * sb * sc - cc * sa, 0.0f,
				-sb, cb * sa, ca * cb, 0.0f,
				0,0,0,1);
}
	//-----------------------------------------------------------------------------
	void fromEuler(const vec3 &euler, RotationOrder order = RotationOrder::Default) {
		float x = euler.x, y = euler.y, z = euler.z;
		float a = cos(x), b = sin(x);
		float c = cos(y), d = sin(y);
		float e = cos(z), f = sin(z);

		identity();

		if (order == RotationOrder::XYZ) {
			float ae = a * e, af = a * f, be = b * e, bf = b * f;

			m[0] = c * e;
			m[4] = -c * f;
			m[8] = d;

			m[1] = af + be * d;
			m[5] = ae - bf * d;
			m[9] = -b * c;

			m[2] = bf - ae * d;
			m[6] = be + af * d;
			m[10] = a * c;

		} else if (order == RotationOrder::YXZ) {
			float ce = c * e, cf = c * f, de = d * e, df = d * f;

			m[0] = ce + df * b;
			m[4] = de * b - cf;
			m[8] = a * d;

			m[1] = a * f;
			m[5] = a * e;
			m[9] = -b;

			m[2] = cf * b - de;
			m[6] = df + ce * b;
			m[10] = a * c;

		} else if (order == RotationOrder::ZXY) {
			float ce = c * e, cf = c * f, de = d * e, df = d * f;

			m[0] = ce - df * b;
			m[4] = -a * f;
			m[8] = de + cf * b;

			m[1] = cf + de * b;
			m[5] = a * e;
			m[9] = df - ce * b;

			m[2] = -a * d;
			m[6] = b;
			m[10] = a * c;

		} else if (order == RotationOrder::ZYX) {
			float ae = a * e, af = a * f, be = b * e, bf = b * f;

			m[0] = c * e;
			m[4] = be * d - af;
			m[8] = ae * d + bf;

			m[1] = c * f;
			m[5] = bf * d + ae;
			m[9] = af * d - be;

			m[2] = -d;
			m[6] = b * c;
			m[10] = a * c;

		} else if (order == RotationOrder::YZX) {
			float ac = a * c, ad = a * d, bc = b * c, bd = b * d;

			m[0] = c * e;
			m[4] = bd - ac * f;
			m[8] = bc * f + ad;

			m[1] = f;
			m[5] = a * e;
			m[9] = -b * e;

			m[2] = -d * e;
			m[6] = ad * f + bc;
			m[10] = ac - bd * f;

		} else if (order == RotationOrder::XZY) {
			float ac = a * c, ad = a * d, bc = b * c, bd = b * d;

			m[0] = c * e;
			m[4] = -f;
			m[8] = d * e;

			m[1] = ac * f + bd;
			m[5] = a * e;
			m[9] = ad * f - bc;

			m[2] = bc * f - ad;
			m[6] = b * e;
			m[10] = bd * f + ac;
		}
	}
//-----------------------------------------------------------------------------
//INLINE vec3 toEuler()const{//h=y,a=p,b=r
//	float T1 = atan2(m[6], m[10]);
//	float C2 = sqrt(m[0]*m[0] + m[1]*m[1]);
//	float T2 = atan2(-m[2], C2);
//	float S1 = sin(T1), C1 = cos(T1);
//	float T3 = atan2(S1*m[8] - C1*m[4], C1*m[5] - S1*m[9]);
//	return vec3(T1, T2, T3);
// }
//-----------------------------------------------------------------------------
//vec3 getDiag3()const{return vec3(m[0],m[5],m[10]);}//m[15]
INLINE vec3 get_scale()const { return vec3(len(R), len(U), len(F)); }
INLINE void setDiag(const vec3 &s) { m[0] = s.x; m[5] = s.y; m[10] = s.z; }//->>>>
INLINE void set_scale(const vec3 &s) { R *= s.x; U *= s.y; F *= s.z; }
//-----------------------------------------------------------------------------
INLINE void Plane(const vec3 &N,vec3 *Uv=0){
	F = norm(N);
	if(Uv){U=norm(*Uv);}else{U=UNIT_UP;}
	//float UdotF=dot(U,F);
	//if(UdotF> (1.0-EPSILON)){U= UNIT_DR;}//if F==U
	//if(UdotF<-(1.0-EPSILON)){U=-UNIT_DR;}//if F==-U
	R = norm(cross(U,F));
	U = norm(cross(F,R));
}
//-----------------------------------------------------------------------------
// R = norm(cross(U,F));
// U = norm(cross(F,R));  ruf
// F = norm(cross(R,U));
//-----------------------------------------------------------------------------
INLINE mat4 transpose()const{
	return mat4(m[0],m[4],m[8 ],m[12],
				m[1],m[5],m[9 ],m[13],
				m[2],m[6],m[10],m[14],
				m[3],m[7],m[11],m[15]);
}
//-----------------------------------------------------------------------------
INLINE mat4 transpose3()const{
	return mat4(m[0],m[4],m[8 ],m[3],
				m[1],m[5],m[9 ],m[7],
				m[2],m[6],m[10],m[11],
				m[12],m[13],m[14],m[15]);
}
//-----------------------------------------------------------------------------
INLINE float det()const{
	return m[0]*m[5]*m[10] + m[4]*m[9]*m[2] + m[8]*m[1]*m[6]
		 - m[8]*m[5]*m[2] - m[4]*m[1]*m[10] - m[0]*m[9]*m[6];
}
//-----------------------------------------------------------------------------
INLINE mat4 inv()const {
	mat4 ret(1.0f);
	float det;
	det  = m[0] * m[5] * m[10];
	det += m[4] * m[9] * m[2];
	det += m[8] * m[1] * m[6];
	det -= m[8] * m[5] * m[2];
	det -= m[4] * m[1] * m[10];
	det -= m[0] * m[9] * m[6];
	float idet = 1.0f / det;
	ret[0] =  (m[5] * m[10] - m[9] * m[6])*idet;
	ret[1] = -(m[1] * m[10] - m[9] * m[2])*idet;
	ret[2] =  (m[1] * m[6] - m[5] * m[2])*idet;
	ret[4] = -(m[4] * m[10] - m[8] * m[6])*idet;
	ret[5] =  (m[0] * m[10] - m[8] * m[2])*idet;
	ret[6] = -(m[0] * m[6] - m[4] * m[2])*idet;
	ret[8] =  (m[4] * m[9] - m[8] * m[5])*idet;
	ret[9] = -(m[0] * m[9] - m[8] * m[1])*idet;
	ret[10] = (m[0] * m[5] - m[4] * m[1])*idet;
	ret[12] = -(m[12] * ret[0] + m[13] * ret[4] + m[14] * ret[8]);
	ret[13] = -(m[12] * ret[1] + m[13] * ret[5] + m[14] * ret[9]);
	ret[14] = -(m[12] * ret[2] + m[13] * ret[6] + m[14] * ret[10]);
	return ret;
}
mat4 inv3()const{
	mat4 ret;
	float det;
	det  = m00 * (m11 * m22 - m12 * m21);
	det -= m01 * (m10 * m22 - m12 * m20);
	det += m02 * (m10 * m21 - m11 * m20); 
	float idet = 1.0f/det;
	ret.m00 =  (m11 * m22 - m12 * m21) * idet;
	ret.m10 = -(m10 * m22 - m12 * m20) * idet;
	ret.m20 =  (m10 * m21 - m11 * m20) * idet;
	ret.m30 = 0.0f;
	ret.m01 = -(m01 * m22 - m02 * m21) * idet;
	ret.m11 =  (m00 * m22 - m02 * m20) * idet;
	ret.m21 = -(m00 * m21 - m01 * m20) * idet;
	ret.m31 = 0.0f;
	ret.m02 =  (m01 * m12 - m02 * m11) * idet;
	ret.m12 = -(m00 * m12 - m02 * m10) * idet;
	ret.m22 =  (m00 * m11 - m01 * m10) * idet;
	ret.m32 = 0.0f;
	ret.m03 = -(ret.m00 * m03 + ret.m01 * m13 + ret.m02 * m23);
	ret.m13 = -(ret.m10 * m03 + ret.m11 * m13 + ret.m12 * m23);
	ret.m23 = -(ret.m20 * m03 + ret.m21 * m13 + ret.m22 * m23);
	ret.m33 = 1.0f;
	return ret;
}
//-----------------------------------------------------------------------------
// Invert via gauss-jordan elimination. Modified from dreamworks internal mx library
//mat4 inverse() const{
//	mat4 temp = *this;
//	mat4 inverse(1.0f);
//
//	// Forward elimination step
//	double det = 1.0;
//	for (int i = 0; i < 4; ++i) {
//		int row = i;
//		double max = fabs(temp[i][i]);
//
//		for (int k = i + 1; k < 4; ++k) {
//			if (fabs(temp[k][i]) > max) {
//				row = k;
//				max = fabs(temp[k][i]);
//			}
//		}
//
//		if (isExactlyEqual(max, 0.0)) return mat4(1.0f);
//
//		// must move pivot to row i
//		if (row != i) {
//			det = -det;
//			for (int k = 0; k < 4; ++k) {
//				std::swap(temp[row][k], temp[i][k]);
//				std::swap(inverse[row][k], inverse[i][k]);
//			}
//		}
//
//		double pivot = temp[i][i];
//		det *= pivot;
//
//		// scale row i
//		for (int k = 0; k < 4; ++k) {
//			temp[i][k] /= pivot;
//			inverse[i][k] /= pivot;
//		}
//
//		// eliminate in rows below i
//		for (int j = i + 1; j < 4; ++j) {
//			double t = temp[j][i];
//			if (!isExactlyEqual(t, 0.0)) {
//				// subtract scaled row i from row j
//				for (int k = 0; k < 4; ++k) {
//					temp[j][k] -= temp[i][k] * t;
//					inverse[j][k] -= inverse[i][k] * t;
//				}
//			}
//		}
//	}
//
//	// Backward elimination step
//	for (int i = 3; i > 0; --i) {
//		for (int j = 0; j < i; ++j) {
//			double t = temp[j][i];
//
//			if (!isExactlyEqual(t, 0.0)) {
//				for (int k = 0; k < 4; ++k) {
//					inverse[j][k] -= inverse[i][k] * t;
//				}
//			}
//		}
//	}
//	//return det * det >= tolerance * tolerance;
//	return inverse;
//}
//-----------------------------------------------------------------------------
INLINE void orthonorm(const vec3 &dir,const vec3 &up){
	F = norm(dir);
	R = norm(cross(up,dir));
	U = norm(cross(dir,R));
	//R = norm(cross(up,dir));
	//U = norm(up);//norm(cross(dir,R));
	//F = norm(cross(R,U));
}
//-----------------------------------------------------------------------------
INLINE void lookat(const vec3 &eye,const vec3 &at, const vec3 &up){//mat4 LAM(1);LAM.lookat();return LAM;
	F = norm(at - eye); U=up;
	float UdotF=dot(U,F);
	#ifdef Z_UP
		if(UdotF> (1.0-EPSILON)){U=-UNIT_RT;}// UNIT_DR;}//if F==U
		if(UdotF<-(1.0-EPSILON)){U= UNIT_RT;}//-UNIT_DR;}//if F==-U
	#endif
	#ifdef Y_UP
		if(UdotF> (1.0-EPSILON)){U= UNIT_DR;}//if F==U
		if(UdotF<-(1.0-EPSILON)){U=-UNIT_DR;}//if F==-U
	#endif
	R = norm(cross(U,F));
	U = norm(cross(F,R));
	T.set(-dot(R,eye), -dot(U,eye), -dot(F,eye), 1.0f);
}
//-----------------------------------------------------------------------------
//void operator=(const Dquat &q);//FD
INLINE void operator=(const quat &q);//FD
//-----------------------------------------------------------------------------
INLINE void print(const char *name)const {
	//LOG::msg("%s:\n[%g %g %g %g]\n[%g %g %g %g]\n[%g %g %g %g]\n[%g %g %g %g]\n", name, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
	LOG::msg("%s:\n[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n", name, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
}
//-----------------------------------------------------------------------------
INLINE void print3(const char *name)const {
	LOG::msg("%s:\n[%f %f %f]\n[%f %f %f]\n[%f %f %f]\n", name, m[0], m[1], m[2],  m[4], m[5], m[6],  m[8], m[9], m[10] );
}
//-----------------------------------------------------------------------------
INLINE void printEuler(const char *name)const {
	vec3 e = toEulerDays()*R2D;
	vec3 s = get_scale();
	LOG::msg("%s: deg[%f %f %f] pos[%f %f %f] scl[%f %f %f]\n", name, e.x, e.y, e.z, T.x, T.y, T.z, s.x, s.y, s.z);
}
//-----------------------------------------------------------------------------
INLINE void norm_rot(){//  https://github.com/openexr/openexr/blob/master/IlmBase/Imath/ImathMatrixAlgo.h
	vec3 row[3],scl,shr;
	//row==*4+??
	row[0] = vec3(m[0*4+0], m[0*4+1], m[0*4+2]);
	row[1] = vec3(m[1*4+0], m[1*4+1], m[1*4+2]);
	row[2] = vec3(m[2*4+0], m[2*4+1], m[2*4+2]);

	float maxVal = 0;
	for (int i=0; i < 3; i++)
		for (int j=0; j < 3; j++)
			if(fabs(row[i][j]) > maxVal) maxVal = fabs(row[i][j]);
	// We normalize the 3x3 matrix here.
	// It was noticed that this can improve numerical stability significantly,
	// especially when many of the upper 3x3 matrix's coefficients are very
	// close to zero; we correct for this step at the end by multiplying the
	// scaling factors by maxVal at the end (shear and rotation are not
	// affected by the normalization).
	if (maxVal != 0){
	for (int i=0; i < 3; i++)
		//   if (! checkForZeroScaleInRow (maxVal, row[i], exc))
		//return false;
		//   else
		row[i] /= maxVal;
	}
	// Compute X scale factor.
	scl.x = len(row[0]);//.length ();
	//if (! checkForZeroScaleInRow (scl.x, row[0], exc))
	//return false;
	// Normalize first row.
	row[0] /= scl.x;
	// An XY shear factor will shear the X coord. as the Y coord. changes.
	// There are 6 combinations (XY, XZ, YZ, YX, ZX, ZY), although we only
	// extract the first 3 because we can effect the last 3 by shearing in
	// XY, XZ, YZ combined rotations and scales.
	//
	// shear matrix <   1,  YX,  ZX,  0,
	//				 XY,   1,  ZY,  0,
	//				 XZ,  YZ,   1,  0,
	//				  0,   0,   0,  1 >
	// Compute XY shear factor and make 2nd row orthogonal to 1st.
	shr[0]  = dot(row[0],row[1]);
	row[1] -= row[0]*shr[0];
	// Now, compute Y scale.
	scl.y = len(row[1]);//.length ();
	//   if (! checkForZeroScaleInRow (scl.y, row[1], exc))
	//return false;
	// Normalize 2nd row and correct the XY shear factor for Y scaling.
	row[1] /= scl.y;
	shr[0] /= scl.y;
	// Compute XZ and YZ shears, orthogonalize 3rd row.
	shr[1]  = dot(row[0],row[2]);
	row[2] -= row[0]*shr[1];
	shr[2]  = dot(row[1],row[2]);
	row[2] -= row[1]*shr[2];
	// Next, get Z scale.
	scl.z = len(row[2]);//.length ();
	//   if (! checkForZeroScaleInRow (scl.z, row[2], exc))
	//return false;
	// Normalize 3rd row and correct the XZ and YZ shear factors for Z scaling.
	row[2] /= scl.z;
	shr[1] /= scl.z;
	shr[2] /= scl.z;
	// At this point, the upper 3x3 matrix in mat is orthonormal.
	// Check for a coordinate system flip. If the determinant
	// is less than zero, then negate the matrix and the scaling factors.
	if (dot(row[0],cross(row[1],row[2])) < 0)
	for (int  i=0; i < 3; i++){
		scl[i] *= -1;
		row[i] *= -1;
	}
	// Copy over the orthonormal rows into the returned matrix.
	// The upper 3x3 matrix in mat is now a rotation matrix.
	for (int i=0; i < 3; i++){
		m[i*4+0] = row[i][0];
		m[i*4+1] = row[i][1];
		m[i*4+2] = row[i][2];
	}
	// Correct the scaling factors for the normalization step that we
	// performed above; shear and rotation are not affected by the
	// normalization.
	scl *= maxVal;
}
//-----------------------------------------------------------------------------
INLINE mat4 RotationOnly()const{
	mat4 ret=*this;
	ret.T.set(0,0,0,1.0f);
	return ret;
}
//-----------------------------------------------------------------------------
};
//============================================================================= end mat4
INLINE mat4 lookatmat(const vec3 &eye,const vec3 &at, const vec3 &up){//return lookat();
	mat4 LAM(1);
	LAM.lookat(eye,at,up);
	return LAM;
}
//=============================================================================
INLINE mat4 Plane(const vec3 &N,vec3 *Uv=0){
	mat4 PM(1);
	PM.Plane(N,Uv);
	return PM;
}
//=============================================================================
INLINE mat4 rot_x(const float &rad){
	float c = cos(rad),s = sin(rad);
	return mat4(1,0, 0,0,
				0,c,-s,0,//[2][1]=-s;	  //c,s
				0,s, c,0,				  //-s,c
				0,0, 0,1);
}
//=============================================================================
INLINE mat4 rot_y(const float &rad){
	float c = cos(rad),s = sin(rad);
	return mat4( c,0,s,0,//c,-s
				 0,1,0,0,
				-s,0,c,0,//s,c
				 0,0,0,1);
}
//=============================================================================
INLINE mat4 rot_z(const float &rad){
	float c = cos(rad),s = sin(rad);
	return mat4(c,-s,0,0,//c,s
				s, c,0,0,//-s,c
				0, 0,1,0,
				0, 0,0,1);
}
//=============================================================================
//pos=rz*ry*rx*pos; RYP ZYX
/*mat4 lookAt(const vec3 &eye,const vec3 &at,const vec3 &up){//2:00:19
	vec3 f=norm(at-eye), r=norm(cross(f,up)), u=norm(cross(r,f));
	return mat4(		r.x,		u.x,	  -f.x,0,
						r.y,		u.y,	  -f.y,0,
						r.z,		u.z,	  -f.z,0,
				-dot(eye,r), -dot(eye,u), dot(eye,f), 1);
}   */
//=============================================================================
//D3DXMatrixPerspectiveLH http://doxygen.reactos.org/de/d57/dll_2directx_2wine_2d3dx9__36_2math_8c_source.html#00359
INLINE mat4 Frustum_gl_LH(float l, float r, float b, float t, float n, float f){
	return mat4((2*n)/(r-l),		   0,		   0, 0,
						  0, (2*n)/(t-b),		   0, 0,
				(r+l)/(r-l), (t+b)/(t-b),	 f/(f-n), 1,
						  0,		   0, (n*f)/(n-f), 0);
}
//============================================================================= D3DXMatrixPerspectiveFovRH
INLINE mat4 Frustum_gl_RH(float l, float r, float b, float t, float n, float f){
	return mat4((2*n)/(r-l),		   0,		   0, 0,
						  0, (2*n)/(t-b),		   0, 0,
				(r+l)/(r-l), (t+b)/(t-b),	 f/(n-f),-1,
						  0,		   0, (n*f)/(n-f), 0);
	/* return mat4( (2*n)/(r-l),		   0,			  0, 0,//SISIGGRAPR 1:57:07 https://www.youtube.com/watch?v=T8gjVbn8VBk&list=LLCd0tWyeFM56_Bn-N59sP8A&feature=c4-overview
							  0, (2*n)/(t-b),			  0, 0,
					(r+l)/(r-l), (t+b)/(t-b),   -(f+n)/(f-n),-1,
							  0,		   0, -(2*f*n)/(f-n), 0);*/
}
//=============================================================================
//http://www.labri.fr/perso/nrougier/python-opengl/ //There exists a second form of the perpective matrix that might be easier to manipulate
//=============================================================================
//http://www.scratchapixel.com/lessons/3d-advanced-lessons/perspective-and-orthographic-projection-matrix/orthographic-projection/
INLINE mat4 Frustum_gl(float l, float r, float b, float t, float n, float f){
	return mat4(  2*n/(r-l),		   0,			0, 0,
						  0,   2*n/(t-b),			0, 0,
				(r+l)/(r-l), (t+b)/(t-b), -(f+n)/(f-n),-1,
						  0,		   0, -2*f*n/(f-n), 0);
}
//=============================================================================
INLINE mat4 Perspective_gl(float angle, float aspect, float n, float f){
	float scale = tan(D2R*(angle * 0.5f)) * n;
	float r = aspect * scale;
	float t = scale;
	//if(0){
		//return Frustum_gl_LH(-r, r, -t, t, n, f);
	//}else{
		return Frustum_gl_RH(-r, r, -t, t, n, f);
	//}
}
//=============================================================================
INLINE mat4 Orthographic_gl(float l, float r, float b, float t, float n, float f){
	/*return mat4(2/(r-l),	  0,	   0, (r+l)/(r-l),
						0,2/(t-b),	   0, (t+b)/(t-b),
						0,	  0,-2/(f-n), (f+n)/(f-n),
						0,	  0,	   0,		  1);//SISIGGRAPR 1:57:07 https://www.youtube.com/watch?v=T8gjVbn8VBk&list=LLCd0tWyeFM56_Bn-N59sP8A&feature=c4-overview*/
	return mat4(	 2/(r-l),		   0,		   0, 0,
						   0,	 2/(t-b),		   0, 0,
						   0,		   0,-2*f*n/(f-n), 0,
				-(r+l)/(r-l),-(t+b)/(t-b),	-n/(f-n), 1);
}
//=============================================================================
INLINE mat4 Ortho(float l,float r,float b,float t,float n,float f){//GL
	return mat4(  2.0f/(r-l),			0,			0, 0,
						   0,   2.0f/(t-b),			0, 0,
						   0,			0,  -2.0f/(f-n), 0, //3:-1 / (f - n)
				-(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0f);//3:-n / (f - n)
}
//=============================================================================
INLINE mat4 Perspective(const float &fovy, const float &a, const float &n, const float &f){
	const float r = 1.0f/tan(fovy*PI/360.0f);
	return mat4(r/a,			   0,		   0, 0, //1: 2*n/(r-l)
				  0,			   r,		   0, 0, //2: 2*n/(t-b)
				  0,			   0, (f+n)/(n-f),-1, //3: -(f+n)/(f-n) 4: -1
				  0, 0,(2*f*n)/(n-f),			  0);//3: -2*f*n/(f-n)
}
//=============================================================================
//http://www.reedbeta.com/blog/depth-precision-visualized/
//http://www.geometry.caltech.edu/pubs/UD12.pdf
//glDepthRange(0, 1);
//if(isinfiniteproj && isdepthclip) {
//	glClearDepth(1.0 - n/f);
//}
INLINE mat4 InfPerspective(const float x1, const float x2, const float y1, const float y2, const float n, const float f){
	//const float r = 1.0f/tan(fovy*PI/360.0f);
	float b = 2.0f*f*n;
	float c = b / (x2 - x1);
	float d = b / (y2 - y1);
	float i = (x2 + x1) / (x2 - x1);
	float j = (y2 + y1) / (y2 - y1);
	return mat4(c, 0, i, 0,
				0, d, j, 0,
				0, 0, -1.0f, -b,
				0, 0, -1.0f, 0);
}
//=============================================================================
INLINE mat4 ModelView(const vec3 &ang,const vec3 &pos){
	mat4 RM(ang*D2R,0.0),TM(0.0,-pos);
	#ifdef Z_UP
		mat4 ZU(vec3(0,0,-1),vec3(-1,0,0),vec3(0,1,0));
		return ZU*RM.inv()*TM;//  .inv()
	#endif
	#ifdef Y_UP
		return mat4(RM*TM);
	#endif
}//cam pos, plane pos, plane normal
//=============================================================================
//mat4 mulPlaneProj(vec3 l,vec3 e, vec3 n){
//	float d, c;
//	float mat[16];
//
//	d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
//	c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;
//
//	mat[0]  = l[0]*n[0]+c;
//	mat[4]  = n[1]*l[0];
//	mat[8]  = n[2]*l[0];
//	mat[12] = -l[0]*c-l[0]*d;
//
//	mat[1]  = n[0]*l[1];
//	mat[5]  = l[1]*n[1]+c;
//	mat[9]  = n[2]*l[1];
//	mat[13] = -l[1]*c-l[1]*d;
//
//	mat[2]  = n[0]*l[2];
//	mat[6]  = n[1]*l[2];
//	mat[10] = l[2]*n[2]+c;
//	mat[14] = -l[2]*c-l[2]*d;
//
//	mat[3]  = n[0];
//	mat[7]  = n[1];
//	mat[11] = n[2];
//	mat[15] = -d;
//	return mat4(mat);
//   // glMultMatrixf(mat);
//}
//=============================================================================
INLINE mat4 shadowMatrix(const vec4 &plane,const vec4 &lightpos){
	float dotPL=dot(plane,lightpos);
	return mat4(dotPL-lightpos.x*plane.x,	 -lightpos.y*plane.x,	 -lightpos.z*plane.x,	 -lightpos.w*plane.x,
					 -lightpos.x*plane.y,dotPL-lightpos.y*plane.y,	 -lightpos.z*plane.y,	 -lightpos.w*plane.y,
					 -lightpos.x*plane.z,	 -lightpos.y*plane.z,dotPL-lightpos.z*plane.z,	 -lightpos.w*plane.z,
					 -lightpos.x*plane.w,	 -lightpos.y*plane.w,	 -lightpos.z*plane.w,dotPL-lightpos.w*plane.w);
}
//=============================================================================
//void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]){ // Find dot product between light position vector and ground plane normal. */
// float dot;
// float shadowMat[4][4];
// dot = ground[0] * light[0] + //distance between light and plane
// ground[1] * light[1] +
// ground[2] * light[2] +
// ground[3] * light[3];
// shadowMat[0][0] = dot - light[0] * ground[0];
// shadowMat[1][0] = 0.0 - light[0] * ground[1];
// shadowMat[2][0] = 0.0 - light[0] * ground[2];
// shadowMat[3][0] = 0.0 - light[0] * ground[3];
// shadowMat[0][1] = 0.0 - light[1] * ground[0];
// shadowMat[1][1] = dot - light[1] * ground[1];
// shadowMat[2][1] = 0.0 - light[1] * ground[2];
// shadowMat[3][1] = 0.0 - light[1] * ground[3];
// shadowMat[0][2] = 0.0 - light[2] * ground[0];
// shadowMat[1][2] = 0.0 - light[2] * ground[1];
// shadowMat[2][2] = dot - light[2] * ground[2];
// shadowMat[3][2] = 0.0 - light[2] * ground[3];
// shadowMat[0][3] = 0.0 - light[3] * ground[0];
// shadowMat[1][3] = 0.0 - light[3] * ground[1];
// shadowMat[2][3] = 0.0 - light[3] * ground[2];
// shadowMat[3][3] = dot - light[3] * ground[3];
// glMultMatrixf((const GLfloat*)shadowMat); //Concatination
//}
//=============================================================================
INLINE mat4 AxisRot(const vec3 &axis,float angle){//http://ru.wikipedia.org/wiki/???????_????????
	float c=cos(angle),s=sin(angle),oc=1.0f-c;
	return mat4(	   c+oc*axis.x*axis.x,oc*axis.y*axis.x-s*axis.z,oc*axis.z*axis.x+s*axis.y, 0,
				oc*axis.x*axis.y+s*axis.z,	   c+oc*axis.y*axis.y,oc*axis.z*axis.y-s*axis.x, 0,
				oc*axis.x*axis.z-s*axis.y,oc*axis.y*axis.z+s*axis.x,	   c+oc*axis.z*axis.z, 0,
				0,					  0,						0,						   1);
}
//=============================================================================
INLINE mat4 rotationAlign(const vec3 &d,const vec3 &z){//axis z allign to dir d (both normalized) http://www.iquilezles.org/www/articles/noacos/noacos.htm
	const vec3  v = cross(z,d);			 //WTF this function for? - allign with damn roll
	const float c = dot(z,d);
	const float k = 1.0f/(1.0f+c);
	return mat4(v.x*v.x*k + c,   v.y*v.x*k - v.z, v.z*v.x*k + v.y,0,
				v.x*v.y*k + v.z, v.y*v.y*k + c,   v.z*v.y*k - v.x,0,
				v.x*v.z*k - v.y, v.y*v.z*k + v.x, v.z*v.z*k + c  ,0, 0,0,0,1);
}
//=============================================================================
INLINE bool mInvert4(float *out){
// NB. OpenGL Matrices are COLUMN major
#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]
	float m[16];memcpy(m,out,16*sizeof(float));
	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT(m,0,0), r0[1] = MAT(m,0,1),
	r0[2] = MAT(m,0,2), r0[3] = MAT(m,0,3),
	r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

	r1[0] = MAT(m,1,0), r1[1] = MAT(m,1,1),
	r1[2] = MAT(m,1,2), r1[3] = MAT(m,1,3),
	r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

	r2[0] = MAT(m,2,0), r2[1] = MAT(m,2,1),
	r2[2] = MAT(m,2,2), r2[3] = MAT(m,2,3),
	r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

	r3[0] = MAT(m,3,0), r3[1] = MAT(m,3,1),
	r3[2] = MAT(m,3,2), r3[3] = MAT(m,3,3),
	r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	// choose pivot - or die
	if (fabs(r3[0])>fabs(r2[0])) SWAP_ROWS(r3, r2);
	if (fabs(r2[0])>fabs(r1[0])) SWAP_ROWS(r2, r1);
	if (fabs(r1[0])>fabs(r0[0])) SWAP_ROWS(r1, r0);
	if (0.0 == r0[0]){return 0;}

	// eliminate first variable
	m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or die
	if (fabs(r3[1])>fabs(r2[1])) SWAP_ROWS(r3, r2);
	if (fabs(r2[1])>fabs(r1[1])) SWAP_ROWS(r2, r1);
	if (0.0 == r1[1]) {return 0;}

	// eliminate second variable
	m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or die
	if (fabs(r3[2])>fabs(r2[2])) SWAP_ROWS(r3, r2);
	if (0.0 == r2[2]) {return 0;}

	// eliminate third variable
	m3 = r3[2]/r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
	r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
	r3[7] -= m3 * r2[7];

	// last check
	if (0.0 == r3[3]) {return 0;}

	s = 1.0f/r3[3];			  // now back substitute row 3
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];				 // now back substitute row 2
	s  = 1.0f/r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
	r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
	r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
	r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];				 // now back substitute row 1
	s  = 1.0f/r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
	r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
	r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];				 // now back substitute row 0
	s  = 1.0f/r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
	r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
	MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
	MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
	MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
	MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
	MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
	MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
	MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

	return 1;
#undef MAT
#undef SWAP_ROWS
}
//=============================================================================
// bool Projectt(const vec3 &obj,const mat4 &M,const mat4 &P,int VP[4],vec3 &win){
// vec4 in(obj,1.0f);
// in=M.mul4(P)*in;
// if(in[3]==0.0f)return false;
// in[0]/=in[3];
// in[1]/=in[3];
// in[2]/=in[3];
// /* Map x, y and z to range 0-1 */ /* Map x,y to viewport */
// win[0]=VP[0]+(1.0f+in[0])*VP[2]*0.5;	   //(1+tk[0]/tk.w)*VP[2]/2;
// win[1]=VP[1]+(1.0f+in[1])*VP[3]*0.5;	   //(1+tk[1]/tk.w)*VP[3]/2;
// win[2]=(1.0f+in[2])*0.5;
// return true;
//}
//=============================================================================
//INLINE void modified_gram_schmidt(Mat33f &out, const Mat33f &in){https://fgiesen.wordpress.com/page/6/
//	out.col[0] = normalize(in.col[0]);
//	out.col[1] = normalize(in.col[1] -
//						   dot(in.col[1], out.col[0])*out.col[0]);
//
//	out.col[2] = in.col[2] -
//				 dot(in.col[2], out.col[0])*out.col[0];
//	// note the second dot product is computed from the partial
//	// result out.col[2], not the input vector in.col[2]!
//	out.col[2] -= dot(out.col[2], out.col[1])*out.col[1];
//	out.col[2] = normalize(out.col[2]);
//}
//=============================================================================
#endif
