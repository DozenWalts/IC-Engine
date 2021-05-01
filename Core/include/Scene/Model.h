#ifndef __MODEL_H__
#define __MODEL_H__
//=============================================================================
#include "Sys/DLL_API.h"
#include "Node.h"
//=============================================================================
//struct Component{
//	char name[32];// and id
//	Component(){};
//	virtual void onInit(){ LOG::msg("Component::onInit"); };
//	virtual void onDel() = 0;
//	virtual void onEdit(const Camera &cam) = 0;
//	virtual void onDraw(const Camera &cam) = 0;
//	virtual void onUpdate(const Camera &cam) = 0;
//	virtual void onGUI(UI_Panel *p) = 0;
//};
//=============================================================================
struct DLL_API EditModel{
    struct Model *md;//FD
	struct Mesh *m;//FD
	//---------------------------------- editor

	enum TOOL{FREE=0, CREATE, SELECT};// MOV,ROT,SCL -> Gizmo
	u32_t edit_tool;

	enum   EM{NONE=0, VERT, UV, FACE, EDGE, BONE, ANIM, CURVE, SURF, SPRITE, FIGURE, MAT, TEX};
	u32_t edit_mode, uv_cur_tex;

	enum   FM{TEXTURED=0, WIREFRAME, FLAT, SMOOTH};
	u32_t face_mode;

	union{
		u32_t draw_stt;
		struct{bool DRAW_VERTS:1, DRAW_VN:1, DRAW_FACES:1, DRAW_FN:1, DRAW_EDGES:1, DRAW_OPEN_EDGES:1, DRAW_UV_SEAMS:1, DRAW_BONES:1,
			DRAW_S:1, DRAW_SL:1, DRAW_FIG:1, DRAW_SPR:1, DRAW_CURVES:1, DRAW_UV_F:1, DRAW_UV_B:1, DRAW_BAUV:1, 
			DRAW_TBN:1, DRAW_WIRE:1, dflag_32:1, dflag_33:1, dflag_34:1, dflag_35:1, dflag_36:1, dflag_37:1,
			dflag_40:1, dflag_41:1, dflag_42:1, dflag_43:1, dflag_44:1, dflag_45:1, dflag_46:1, dflag_47:1;};
	};

	union{
		u16_t config;
		struct{bool fixed_bone_length:1, ANIMATE:1, TriAutoHelp:1, TriOrQuad:1;};
	};
	
	enum SM{DESEL=0, SEL_ALL, RANGE, SEL_3D, SEL_2D, SEL_ADJ, PICK, BYVERT};//DESEL-unused?
	enum STT{NON=0, SEL, HID, DEL};// DEL now unused, delete inplace
	u8_t *SF,*SQF,*SV,*SB,*ST,*SFIG;//select states
	u32_t sel_v, sel_f, sel_q, sel_b, sel_t, sel_c, sel_fig;

	u8_t RTvsP;
	Face4 RTvs, LRTvs;//triangles & quads, sel vertex 
	u32_t ip_fi[2];
	u32_t RTbs, RTbss;//,LRTbs;// to pick a bones ? unused
//-----------------------------------------------------------------------------
	void swapV(u32_t i,u32_t j);
	void resizeV(u32_t nmv, bool clearall = 0);
	void resizeF(u32_t nmf, bool clearall = 0);
	void resizeQ(u32_t nmq, bool clearall = 0);
	void resizeB(u32_t nmb, bool clearall = 0);
	void resizeSSF(u32_t nms, bool clearall = 0);
//-----------------------------------------------------------------------------
    EditModel(Model *nmd);
	void reinit(Model *nmd);
	~EditModel();
	void DrawSeams();
    void Draw(const Camera &cam);
	void Edit(Camera *cam);
	void Update(float dt);
//----------------------------------------------------------------------------- Editor code
	void ED_CREATE(u8_t MODE, vec3 add_pos, Face4 add_face);
	void ED_DELETE(u8_t MODE);
	void ED_SELECT(u8_t EDIT_MODE, u8_t SELECT_MODE, u8_t State,const vec4 *FR);
    void setEditMode(u8_t new_EM);
    void setTool(u8_t new_Tool);
//-----------------------------------------------------------------------------
	void onGUI(UI_Panel *p);
};
//=============================================================================
//=============================================================================
//=============================================================================
struct DLL_API Model final: Node {
	struct Mesh *mesh;//FD
	struct FFP *vbo;//FD
    EditModel *em;
	//---------------------------------- bone (transformed)
	struct Skeleton *skel;
	vec3 *V, *VN;// skinned vertex, vertex_normal
//-----------------------------------------------------------------------------
	Model(const char *model_name = nullptr);
	~Model();
//-----------------------------------------------------------------------------
	//bool Load(const char *model_name);
	void BakeMesh();
	void BakeVerts();
//-----------------------------------------------------------------------------
	void Draw(const Camera &cam);
	bool Edit(Camera *cam);
	void Update(float dt);
//-----------------------------------------------------------------------------
	void Bound();
	bool intersectFaces(Ray &local_mray, u32_t *face_idx = nullptr);
	bool Intersect(Ray &r);
//-----------------------------------------------------------------------------
	void onGUI(UI_Panel *p);
//----------------------------------------------------------------------------- Resource
	//void init() {}
	bool load(const str &filename);
	bool save(const str &filename);
	void save(XML *xml);
	void load(const XML *xml);
	static const Resource *fallback();
	u32_t res_type() const{ return Resource::MODEL; }
	static u32_t node_type_id;
};
//=============================================================================
#endif