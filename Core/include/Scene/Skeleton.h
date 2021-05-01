#ifndef __SKELETON_H__
#define __SKELETON_H__

#include "Sys/DLL_API.h"
#include "Sys/vector.h"
#include "Math/Maths.h"
#include "Scene/Node.h"

struct Camera;//FD
struct VertBone8;//FD
//struct Bone{
//	Origin org;
//	str *name;
//	Bone *parent;
//};

struct DLL_API Skeleton{// (255 bones, 8 bone/vert, 1/256 weight) _OR_ (16k bones, 4 bone/vert, 1/16k weight) to pack skinning VertWeights to vec4()
	//Vector<Bone> b;
	u8_t mb;//num bones
		Origin *src;// link to local bone matrix
		u8_t *parent;// float:4b/v vec4:8b/v
		str **bname;// bone name

	u32_t ma;// num animations
		struct SkelAnim **a;

	Vector<Origin> cur;// animated local bone transform
	Vector<mat4> bm;// heirarchical bone matrix
	Vector<mat4> ibm;// inverse hierarchical bone matrix
	Vector<mat4> B;// skinned final bone transform + animation if there one

	Skeleton();
	Skeleton(u8_t nmb, Origin *b, int *p);
	~Skeleton();

	void init(u8_t nmb, Origin *b, int *p);
	void link_anim(u32_t nma, struct SkelAnim **sa);
	void reset();
	void resize(u8_t nmb);

	void CookAnim(float dtime);
	void animate(float dtime);

	void deform_vn(u32_t mv, const vec3 *v, vec3 *V, const vec3 *vn, vec3 *VN, const VertBone8 *idwt8);
	void bind(u32_t mv, const vec3 *v, vec3 *V, const VertBone8 *idwt8, u8_t sb);
	void unbind(u32_t mv, const vec3 *v, vec3 *V, const VertBone8 *idwt8, u8_t sb);

	void aim(u8_t i);
	mat4 to_local_bone(const mat4 &from, const u8_t i)const;
	bool HasParent(u8_t child_bone_id, u8_t test_parent_id)const;

};

#endif