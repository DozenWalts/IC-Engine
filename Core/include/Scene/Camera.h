#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Core.h"
#include "Math/Maths.h"
#include "UI/UI.h"
#include "Node.h"
#include "Scene/Gizmo.h"

//=============================================================================
//=============================================================================
struct DLL_API Camera final : Node, UI_Widget{
	mat4 PM,VM,MVP,PM_target;//projection,modelview,combined
	Origin EditPlane;//or mat4 Plane;?  mat4(16) or quat+vec3(7) - diff=9
	Ray mray,lmray;//,gmray;//current,last_frame,grappled_pos rays
	vec4 F[6], cmx,gcmx;//frustum + current mouse state(last+now); gcmx - grappled start cmx
	vec3 va,vb,vc,vd, vel,force;//,euler;// mouse_ip,
	float fov, Near, Far, zoom, ox, oy, cx, cy, dis[5];// camera intrinsics parameters	rad,
	bool mouselook, proj_mode, grappled, proj_on_EP, zoom_at_mouse, draw_circle_lods, draw_grid;
	//int *VP;//UI_Panel &VP;//int VP[4];  moved to widget
//---------------------------
	Node *target;//local global + object.input(Camera)
	Node *Controlled_object;
	//--------------------------
	float grid_fade;
//----------------------------------------------------------------------------- relocation
	vec3 tpos;
	quat trot;
	float relocate_time, reloc_poroj_time;
	bool relocate, proj_reloc;
//-----------------------------------------------------------------------------
	Gizmo gizmo;
	vec3 grap_mouse_ip;
	str info;
	float show_info_start_time;
//-----------------------------------------------------------------------------
Camera(){}
~Camera();
//-----------------------------------------------------------------------------
void init()override;
//-----------------------------------------------------------------------------
void resetExernalTranform();
//-----------------------------------------------------------------------------
void swap(Camera *c);
//-----------------------------------------------------------------------------
void setFrustum(float fv, float nr, float fr);
void setProjection(bool persp = true);
void setViewPort(int w, int h, int x = 0, int y = 0);
//-----------------------------------------------------------------------------
void mlook(bool mode = true);
//-----------------------------------------------------------------------------
void Input_UI()override;//FD{
// //switch mode
// Input_spectrator();
//};
//-----------------------------------------------------------------------------
float EPlaneDist()const;
float EPlaneDist(const mat4 &inv_RM)const;
float EPlaneMRayDist()const;
//----------------------------------------------------------------------------- scale on editplane inside RM
float ScreenScale(const mat4 &RM)const;
float ScreenScale()const;
float ScreenScale(const vec3 &v)const;
//-----------------------------------------------------------------------------
void center_mouse();
void apply_rotation_by_mouse(quat &q);
//-----------------------------------------------------------------------------
void show_info(int show_time = 5);//in seconds
void print(const char *text);
void print_info_controls();
//-----------------------------------------------------------------------------
void Input_spectator();
void calcFrustumPlanes(/*const mat4 &mvp,*/ const vec2 &c_start, const vec2 &c_end, vec4 *FP6, const Origin *obj_space = nullptr)const;
//-----------------------------------------------------------------------------
void UpdateMat(bool set_mray_len_cn = true);
//-----------------------------------------------------------------------------
void reloc_at(const vec3 &p, const quat &r);
//-----------------------------------------------------------------------------
void Update_UI(const float &dt)override;
//----------------------------------------------------------------------------- projective screen vector
vec3 screen2world(float x, float y, float plane_dist)const;
//----------------------------------------------------------------------------- orthogonal screen vector
vec3 VRayMM(float mx, float my)const;
vec3 VRay(const float &x, const float &y)const;
//-----------------------------------------------------------------------------
bool Vis(const vec3 &pt)const;
int Vis(const vec3 &pt, float r)const;
//-----------------------------------------------------------------------------
//void Allign(const vec3 &idir){if(_Input->lmouse[1] && !_Input->mouse[2] && dot(mray.n,idir)>0.999){UpdateMat();rot=lookat(0.0,idir,UNIT_UP);UpdateMat();};};  //  pos=target_pos()-idir*(pos-target_pos()).len();	  _Input->lmouse[1] && !_Input->mouse[2] && 
void snap_at_eye_direction(const vec3 &idir, float min_angle);
//-----------------------------------------------------------------------------
vec3 Project(const vec3 &obj)const;
//-----------------------------------------------------------------------------
float screen_distance_to_mouse(const vec3 &pt)const;
void Fit(const Node *node, bool reset_ang = true, bool instant = true);
void Fit(const BBOX *box, bool reset_ang = true, bool instant = true);
//-----------------------------------------------------------------------------
//unproject==Vray
//-----------------------------------------------------------------------------
//////void GL()const{
//////	glMatrixMode(GL_PROJECTION);glLoadMatrixf(PM);
//////	glMatrixMode(GL_MODELVIEW);glLoadMatrixf(VM);
//////	glViewport(VP[0],VP[1],VP[2],VP[3]);
//////	//glDisable(GL_BLEND);// always by default?
//////}
//-----------------------------------------------------------------------------
void DrawAsOtherCamera(const vec3 &PlaneNormal = vec3(1, 0, 0), const vec3 &PlanePoint = vec3(0, 0, 0));
//-----------------------------------------------------------------------------
void Draw_2D(int border_size = 50, bool sel = false, bool drawM2daxis = true);
//-----------------------------------------------------------------------------
//soh cah toa -> s=o/h c=a/h t=o/a -> a=D o=(LL)
//return projected length(PL) of line(L) at distance(D) from camera
//float get_hfov_rad(float width, float len);
//float get_fov_deg(float width, float len);
//float get_width(float len, float hfovr);
float SP2SC(const float &Dist)const;
float getFrustumHeightAt(float dist)const;
float getDistanceFor(float frustumHeight)const;
float getFOVdeg(float frustumHeight, float dist)const;
INLINE float width()const;
INLINE float height()const;
float getAspect()const;
//-----------------------------------------------------------------------------  FD at end of "Scene.h"
void Draw_UI()override;/*{  FD at end of "Scene.h"
	Draw_2D();
	GL();
	SCN->Draw_from_cam(*this);
}*/
//-----------------------------------------------------------------------------
void Draw(const Camera &cam)override;
//-----------------------------------------------------------------------------
//bool insideLoop(vec2 p,vec2 A,vec2 B){//1div,1mul,3sub, 1xor,3and,2or,7cmp  vs clockwize()//2mul,7sub,1cmp
// bool rez=false;
// if((A.y<p.y && B.y>=p.y || B.y<p.y && A.y>=p.y) && (A.x<=p.x || B.x<=p.x)) rez^=(A.x+(p.y-A.y)/(B.y-A.y)*(B.x-A.x)<p.x);
// return rez;
//}
bool Point_in_PlaneBox(vec2 pt);
//-----------------------------------------------------------------------------
void glScreenQuad(float dist = -1);
//-----------------------------------------------------------------------------
void draw_lod_circles();
//-----------------------------------------------------------------------------
void ui_set_fov(UI_Panel *p);
void ui_set_near(UI_Panel *p);
void ui_set_far(UI_Panel *p);
//-----------------------------------------------------------------------------
void onGUI(UI_Panel *p)override;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};//end struct Camera::
//=============================================================================
#endif
