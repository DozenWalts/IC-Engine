#ifndef __UI_PANEL_H__
#define __UI_PANEL_H__

#include "Sys/Str.h"
#include "UI/UI.h"

#include "Winnie/closure.h"
#include "Sys/vector.h"
#include "Sys/Tlist.h"
#include "Sys/HashTable.h"

struct DLL_API UI_Panel{//	sizeof()=248
	// 4*4*4+4+2=16*4+6=64+6=70
	UI_Panel *apx, *apy, *apxw, *apyh;// anchored panel pointer
	float  x,  y,  xw,  yh;			// local position
	float gx, gy, gxw, gyh;			// graphcis on screen position (read only)
	float sx, sy, sx_max, sy_max;	// scroll
	i8_t adx, ady, adxw, adyh;		// anchored panel direction [-1,0,1] [start ?mid end]
	bool  px, py, pxw, pyh;			// position in percents or pixels
	bool  fx, fy, fxw, fyh;			// frozen with anchored or not

	float VP[4];
	i32_t id;

	UI_Panel *Parent,*param;

	//hierachy
	typedef TPool<UI_Panel>::pnode pnode;
	Vector< pnode > childs_panel_node;

	//-------
	union{
		u16_t flags;
		struct { bool AutoUp : 1, vis : 1, CanMove : 1, Grapable : 1, filled : 1, Expanded : 1, Grappled : 1, GrapScroll : 1, group_edit_caption : 1; };
	};
	bool Down, AutoUpm, limit;// , scrollable;
	u8_t inm, style;//inm: 0-inside/outside, 1-isleft, 2-istop, 3-isright, 4-isbottom   //style:0-left, 1-center, 2-right
	u8_t type, switch_id;//switch_id for autoswitch downstate in groups with same parent
	str caption, name;//pointers???
	vec4 color;
	
	// reusable vars
	float stp, pos, emin, emax, val;
	int mul;

	//------ multiline word-wrapped text (?with idents?)
	//const char *visible_text_start;// TODO Use
	u32_t t_cur_pos, t_cur_sel;
	vec2 t_max;//text max x,y|w,h for render - reuse 'emin,emax'?
	float t_ident;// reuse 'stp'?
	//------
	//HashTable<str,FuncBase||CallbackBase> callbacks;?		 callbacks[str("use")|str("del")|str("update")|str("click")] = MakeCallback(x,x);	  callbacks[str("update")].run();
	//////typedef void (*UI_CallBack)(UI_Panel*);//cant use struct methods -> closure ?
	//////UI_CallBack onclick, onDel, onUpdate;// use_OC, use_MO, use_Alt;
	Closure<void(UI_Panel*)> onclick, onDel, onUpdate;//,onRclick;//ex: VAR->onclick=CLOSURE(this,&ImageTrain::UI_SEEK_click);
	//std::function<void()> void_lambda;
	void(*void_lambda)(UI_Panel *p);//? or void(*void_lambda)(UI_Panel *p,void *obj) as default
	//Variable Var;//pointer?
	//VirtOPCodes Var_OP;
	UI_Widget *Widget;//UI->P[i]->Widget=ColorPicker;
	struct Script *script;//Script script;//132 -> 380 script->push(var(MakeFunction()),"click"); script->run("click");
	//------------------------------------------------------------------------------
	void OnClick();
	//-----------------------------------------------------------------------------
	UI_Panel();
	UI_Panel(u8_t ntype, float nl, float nt, float nr, float nb);
	void set(float panel_x, float panel_y, float panel_xw, float panel_yh);
	void init(u8_t ntype, float nl, float nt, float nr, float nb, bool reinit = false);
	//-----------------------------------------------------------------------------
	UI_Panel *switch_tab(u32_t n_switch_id, bool down_state);
	//-----------------------------------------------------------------------------
	UI_Panel *edit_set(u8_t edit_type, float step, bool limiters = 0, float nemin = 0, float nemax = 0);
	//-----------------------------------------------------------------------------
	UI_Panel *set_caption(const char *cap, u8_t nstyle = 0);//style:0-left, 1-center, 2-right
	//-----------------------------------------------------------------------------
	//ex: VAR->assign(CLOSURE(this,&ImageTrain::UI_SEEK_click));
	UI_Panel *assign(Closure<void(UI_Panel*)> clsr);
	//-----------------------------------------------------------------------------
	UI_Panel *set_anchors(UI_Panel *left_px, UI_Panel *up_py, UI_Panel *right_pw, UI_Panel *down_ph);
	UI_Panel *set_anchors_dir(const i8_t &left_idx, const i8_t &up_idy, const i8_t &right_idw, const i8_t &down_idh);
	//-----------------------------------------------------------------------------
	float width()const { return gxw - gx; }
	float width_for_text()const;// text area - scroll width, if lines > height
	float height()const { return gyh - gy; }
	//-----------------------------------------------------------------------------
	float anchor_x()  { return (apx  ? (adx  < 0 ? apx->gx  : apx->gxw)  + (apx  == Parent ? apx->sx  : 0) : Parent->gx  + Parent->sx); }
	float anchor_y()  { return (apy  ? (ady  < 0 ? apy->gy  : apy->gyh)  + (apy  == Parent ? apy->sy  : 0) : Parent->gy  + Parent->sy); }
	float anchor_xw() { return (apxw ? (adxw < 0 ? apxw->gx : apxw->gxw) + (apxw == Parent ? apxw->sx : 0) : Parent->gxw + Parent->sx); }
	float anchor_yh() { return (apyh ? (adyh < 0 ? apyh->gy : apyh->gyh) + (apyh == Parent ? apyh->sy : 0) : Parent->gyh + Parent->sy); }
	//-----------------------------------------------------------------------------
	float to_screen_x(float loc_x)   { return (px  ? loc_x  * Parent->width()  : loc_x)  + anchor_x(); }
	float to_screen_y(float loc_y)   { return (py  ? loc_y  * Parent->height() : loc_y)  + anchor_y(); }
	float to_screen_xw(float loc_xw) { return (pxw ? loc_xw * Parent->width()  : loc_xw) + anchor_xw(); }
	float to_screen_yh(float loc_yh) { return (pyh ? loc_yh * Parent->height() : loc_yh) + anchor_yh(); }
	//-----------------------------------------------------------------------------
	float to_loc_x(float screen_x)   { return (screen_x  - anchor_x())  / (px  ? Parent->width()  : 1.0f); }
	float to_loc_y(float screen_y)   { return (screen_y  - anchor_y())  / (py  ? Parent->height() : 1.0f); }
	float to_loc_xw(float screen_xw) { return (screen_xw - anchor_xw()) / (pxw ? Parent->width()  : 1.0f); }
	float to_loc_yh(float screen_yh) { return (screen_yh - anchor_yh()) / (pyh ? Parent->height() : 1.0f); }
	//-----------------------------------------------------------------------------
	INLINE void sub_from_x(float v) { x += v; }
	INLINE void sub_from_w(float v) { xw -= v; }
	//-----------------------------------------------------------------------------
	INLINE UI_Panel *x_to_x(UI_Panel *P, float v = 0.0f) { adx = -1; apx = P; px = fabs(v) <= 1.0f; x = v; return this; }
	INLINE UI_Panel *x_to_w(UI_Panel *P, float v = 0.0f) { adx =  1; apx = P; px = fabs(v) <= 1.0f; x = v; return this; }
	INLINE UI_Panel *y_to_y(UI_Panel *P, float v = 0.0f) { ady = -1; apy = P; py = fabs(v) <= 1.0f; y = v; return this; }
	INLINE UI_Panel *y_to_h(UI_Panel *P, float v = 0.0f) { ady =  1; apy = P; py = fabs(v) <= 1.0f; y = v; return this; }
	//-----------------------------------------------------------------------------
	INLINE UI_Panel *w_to_x(UI_Panel *P, float v = 0.0f) { adxw = -1; apxw = P; pxw = fabs(v) <= 1.0f; xw = v; return this; }
	INLINE UI_Panel *w_to_w(UI_Panel *P, float v = 0.0f) { adxw =  1; apxw = P; pxw = fabs(v) <= 1.0f; xw = v; return this; }
	INLINE UI_Panel *h_to_y(UI_Panel *P, float v = 0.0f) { adyh = -1; apyh = P; pyh = fabs(v) <= 1.0f; yh = v; return this; }
	INLINE UI_Panel *h_to_h(UI_Panel *P, float v = 0.0f) { adyh =  1; apyh = P; pyh = fabs(v) <= 1.0f; yh = v; return this; }
	//-----------------------------------------------------------------------------
	INLINE UI_Panel *xy_to_xh(UI_Panel *P, float a, float b) { return x_to_x(P, a)->y_to_h(P, b); }
	INLINE UI_Panel *xy_to_xy(UI_Panel *P, float a, float b) { return x_to_x(P, a)->y_to_y(P, b); }
	INLINE UI_Panel *hw_to_hw(UI_Panel *P, float a, float b) { return h_to_h(P, -a)->w_to_w(P, -b); }
	INLINE UI_Panel *wh_to_xy(UI_Panel *P, float a, float b) { return w_to_x(P, a)->h_to_y(P, b); }
	INLINE UI_Panel *wh_to_wy(UI_Panel *P, float a, float b) { return w_to_w(P, a)->h_to_y(P, b); }
	//-----------------------------------------------------------------------------
	//default window
	INLINE UI_Panel *windowLU(UI_Panel *P, float offx, float offy, float nw, float nh) { return xy_to_xy(P, offx, offy)->w_to_x(this, nw)->h_to_y(this, nh); }
	//left down chat window
	INLINE UI_Panel *windowLH(UI_Panel *P, float offx, float offy, float nw, float nh) { return x_to_x(P, offx)->h_to_h(P, -offy)->w_to_x(this, nw)->y_to_h(this, -nh); }
	//right up window
	INLINE UI_Panel *windowRU(UI_Panel *P, float offx, float offy, float nw, float nh) { return w_to_x(P, -offx)->y_to_y(P, offy)->x_to_w(this, -nw)->h_to_y(this, nh); }
	//place right to source
	INLINE UI_Panel *AFTER(UI_Panel *P, float offx = 0.0f) { return x_to_w(P, offx)->y_to_y(P)->h_to_h(P)->lock(1 | 2 | 8); }
	//-----------------------------------------------------------------------------
	UI_Panel *right_to(UI_Panel *P, u8_t nd = 2) {//nd-number of divisions - 5 tabs 5 divs
		P->w_to_x(P, 1.0f / nd);
		return AFTER(P);
	}
	//-----------------------------------------------------------------------------
	INLINE UI_Panel *UNDER(UI_Panel *P, float offy = 0.0f, float height = 0.0f) { return xy_to_xh(P, 0.0f, offy)->w_to_w(P, 0.0f)->h_to_y(this, -height)->lock(1 | 2 | 4); }
	//-----------------------------------------------------------------------------
	INLINE UI_Panel *lock(u8_t flag);
	//-----------------------------------------------------------------------------
	UI_Panel *SubItem();
	//-----------------------------------------------------------------------------
	UI_Panel *last_child();
	//-----------------------------------------------------------------------------
	UI_Panel *width_by_caption();
	//-----------------------------------------------------------------------------
	void bind(UI_Widget *new_widget);
	//-----------------------------------------------------------------------------
	bool isVisible(float ty);
	//-----------------------------------------------------------------------------
	void Draw_mm_in_sides(float off);
	//-----------------------------------------------------------------------------
	vec3 scroll_params()const;
	//-----------------------------------------------------------------------------
	void draw_visible_scroll_area();
	void Draw();
	//-----------------------------------------------------------------------------
	void set_edit_val(float new_val);
	float get_edit_val();
	//-----------------------------------------------------------------------------
	bool Input();
	//-----------------------------------------------------------------------------
	bool inside(vec2 m);
	bool inside_all(vec2 m);
	bool inside_scroll(vec2 m);
	//-----------------------------------------------------------------------------  func icons zones FIZ (0..7) (7 total)
	void write_fiz(u8_t n);
	bool open_or_close();//read_fiz()==1
	bool isExpanded();
	bool isCollapsed();
	void Collapse(bool state = true);
	void in_test(vec2 m);
	//-----------------------------------------------------------------------------
	void update_VP(float *main_vp);
	//-----------------------------------------------------------------------------
	void update_text_box_size();
	//-----------------------------------------------------------------------------
	//if panel height are not fit in parent height-?y? - then set scroll size as diff
	void set_scroll_lim();
	void scroll_down();
	void ScrollDelta(float mdx, float mdy);
	void ScrollSet(float nsx, float nsy);
	//------------------------------------------------------------------------------
	pnode get_unused();
	void release(pnode child_panel);
	u32_t pool_size();
	//-----------------------------------------------------------------------------
	void hide(bool only_sub);
	void unhide();
	//-----------------------------------------------------------------------------
	pnode reuse_hidden();
	UI_Panel *ADD(u8_t ntype, const char *aname);
	UI_Panel *child(u32_t i);
	void DEL(u32_t child_panel_i);
	//-----------------------------------------------------------------------------
	void update_position();
	void enclose_subs();
	void sub_extent_to_scroll();
	bool occluded();
	//-----------------------------------------------------------------------------
};
#endif
