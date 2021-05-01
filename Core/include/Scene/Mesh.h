#ifndef __MESH_H__
#define __MESH_H__

#include "Sys/DLL_API.h"
#include "Sys/HashTable.h"
#include "Sys/Buffer.h"
#include "Math/Maths.h"
#include "Scene/Resource.h"

struct DLL_API HalfEdge {//4*6=24
	u32_t vi, fi, fj;
	HalfEdge *next, *twin, *prew;
	HalfEdge *next_face() { return twin ? twin->next : NULL; }
	HalfEdge *prev_face() { return prew ? prew->twin : NULL; }//	->twin
	HalfEdge *rewind() {//around single vetex - rewind back once, or till twin==null - if crack then count only first and last edges
		HalfEdge *he = this;
		while(he->prev_face()) {
			he = he->prev_face();
			if(he == this)break;
		}
		return he;
	}
};

//void INLINE static classifyEdge(const std::pair<uint32_t, uint32_t> &e,	std::set<std::pair<uint32_t, uint32_t>> &out)
//{
//	auto it = out.insert(e);
//	if (!it.second) {
//		out.erase(it.first);
//	}
//}
//bool EdgeBuilderPrivate::buildExternalEdges(const glm::uvec3 *faces, const size_t &size)
//{
//	m_edges.clear();
//	for (size_t i = 0; i < size; i++) {
//		const auto &f = faces[i];
//		classifyEdge({ f[0], f[1] }, m_edges);
//		classifyEdge({ f[1], f[2] }, m_edges);
//		classifyEdge({ f[2], f[0] }, m_edges);
//	}
//
//	return true;
//}
//=============================================================================
struct VertBone8 {
	union {
		struct { vec4 v; };
		struct { u8_t bi[8], w[8]; };
	};
	VertBone8(u8_t mbi, int *id, float *w01) {
		assert(sizeof(vec4) == sizeof(VertBone8));
		memset(v, 0, sizeof(vec4));// vec4_zero?
		assert(mbi <= 8);
		loop0i(mbi) {
			bi[i] = id[i];
			w[i] = round(w01[i] * 255.0f);
		}
		weightSort();
	}
	void weightSort() {
		//LOG::msg("pre sort [%i %i %i %i  %i %i %i %i] [%i %i %i %i  %i %i %i %i]", bi[0], bi[1], bi[2], bi[3], bi[4], bi[5], bi[6], bi[7], w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7]);
		//void insertionSort(int arr[], int n)
		int i, key, key2, j;
		for (i = 1; i < 8; i++) {

			key = w[i];
			key2 = bi[i];
			j = i - 1;

			while (j >= 0 && w[j] < key) {
				w[j + 1] = w[j];
				bi[j + 1] = bi[j];
				j = j - 1;
			}
			w[j + 1] = key;
			bi[j + 1] = key2;
		}

		key = 0;loop0i(8) key += w[i];//reminder
		if (key != 0xff) {
			///LOG::msg("post sort [%i %i %i %i  %i %i %i %i] [%i %i %i %i  %i %i %i %i] reminder %i(%i)", bi[0], bi[1], bi[2], bi[3], bi[4], bi[5], bi[6], bi[7], w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7], 0xff - key, key);
			if(key != 0xff)w[0] += (0xff - key);
		}
	}
	//u8_t id(u8_t i)const{ return bi[k]; }
	//operator vec4 &(){ return v; }
	float weight(u8_t i){ return 255.0f / w[i]; }
};
//=============================================================================
struct DLL_API Mesh final : Resource {
	//------------------------------------- unique vertices index
	struct vert_uv {//20
		vec3 v;
		vec2 uv;
		vert_uv() {}
		vert_uv(vec3 nv, vec2 nuv) { v = nv; uv = nuv; }
		bool operator == (const vert_uv &ov) { 
			//return (v.x == ov.v.x && v.y == ov.v.y && v.z == ov.v.z  
			//	&&  uv.x == ov.uv.x && uv.y == ov.uv.y);
			return equal(v.x, ov.v.x) && equal(v.y, ov.v.y) && equal(v.z, ov.v.z)
				&& equal(uv.x, ov.uv.x) && equal(uv.y, ov.uv.y);
		}
	};
	HashTable<vert_uv, u32_t> VV;
	typedef HashTable<vert_uv, u32_t>::node vv_t;
	//------------------------------------- unique vertices index

	//------------------------------------- vertices
	u32_t mv;//max vertices
		vec3 *v, *vn, *vt, *vb;//quat *tbn;?
		//u8_t mtc;//max texture coord
		// vec2 **t;//t[mtc][mv]
		///u8_t uv_layers;//t[vi + uv_lay*mv] - no, t[vi+uv_channel]
		vec2 *t;//several uv's?? as material layers
		u8_t *dvm;
			u32_t **DV;//dupe vert_id for each vert	? or VVI?
		u8_t *mbi;
			int **bi;
			float **w;
		VertBone8 *idwt8;// alternative bi + w
	//------------------------------------- triangle faces
	u32_t mf;//max triangle faces
		Face3 *f;
		vec3 *fn;
	//------------------------------------- quad faces
	u32_t mqf;//max quad faces
		Face4 *qf;
		vec3 *qfn;
	//------------------------------------- face edges (tri+quad) -> now hash_table_edge_index E
	//u32_t me;//max edges
	//	Edge *E;
	//	Face4 *FEi;
	//	int *Eflag;
	HashTable<u64_t, u32_t> E;// edge_index = (min(vi_a,vi_b) | (max(vi_a,vi_b) << 32))
	typedef HashTable<u64_t, u32_t>::node edge_t;
	//------------------------------------- half edges (tri+quad)
	u32_t mhe;//max half edges	   TF*3 + QF*4
		HalfEdge *HE;// (E=F+V-2)*24 + V*8*4 -> 1k verts = 1k*(2*24 + 32) = 80k
		HalfEdge **F2HE;// links only [mf+mqf] - link to start halfedge	   1k faces = 4k mem for he links
		HalfEdge **V2HE;// links only [mv] - 1k verts = 4k mem for he links
		//HalfEdge **E2HE;// edges only			  E=F+V-2;
	//------------------------------------- triangle strips - wip
	//u32_t mts;//max tri-strip
		//u32_t *ts;//triangle strip
	//------------------------------------- bones
	HashTable<str, u32_t> bone_index;// bm[ bone_index["head"] ]=mat4(...);
	u8_t mb;//max bones 256
		str *bname;//bone name - ?unordered_map?	<- remove? now SIHT hold str's
		Origin *b;//vec3 *bv,*ba,*bs;
		int *p;//bone parent
	//------------------------------------- materials
	u8_t mm;//max materials 256 mm==mr
		str *mname;//meterial name
		u8_t *mmt;//max material texture layers
		u8_t **msi;//material shader index - several shaders ?shader for each layer?
		u8_t **mti;//material texture [index][layer]
	//------------------------------------- face regions
	u16_t mr;//max regions, mm==mr
		u32_t *num_reg_tris, *num_reg_quads;//face texture index offset - mr: max_regions
		u8_t *mat_id;//index 0..mmt to mti[index][layer]
		//u32_t *rofs;? half edges??
	//------------------------------------- textures
	u16_t mt;//max mesh textures(names) txn[mt]
		//u16_t *ti; removed, now all faces sorted in order of texture index -> now sorted by materials
		str *txn;
	//------------------------------------- animations
	u8_t ma;//max animations
		struct SkelAnim **ani;
	//------------------------------------- ResMan id
	u32_t id;//res_man id
	//--------------------------------------------------------------------------------------
	Mesh() { init(); }
	~Mesh() { del(); }
	void init();
	void del();
	//--------------------------------------------------------------------------------------
	u32_t push_tex(const char *tex_name);
	void push_mat_ts_idx(u8_t mid, u8_t txi = 0, u8_t shi = 0);
	void push_mat(const char *mat_name);
	void push_a();
	//--------------------------------------------------------------------------------------
	void swapV(u32_t i, u32_t j);
	void swapF(u32_t i, u32_t j);
	//--------------------------------------------------------------------------------------
	void resizeA(u8_t nma);
	void resize_skinning_weigts(int nmv, int start_v = 0);
	void resizeVb(u32_t vi, u32_t nmb);
	void resizeV(u32_t nmv, bool clearall = 0);
	void resizeQF(u32_t nmf, bool clearall = 0);
	void resizeF(u32_t nmf, bool clearall = 0);
	void resizeB(u32_t nmb, bool clearall = 0);
	void resizeT(u32_t nmt, bool clearall = 0);
	void resizeM(u32_t nmm, bool clearall = 0);
	void resizeMmt(u32_t mid, u32_t nmmt);
	void resizeR(u32_t nmr, bool clearall = 0);
	//--------------------------------------------------------------------------------------
	void add_face(const Face4 &add_face, bool build_edges_renormal);
	//--------------------------------------------------------------------------------------
	bool query_vertex(const vec3 &iv, const vec2 &uv, u32_t &index, bool store=false);
	bool uv_split(vec2 uv, u32_t f_id, u32_t f_v_id, u32_t v_id);
	//--------------------------------------------------------------------------------------
	void setup_HE_face(u32_t he_i);
	//--------------------------------------------------------------------------------------
	u32_t getEdge(const u64_t &vi_a, const u64_t &vi_b);
	//--------------------------------------------------------------------------------------
	void setEdge(const u32_t edge_index, const u64_t &vi_a, const u64_t &vi_b);
	//--------------------------------------------------------------------------------------
	void same_vert_face();
	//--------------------------------------------------------------------------------------
	void zero_area_face();
	//--------------------------------------------------------------------------------------
	void BuildEdges();
	//--------------------------------------------------------------------------------------
	bool Load(BUFFER *B);
	void LoadEM7(BUFFER *B);
	bool LoadEMDL(BUFFER *B);
	//--------------------------------------------------------------------------------------
	void SaveEMDL(BUFFER *B);
	//--------------------------------------------------------------------------------------
	void Sphere(u32_t R, u32_t S);
	void Cylinder(u32_t R, u32_t S, bool caps);
	void Torus(u32_t R, u32_t S, float r);
	void ReTorus(u32_t R, u32_t S, float r);
	void plane(u32_t x = 0, u32_t y = 0);
	void Box(u32_t x=0, u32_t y=0, u32_t z=0);
	//--------------------------------------------------------------------------------------
	void create_Tex_Mat_Reg();
	//--------------------------------------------------------------------------------------
	vec3 CenterOrigin();
	void transform(const mat4 &t);
	//--------------------------------------------------------------------------------------
	void setDupeVerts();
	//--------------------------------------------------------------------------------------
	static void calcTangentBasis(const vert_uv &v0, const vert_uv &v1, const vert_uv &v2, vec3 &t, vec3 &b, vec3 &n);
	void splitSharpEdges();
	void ReNormal();
	//--------------------------------------------------------------------------------------
	void FlipFaces();
	//--------------------------------------------------------------------------------------
	void Zup_to_Yup();
	//----------------------------------------------------------------------------- Resource
	//void init() {}
	bool load(const str &filename);
	bool save(const str &filename);
	static const Resource *fallback();
	u32_t res_type() const{ return Resource::MESH; }

};
#endif
