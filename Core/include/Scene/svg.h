#ifndef __SVG_H__
#define __SVG_H__

#include "Sys/DLL_API.h"
#include "Sys/Buffer.h"
#include "Sys/vector.h"

#include "Math/Maths.h"

#include "Scene/Node.h"

struct Camera;//FD

//struct DLL_API curve_point {// 36|48
//	//vec2 t1, v, t2;// 2*3*4=24
//	vec3 t1, v, t2;// 3*3*4=36
//	u32_t c;// color
//	float w;// width
//	struct state { u32_t st1 : 3, st2 : 3, sel : 2; } stt;
//};

struct DLL_API Shape{
	Vector<vec3> v;// vec3 ? vec4?
	Vector<u8_t> f;// Mm Ll Hh Vv Qq Ss Tt Cc Aa Zz	  <- packed_struct{u8 type;u24 v_id;}
	str name;
	u32_t fill_color;
	u32_t line_color;
	//struct FFP *vbo;//FD
	union{
		u32_t flags;
		struct{ bool filled : 1, looped : 1; };
	};

	Shape();
	~Shape(){}
	void move_to(vec2 p);
	void line_to(vec2 p);
	void cubic_to(vec2 p1, vec2 p2, vec2 p3);
	void quadric_to(vec2 p1, vec2 p2);
	void circle(vec2 pos, float r);
	void draw()const;
};
/*
struct DLL_API Shape {
	Vector<u32_t> vi;
	u8_t type;// point, line, quadric, cubic, circle, rect, poly
	union{
		u32_t flags;
		struct{u8_t f_closed:1,f2:1,f3:1,f4:1,f5:1,f6:1,f7:1,f8:1;};
	};
};

struct DLL_API Figure {
	str *name;
	Vector<Shape> s;
};

*/

struct DLL_API SVG final : Node {
	Vector<Shape*> shp;//shapes
	//Vector<Origin> v;
	//Vector<Figure> f;
	//Skeleton *bones;
	struct EditSVG *em;

	SVG(const char *nname = nullptr);
	~SVG();
	void del(u32_t d_id);
	void Draw(const Camera &cam);
	u32_t Bake(u32_t w, u32_t h);
	//static void ArcToCubic(Shape *sh, vec2 x1, vec2 r, float ang, bool big_arc, bool sweep_dir, vec2 x2);
	static u32_t parse_color(const char* str);
	Shape *add_shape();
	void parse_path(const char *path, u32_t fillcolor);
	void parse_node(const struct XML *xml, u32_t fillcolor);
	void Bound();
	void onGUI(UI_Panel *p);// Node
	virtual bool Edit(Camera *cam);
	//virtual void Update(float dt){}
	//----------------------------------------------------------------------------- Resource
	//void init() {}
	bool load(const str &filename);
	bool save(const str &filename);
	static const Resource *fallback();
	u32_t res_type() const{ return Resource::SVG; }
	static u32_t node_type_id;
};

struct EditSVG {
	SVG *svg;
	Shape *shp;

	enum SM{ DESEL = 0, SEL_ALL, RANGE, SEL_3D, SEL_2D, SEL_ADJ, PICK, BYVERT };//DESEL-unused?
	enum STT{ NON = 0, SEL, HID, DEL };// DEL now unused, delete inplace
	u8_t *SV, *SS, ccnt;
	u32_t sel_v, sel_s;

	enum TOOL { FREE = 0, CREATE, SELECT };
	u32_t tool;

	enum EM { NOEDIT = 0, VERT, SEG, PATH, LINE, QUADRIC, CUBIC, RECT, CIRCLE, POLY };
	u32_t edit_mode;

	EditSVG(SVG *s);
	void reinit(SVG *s);
	void reinit(Shape *s);
	~EditSVG();

	void Draw(const Camera &cam);
	bool Edit(Camera *cam);
	void Update(float dt);
	void onGUISVG(UI_Panel *p);
	void onGUIShape(UI_Panel *p);

	void ED_CREATE(u8_t MODE, vec3 add_pos);
	void ED_DELETE(u8_t MODE);
	void ED_SELECT(u8_t EDIT_MODE, u8_t SELECT_MODE, u8_t State, const vec4 *FR);
	void setEditMode(u8_t new_EM);
	void setTool(u8_t new_Tool);
};


#endif