//=============================================================================
// USING vec2, vec3, vec4, mat4, utf8, script, closure, GL, Profiler, font
//=============================================================================
#ifndef __GUI_H__
#define __GUI_H__

//#include "BaseTypes.h"
#include "Math/Maths.h"

//=============================================================================
struct UI_Panel;//FD for GUI	& UI_Widget
struct Node;//FD
struct GlyphMap;// FD, pointer to _Render->Font
//=============================================================================
struct DLL_API GUI {
	UI_Panel *Main;// FD can be only as pointer
	UI_Panel *Grappled, *Focused;
	GlyphMap *Font;// pointer to _Render->Font

	vec4 VP;//viewport frame x,y,xw,yh
	vec4 Panel_color;
	vec4 Edit_color;
	vec2 mm, gmm;

	int Grappled_state;
	float border;

	enum UI { PANEL = 0, BUTTON, GROUP, CBOX, LIST, EDIT_T, EDIT_F, EDIT_i };
	enum text_align { left = 0, center, right };
	enum GRAP_STT { EMPTY, NONE, ONE, SCROLL_BAR, SCROLL_PANEL };
	//-----------------------------------------------------------------------------
	GUI();
	//-----------------------------------------------------------------------------
	~GUI();
	//-----------------------------------------------------------------------------
	void init();
	//-----------------------------------------------------------------------------
	void VP_set(int, int, int, int);
	//-----------------------------------------------------------------------------
	void switch_group(UI_Panel *p);
	//-----------------------------------------------------------------------------
	UI_Panel *find(const char *fname, UI_Panel *PT = nullptr);
	//-----------------------------------------------------------------------------
	void hide(UI_Panel *PT, bool only_subitems = false);
	//-----------------------------------------------------------------------------
	void get_panel_under_mouse(UI_Panel *PP, UI_Panel *&one);
	//-----------------------------------------------------------------------------
	void rec_move_side_with_frozen_x(UI_Panel *P, int idx, float valx);
	//-----------------------------------------------------------------------------
	void rec_move_side_with_frozen_y(UI_Panel *P, int idx, float valy);
	//-----------------------------------------------------------------------------
	void move_side(UI_Panel *P);
	//-----------------------------------------------------------------------------
	bool Input(const vec2 &mouse_pos);
	//-----------------------------------------------------------------------------
	void rec_Update(UI_Panel *PP, const float &dt);
	//-----------------------------------------------------------------------------
	void Update(const float &dt);
	//-----------------------------------------------------------------------------
	void rec_draw2(UI_Panel *P);
	//-----------------------------------------------------------------------------
	void draw();
	//-----------------------------------------------------------------------------
	UI_Panel *ADD(u8_t type, const char *name, UI_Panel *PT = nullptr);
	//-----------------------------------------------------------------------------
	UI_Panel *ADD_SUB(u8_t type, const char *name, UI_Panel *PT = nullptr);
	//-----------------------------------------------------------------------------
	UI_Panel *ADD_EDIT_FLOAT(UI_Panel *p, float *value);
	//-----------------------------------------------------------------------------
	//UI_Panel *ADD_EDIT_MAT4(UI_Panel *p, mat4 *mat);
	////-----------------------------------------------------------------------------
	//UI_Panel *ADD_EDIT_ORG(UI_Panel *p, Origin *org);
	//-----------------------------------------------------------------------------
	//UI_Panel *ADD_EDIT_NODE_TRANSFORM(UI_Panel *p, Node *node);
	//-----------------------------------------------------------------------------
	/*
	UI_Panel *Panel(const char *name, UI_Panel *PT);
	UI_Panel *Group(const char *name, UI_Panel *PT);
	UI_Panel *Button(const char *name, UI_Panel *PT);
	UI_Panel *CheckBox(const char *name, UI_Panel *PT);

	UI_Panel *EditFloat(const char *name, UI_Panel *PT);
	UI_Panel *EditText(const char *name, UI_Panel *PT);
	UI_Panel *EditInt(const char *name, UI_Panel *PT);

	UI_Panel *HTab(const char *name, UI_Panel *PT);
	UI_Panel *VTab(const char *name, UI_Panel *PT);
	UI_Panel *List(const char *name, UI_Panel *PT);

	UI_Panel *Slider(const char *name, UI_Panel *PT);
	*/
	//-----------------------------------------------------------------------------
	u32_t pool_size();
	//-----------------------------------------------------------------------------
};
//=============================================================================
struct DLL_API UI_Widget {// render to viewport
	float *VP;// int?
	UI_Panel *panel;

	UI_Widget() { VP = nullptr; panel = nullptr; }
	virtual ~UI_Widget() {}//= 0;//
	//------------UI_Widget virtuals to override
	//glVertex2f(VP[0]	  ,WIN.H-VP[1]	  );// upper left point
	//glVertex2f(VP[0]+VP[2],WIN.H-VP[1]-VP[3]);// lower right point
	virtual void Draw_UI() { }
	virtual void Update_UI(const float &dt) {}
	virtual void Input_UI() {}
	//virtual void OnReg_UI(){};
};
//=============================================================================
//extern GUI UI;
//=============================================================================
#endif
