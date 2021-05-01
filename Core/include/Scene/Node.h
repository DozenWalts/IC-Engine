#ifndef __NODE_H__
#define __NODE_H__
//=============================================================================
#include "Math/Maths.h"
#include "Sys/vector.h"
#include "Sys/XML.h"
#include "Resource.h"
//=============================================================================
struct Camera;//FD
//=============================================================================
// template
//virtual ~Node(){}
//virtual void Draw(const Camera &cam);
//virtual bool Edit(Camera *cam);
//virtual void Update(float dt){}
//virtual void Controll(Camera *cam){}
//virtual bool Intersect(Ray &r);
//virtual void Bound();
//virtual void onGUI(UI_Panel *p);
//virtual void update_transform(){}
DLL_API u32_t getNodeTypeId(str type_name, struct FunctionBase *func);
//=============================================================================
struct DLL_API Node : Resource {//
	
	Origin local;//call node.setLocal(); after modify
	Origin global;//call node.setGlobal(); after modify
	Origin inv_global;// readonly

	str *name;
	Node *parent;
	Vector<Node*> childs;

	u32_t bboxnum;
	BBOX *bbox;
	// u32_t **divs;
	//Vector<u32_t> list;

	struct Script *script;//FD

	//enum TYPE{	  Resource had it
	//	EMPTY = 0,
	//	MODEL = 1,
	//	SVG = 2
	//};
	u32_t type;

	enum STT{
		NONE   = 0,
		SEL    = 1,
		HID    = 2,
		DEL    = 4,
		PHYS   = 8,
		UNUSED = 16,
		EDIT   = 32,
		FROZEN = 64,
		DEBUG  = 128
	};
	u32_t state;

	u32_t node_id;
	struct UI_Panel *panel, **transform_ui;
//-----------------------------------------------------------------------------
bool   is(u32_t s){return BITMASK_CHECK(state,s)!=false;};
void  set(u32_t s){BITMASK_SET(state,s);};
void flip(u32_t s){BITMASK_FLIP(state,s);};
void  clr(u32_t s){BITMASK_CLEAR(state,s);};
//-----------------------------------------------------------------------------
Node(const char *nm = NULL);
virtual ~Node(){}
//-----------------------------------------------------------------------------
void setEdit(bool sst){if(sst){set(STT::EDIT);}else{clr(STT::EDIT);}}
//-----------------------------------------------------------------------------
void Select(bool sst){if(sst){set(STT::SEL);}else{clr(STT::SEL);}}
//-----------------------------------------------------------------------------
virtual void Draw(const Camera &cam);
// return if edit happens to block further editing
virtual bool Edit(Camera *cam);
virtual void Update(float dt){}
virtual void Controll(Camera *cam){}
//-----------------------------------------------------------------------------
virtual bool Intersect(Ray &r);
virtual void Bound();
//-----------------------------------------------------------------------------
virtual void onGUI_ADD_MENU(UI_Panel *p);
//-----------------------------------------------------------------------------
virtual void onGUI(UI_Panel *p);
//-----------------------------------------------------------------------------
void setLocal(const Origin *new_local = nullptr);
//-----------------------------------------------------------------------------
void setGlobal(const Origin *new_global = nullptr);
//-----------------------------------------------------------------------------
virtual void update_transform();
//-----------------------------------------------------------------------------
const Origin &getTransform(bool islocal=true){
	return (islocal || !parent) ? local : global;
}
////-----------------------------------------------------------------------------
//void setParent(Node *new_parent) {
//	if(parent == new_parent || new_parent == NULL) return;
//	if(parent) parent->removeChild(this);
//	parent = new_parent;
//	parent->childs.append(this);
//	setTransform(getTransform());
//} 
//-----------------------------------------------------------------------------
Node *getRoot() {
	Node *ret = this;
	while (ret->parent) ret = ret->parent;
	return ret;
}
//-----------------------------------------------------------------------------
void addChild(Node *node) {
	if(childs.find(node) != childs.end()) return;
	if(node->parent) node->parent->removeChild(node);
	node->parent = this;
	childs.append(node);
	node->setLocal();
} 
//-----------------------------------------------------------------------------
void removeChild(Node *node) {
	loop0i(childs.size){
		if(childs[i] == node) {
			node->parent = NULL;
			childs.remove(i);
			node->setLocal();//Transform(node->getTransform());
			return;
		}
	}
} 
////-----------------------------------------------------------------------------
//int isChild(const Node *node) const {
//	for(int i = 0; i < childs.size(); i++) {
//		if(childs[i] == node) return 1;
//	}
//	for(int i = 0; i < childs.size(); i++) {
//		if(childs[i]->isChild(node)) return 1;
//	}
//	return 0;
//} 
////-----------------------------------------------------------------------------
//int findChild(const char *name) const {
//	if(name == NULL) return -1;
//	for(int i = 0; i < childs.size(); i++) {
//		if(!strcmp(name,childs[i]->name->text)) return i;
//	}
//	return -1;
//}
////-----------------------------------------------------------------------------
//Node *getChild(int num) const {
//	assert(num >= 0 && num < childs.size() && "Node::getChild(): bad child number");
//	return childs[num];
//} 
//-----------------------------------------------------------------------------
void update_ui_transform();
//-----------------------------------------------------------------------------
UI_Panel *ADD_EDIT_NODE_TRANSFORM(UI_Panel *p);
static Node *createNodeType(const str &type_name);
static bool validNodeType(const str &type_name);

static Node *load_rec(const XML *xml);
void save_rec(XML *xml, Node *n);
//----------------------------------------------------------------------------- Resource
bool load(const str &filename);
bool save(const str &filename);
void save(XML *xml){}
void load(const XML *xml){}
static const Resource *fallback();
u32_t res_type() const { return Resource::NODE; }
};
//=============================================================================
#endif
