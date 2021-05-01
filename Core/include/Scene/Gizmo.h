#ifndef _GIZMO_H_
#define _GIZMO_H_

//=============================================================================
#include "Math/Maths.h"
#include "sys/vector.h"
//=============================================================================
struct DLL_API Gizmo{
	mat4 S;//source/saved mat
	mat4 D;//delta mat
	mat4 R,LiR;//result/render mat and LastInvertedRerult_mat
	//mat4 LR;//last iter result/render mat  to get dynamic_delta_mat	 pivot?
	vec3 cam_pos;//mat4 scr;//camera matrix <- store only quat, mat=(quat,ray.pos)
	quat cam_rot;
	bool grappled, reveal, planar, snap_transform;
	u32_t second_axis_on_plane;
	float o_dist;//origin_dist
	float s_dist;//saved origin dist
	float mov_step, rot_step, scl_step;
	u8_t STT;// bits [plane 0 1| tool 2 3| mode 4 5| rel 6 7]
	Ray lmray, tray;
	//-----------------------------------------------------------------------------
	void *pts_handle;
	Vector<vec3> pts;
	//-----------------------------------------------------------------------------
	enum {
		PLANE_X=0,
		PLANE_Y,
		PLANE_Z,
		PLANE_W
	};
	enum {
		T_SEL=0,
		T_MOV,
		T_ROT,
		T_SCL
	};
	enum {
		M_NONE=0,
		M_AXIS,
		M_PLANE,
		M_ALL
	};
	enum {
		R_LOCAL=0,
		R_GLOBAL,
		R_SCREEN,
		R_PLANAR
	};
	enum STATE {
		NONE=0,
		INIT,
		EDIT,
		DONE
	};
//-----------------------------------------------------------------------------
u8_t PLANEb()const{
	u8_t ret=0;
	if(BIT_CHECK(STT,0)) BIT_SET(ret,0);
	if(BIT_CHECK(STT,1)) BIT_SET(ret,1);
	return ret;
}
bool PLANE(u8_t p)const{return BIT_CHECK(STT,0)==BIT_CHECK(p,0) && BIT_CHECK(STT,1)==BIT_CHECK(p,1);}//PLANE_X =0|PLANE_Y =1|PLANE_Z =2|PLANE_W  =3
bool TOOL (u8_t t)const{return BIT_CHECK(STT,2)==BIT_CHECK(t,0) && BIT_CHECK(STT,3)==BIT_CHECK(t,1);}//T_SEL   =0|T_MOV   =1|T_ROT   =2|T_SCL    =3
bool MODE (u8_t m)const{return BIT_CHECK(STT,4)==BIT_CHECK(m,0) && BIT_CHECK(STT,5)==BIT_CHECK(m,1);}//M_NONE  =0|M_AXIS  =1|M_PLANE =2|M_ALL    =3
bool REL  (u8_t r)const{return BIT_CHECK(STT,6)==BIT_CHECK(r,0) && BIT_CHECK(STT,7)==BIT_CHECK(r,1);}//R_LOCAL =0|R_GLOBAL=1|R_SCREEN=2|R_PLANAR =3
void SET_PLANE(u8_t s){//0,1
	if(BIT_CHECK(s,0)!=BIT_CHECK(STT,0)) BIT_FLIP(STT,0);
	if(BIT_CHECK(s,1)!=BIT_CHECK(STT,1)) BIT_FLIP(STT,1);
}
void SET_TOOL(u8_t s){//2,3
	if(BIT_CHECK(s,0)!=BIT_CHECK(STT,2)) BIT_FLIP(STT,2);
	if(BIT_CHECK(s,1)!=BIT_CHECK(STT,3)) BIT_FLIP(STT,3);
}
void SET_MODE(u8_t s){//4,5
	if(BIT_CHECK(s,0)!=BIT_CHECK(STT,4)) BIT_FLIP(STT,4);
	if(BIT_CHECK(s,1)!=BIT_CHECK(STT,5)) BIT_FLIP(STT,5);
}
void SET_REL(u8_t s){//6,7
	if(BIT_CHECK(s,0)!=BIT_CHECK(STT,6)) BIT_FLIP(STT,6);// local/global
	if(BIT_CHECK(s,1)!=BIT_CHECK(STT,7)) BIT_FLIP(STT,7);// screen/planar
}
//-----------------------------------------------------------------------------
void init();
void reset(mat4 &SRC);
//-----------------------------------------------------------------------------
void edit(Origin &org, const Ray &mray, const quat &cm);
void edit(mat4 &org, const Ray &mray, const quat &cm);
//-----------------------------------------------------------------------------
//switch(cam->G.edit_delta(cam->mray,cam->rot)){// usage template
//	case STATE::INIT:{
//		init_edit_delta(some_mat)//setup start mat
//		break;
//	}
//	case STATE::EDIT:{// or STATE::DONE
//		...*=cam->G.D;// apply delta mat
//		break;
//	}
//}//switch
//-----------------------------------------------------------------------------
mat4 getSourceModMat(const mat4 &src)const;
void setSourceMat(const mat4 &SM);
//-----------------------------------------------------------------------------
mat4 getRezult()const;
//-----------------------------------------------------------------------------
u32_t edit_delta(const Ray &mray, const quat &cm);
void edit_R(const Ray &mray, const quat &cm);
//-----------------------------------------------------------------------------
void draw_plane(int i, float size)const;
void draw()const;
//-----------------------------------------------------------------------------
void hide();//call at end of each frame
//-----------------------------------------------------------------------------
u32_t edit_points(const Ray &mray, const quat &cm, u32_t num_v, vec3 *v, u8_t *sv, Origin RM);
//-----------------------------------------------------------------------------
};
//=============================================================================
#endif