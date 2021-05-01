#ifndef __FFP_H__
#define __FFP_H__

#include "BaseTypes.h"
#include "Math/Maths.h"
//#include "Render/Render.h"
#include "Render/Shader.h"
#include "Render/Material.h"
#include "Sys/HashTable.h"
#include "Sys/vector.h"

struct DLL_API FFP{

	struct layout{// 4b=16 for primitives, 4b for vbo_layout
		union{
			u8_t data;
			struct{ u8_t primitive : 4, vbo_lay : 4; };
		};
		layout(u32_t mode, u8_t vbo_layout){ primitive = mode;vbo_lay = vbo_layout; }
		layout(u8_t lay){ data = lay; }
	};

	enum VBO_LAYOUT{
		NONE=0,
		VC,
		VCT,
		VTN,
		VTNTB
	};

	struct batch{//	vbo buffer
		layout vbo_lay;// primitive mode, quad/tri/pt/ln
		Vector<float> vbo;// VC,VTN,VCT,VTN_L
		Vector<u32_t> ebo;// vertex index for primitive, short/uint ?
		//-----------------------------------------------------------------------------
		batch(layout lay):vbo(),ebo(),vbo_lay(lay){
		}
		~batch(){
		}
		//-----------------------------------------------------------------------------
		void push_vc(const vec3 &V, const vec4 &C);
		void push_vct(const vec3 &V, const vec4 &C, const vec2 &T);
		void push_vtn(const vec3 &V, const vec2 &T, const vec3 &N);
		void push_vtntb(const vec3 &V, const vec2 &UV, const vec3 &N, const vec3 &T, const vec3 &B);
	};

	struct dip{// info to draw from single buffer
		//mat4 M;?
		u32_t start_off;// start vbo offset
		u32_t end_off;// end vbo offset
		//u32_t elems;// vbo elements count
		u32_t mode;// primitive mode, quad/tri/pt/ln
		//u8_t elems;// primitive elements, quad = 4
		//u8_t itype;// index_type, short/uint
		u8_t vsz;// vertex struct size
		u8_t isz;// index struct size

		u16_t tid;// material id
		Material *material;

		dip() {
			tid = 0;material = nullptr;
			start_off = end_off = mode = 0;
			vsz = isz = 0;
		}
		~dip() {
			//DELETE(material);
		}
	};

	// global buffers
	u32_t mv, memv;// VBO
	float *v;// VC,VTN,VCT,VTN_L
	u32_t mi, memi;// EBO
	u32_t *idx;// vertex index for primitive, short/uint ?

// for runtime bake optimization; material index to mats[mti[i]].on/off() of each primitive,
// to sort verts/idx at bake by same mats (to have less mat switches -> less dips)
	Vector<u32_t> mti;

	Vector<Material*> mats;// unique materials
	HashTable<str, u32_t> mat_name2id;
	typedef HashTable<str, u32_t>::node mat_name2id_node;

	Vector<batch*> batches;// multi vbo buffer
	HashTable<u32_t, u32_t> mat2batch;// mat_id to batch_id
	typedef HashTable<u32_t, u32_t>::node mat2batch_node;

	//		  mat_id, dc
	Vector<dip*> dips;// draw calls single vbo buffer

	u32_t va_id, prog_id, mat_id, vb_id, ib_id;
	u16_t num_attribs, ssz;
	u32_t stride, tmp_vap_off, ib_type;

	Shader *shader;

	// attributes uniform ids
	int MVP_uid = 0;
	int campos_uid = 0;
	int vp_uid = 0;
	int model_mat_uid = 0;
	int light_pos_uid = 0;

	int primitive;

	vec4 color;
	//-----------------------------------------------------------------------------
	FFP();
	~FFP();
	//-----------------------------------------------------------------------------
	void init(int draw_mode = 0, int new_stride = 0);
	void setupVC(int gl_primitive);
	void setupVCT(int gl_primitive);
	void setupVTN(int gl_primitive);
	void setupVTN_L(int gl_primitive);
	void clear();
	//-----------------------------------------------------------------------------
	void bind_begin(u32_t sizeofstruct = 0);
	void bind_vap(u32_t num_elements);// internal
	void bind_vertexbuf(const void *vert_ptr = 0, u32_t vert_num = 0);
	void bind_update_vertexbuf(const void *vert_ptr = 0, u32_t vert_num = 0);
	void bind_indexbuf(const void *idx_ptr, u32_t idx_num, u32_t idx_sizeof_type);
	void bind_end();
	//-----------------------------------------------------------------------------
	u32_t findMaterial(const str *name);
	u32_t addMaterial(Material *mat);
	batch *getBatch(u32_t mat_id, layout lay);
	//-----------------------------------------------------------------------------
	dip *get_dip(u32_t material_id);
	void sortByMaterials();
	Material *add_surface(Texture *region_texture = nullptr);
	u32_t add_surface_mat(Material *region_mat/* = nullptr*/);
	dip *get_last() { return dips.size ? dips[dips.size - 1] : nullptr; }
	//-----------------------------------------------------------------------------
	void draw(const mat4 &org);
	//void draw_dip(const mat4 &org, u32_t dip_id, u32_t i_start, u32_t i_end);
	//-----------------------------------------------------------------------------
	void reserve_v(const u32_t &nmv);
	void resize_v(const u32_t &nmv);
	void resize_i(u32_t nmf);
	//-----------------------------------------------------------------------------
	INLINE void push_vc(const vec3 &V, const vec4 &C);
	INLINE void push_vct(const vec3 &V, const vec4 &C, const vec2 &T);
	INLINE void push_vtn(const vec3 &V, const vec2 &T, const vec3 &N);
	INLINE void push_vtntb(const vec3 &V, const vec2 &UV, const vec3 &N, const vec3 &T, const vec3 &B);
	INLINE void update_vtntb(const vec3 *V, const vec2 *UV, const vec3 *N, const vec3 *T, const vec3 *B);
	//-----------------------------------------------------------------------------
	//void dupe(u32_t i=U32_MAX);
	u32_t last();
	//float *vertex(u32_t i,int ssz);
	//void dupe_vert(u32_t i=U32_MAX);
	//-----------------------------------------------------------------------------
	void box(const vec3 &s);
	//-----------------------------------------------------------------------------
	void point(const vec3 &a, const vec4 &color, u32_t style);
	void line(const vec3 &a, const vec3 &b, const vec4 &color, u32_t style);
	void quad(const vec2 &mn, const vec2 &mx, const vec4 &color, const vec4 *uv = nullptr);
	void quad(const vec2 &a_uv, const vec3 &a,
		const vec2 &b_uv, const vec3 &b,
		const vec2 &c_uv, const vec3 &c,
		const vec2 &d_uv, const vec3 &d, const Texture *tex = nullptr);
	void quad(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec4 &color, const vec4 *uv = nullptr);
	void quad2d(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d, const vec4 &color, const vec4 &uv);
	void triangle(const vec3 &a, const vec3 &b, const vec3 &c, const vec4 &color);
	void triangle(
		const vec2 &a_uv, const vec3 &a, 
		const vec2 &b_uv, const vec3 &b,
		const vec2 &c_uv, const vec3 &c, const Texture *tex = nullptr);
	//-----------------------------------------------------------------------------
};
#endif
