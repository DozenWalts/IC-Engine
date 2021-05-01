#ifndef __ORIGIN_H__
#define __ORIGIN_H__
//=============================================================================
//=============================================================================
// storing decomposed transformation R|S|T
//=============================================================================
#include "quat.h"
#include "mat4.h"
struct DLL_API Origin {//40 (24 less mat4=64) or 28 witout scale	   sizeof()=40
	quat rot;// 16
	vec3 pos, size;// 24
//-----------------------------------------------------------------------------
	INLINE Origin() { identity(); }
	//-----------------------------------------------------------------------------
	INLINE Origin(const quat &r, const vec3 &t) { rot = r; pos = t; size.set(1); }
	INLINE Origin(const mat4 &mat) {
		pos = mat.T;
		size = mat.get_scale();
		mat4 mt = mat;// remove scale
		mt.R /= size.x;
		mt.U /= size.y;
		mt.F /= size.z;
		rot = mt;
	}
	//-----------------------------------------------------------------------------
	INLINE void set(const quat &r, const vec3 &t) { rot = r; pos = t; size.set(1); }
	//-----------------------------------------------------------------------------
	INLINE void set(const vec3 &r, const vec3 &t, const vec3 &s, RotationOrder order = RotationOrder::Default) { rot.fromEuler(r, order); pos = t; size = s; }
	//-----------------------------------------------------------------------------
	INLINE void identity() { pos.set(0.0); rot = quat(); size.set(1); }
	//-----------------------------------------------------------------------------
	INLINE operator mat4()const { return mat4(rot, pos, size); }
	//-----------------------------------------------------------------------------
	//mat4 mat()const{return mat4(rot,pos,size);};
	//-----------------------------------------------------------------------------
	INLINE void operator=(const Origin &org) {
		pos = org.pos;
		rot = org.rot;
		size = org.size;
	}
	//-----------------------------------------------------------------------------
	INLINE void operator=(const mat4 &mat) {
		pos = mat.T;
		size = mat.get_scale();
		mat4 mt = mat;
		mt.R /= size.x;
		mt.U /= size.y;
		mt.F /= size.z;
		rot = mt;
	}
	//-----------------------------------------------------------------------------
	INLINE Origin &origin() { return *this; }
	//-----------------------------------------------------------------------------
	INLINE Origin origin_inv() { mat4 rm(rot, pos, size); return rm.inv(); }//quat irot = rot.inv();return Origin(irot, irot*-pos);}//scale ?	 
//-----------------------------------------------------------------------------
//Origin tolocal(const Origin &go){return Origin(rot.inv()*go.rot, rot.inv()*(go.pos-pos));};
//Origin toglobal(const Origin &lo){return Origin(rot*lo.rot, pos+rot*lo.pos);};
//-----------------------------------------------------------------------------
	INLINE Origin operator*(const Origin &g)const { return mat4(rot, pos, size) * mat4(g.rot, g.pos, g.size); };//Origin(rot*g.rot, g.pos + g.rot*pos);}//scale??	  
//-----------------------------------------------------------------------------
	INLINE vec3 operator*(const vec3 &v)const { return (rot*v + pos)*size; }
	//-----------------------------------------------------------------------------
	INLINE vec4 plane()const { return calcPlane(rot.dir(), pos); }
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
extern DLL_API const Origin Origin_identity;//(quat_identity, vec3_zero);
//=============================================================================
//vec3 local(const vec3 &pz){return grot.inv()*(pz-gpos);};
//vec3 global(const vec3 &pz){return gpos + grot*pz;};
//quat local(const quat &rt){return grot.inv()*rt;};
//quat global(const quat &rt){return grot*rt;};
//-----------------------------------------
//=============================================================================
//=============================================================================
//vec3 vec3::operator*(const vec3 &v){return rot*v+pos;}//scale??
//=============================================================================
#endif
