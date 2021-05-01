//=============================================================================
#ifndef __SCENE_H__
#define __SCENE_H__
//=============================================================================
//#include "BaseTypes.h"
#include "UI/UI.h" // widget
//#include "UI/UI_Panel.h"
struct Node;//#include "Scene/Node.h"
struct Mesh;//#include "Scene/Mesh.h"
struct Model;//FD //#include "Render/Model.h"
struct Texture;//FD //#include "Render/Texture.h"//struct Texture;//FD //
struct Camera;
//#include "Render/Material.h"
//#include "Render/Shader.h"
//#include "Core.h"
//#include "Sys/HashTable.h"
//#include "Sys/Tlist.h"
//#include "Sys/Thread.h"
#include "Sys/vector.h"
#include "Scene/Resource.h"// +str.h from "Sys/HashTable.h"
//=============================================================================
/// hold all visible/active resources in current timeframe
//=============================================================================
struct DLL_API Scene:UI_Widget{
	// Vector<!pointer!_to_stored_type> name;// else resize invalidate pointers
	Vector<Node*> nodes;// node has node_id to addressing this vector
	float FrameTime;// to pass animation delta_frame_time to objects, make it pointer?

	ResourceDB DB;
//-----------------------------------------------------------------------------
	Scene();
	~Scene();
//-----------------------------------------------------------------------------
	u32_t push(Node *ob);
//-----------------------------------------------------------------------------
	// sets ob->node_id link to RSide panel
	void reg(Node *ob);
	//called_from_destructor==true -> unreg() calls delete
	void unreg(Node *ob, bool called_from_destructor = false);
//-----------------------------------------------------------------------------
	void del(UI_Panel *p);
//-----------------------------------------------------------------------------
	Camera *cam();
	Model *model(u32_t idx);
//-----------------------------------------------------------------------------
	void Draw_from_cam(const Camera &cam);
//-----------------------------------------------------------------------------
	void Update_UI(const float &dt)override;
	void Draw_UI()override;
//-----------------------------------------------------------------------------
	void input_from_cam(Camera *cam);
//-----------------------------------------------------------------------------
	bool Intersect(Ray &r);
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------- resources
//-----------------------------------------------------------------------------
	bool load(const str &fname);
//-----------------------------------------------------------------------------
	Texture *get(u32_t idx);
//-----------------------------------------------------------------------------
	//used for runtime generated res:texture,mesh... (ex: to bind icons in gui)
	// second reg() will skip registration
	template<typename RESTYPE>
	void reg(RESTYPE *res, const str &file_name) {
		RESTYPE *rf = (RESTYPE*)DB.find(file_name);
		if (rf) LOG::err("alredy registered [%s]", file_name.text);
		if (rf == nullptr) {
			DB.add(res, file_name);
		}
	}
//-----------------------------------------------------------------------------
	template<typename RESTYPE>
	RESTYPE *create(const str &name){
		//RESTYPE *rf = (RESTYPE*) DB.find(file_name); ?
		RESTYPE *res = (RESTYPE*) new RESTYPE();
		DB.add(res, name);
		return res;
	}
//-----------------------------------------------------------------------------
	template<typename RESTYPE>
	bool find(const str &file_name, RESTYPE *&res) {
		res = (RESTYPE*)DB.find(file_name);
		return res != nullptr;
	}
	//-----------------------------------------------------------------------------
	template<typename RESTYPE>
	RESTYPE *get_load(const str &file_name) {
		RESTYPE *rf = (RESTYPE*) DB.find(file_name);
		if(rf) LOG::msg("Used instance for [%s]", file_name.text);
		if(rf == nullptr) {
			rf = new RESTYPE();
			if(rf->load(file_name)) {// <- if(_Plugins->run("Model", "Load", this, filename)){
				DB.add(rf, file_name);
			} else{
				RESTYPE *fb = (RESTYPE*) rf->fallback();
				delete rf;
				rf = fb;//(RESTYPE*)DB["error_???"];
			}
		}
		return rf;
	}
	//-----------------------------------------------------------------------------
};
//=============================================================================
#endif