#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Sys/HashTable.h"
#include "Sys/XML.h"

struct DLL_API Resource {
	u32_t res_id;
	str *res_path;

	enum {
		UNKNOWN = 0,
		TEXTURE = 1,
		MESH = 2,
		MODEL = 3,
		NODE = 4,
		MATERIAL = 5,
		SHADER = 6,
		SVG = 7,
	};

	Resource() {
		res_path = nullptr;
		res_id = 0;
	}
	virtual ~Resource() {}

	virtual void init() {}
	virtual bool load(const str &filename) { return false; }
	virtual bool save(const str &filename) { return false; }
	virtual void save(XML *xml) { }
	virtual void load(const XML *xml) { }
	virtual Resource *fallback() { return nullptr; }
	virtual u32_t res_type() const{ return UNKNOWN; }
};

static char* ResTypeToName(u32_t type){
	switch(type){
        case Resource::TEXTURE: return (char*)"TEXTURE";
        case Resource::MESH:	return (char*)"MESH";
        case Resource::MODEL:	return (char*)"MODEL";
        case Resource::NODE:	return (char*)"NODE";
        case Resource::MATERIAL: return (char*)"MATERIAL";
        case Resource::SHADER:	return (char*)"SHADER";
        case Resource::SVG:		return (char*)"SVG";
	}
    return (char*)"Unknown";
}

static u32_t ResNameToType(char *type_name){
	switch(type_name[0]){
		case 'S': return (type_name[1] == 'H') ? Resource::SHADER : Resource::SVG;
		case 'T': return Resource::TEXTURE;
		case 'M': return (type_name[1] == 'E') ? Resource::MESH : (type_name[1] == 'O') ? Resource::MODEL : Resource::MATERIAL;
		case 'N': return Resource::NODE;
	}
	return Resource::UNKNOWN;
}

// NodeTypes

//static struct Node* createFromTypeId(u32_t type_id){
//	Node* ret = nullptr;
//	switch(type_id){
//		case Resource::TEXTURE: ret = (Node*) new Texture(); break;
//		case Resource::MESH:	ret = (Node*) new Mesh(); break;
//		case Resource::MODEL:	ret = (Node*) new Model(); break;
//		case Resource::NODE:	ret = (Node*) new Node(); break;
//		case Resource::MATERIAL: ret = (Node*) new Material(); break;
//		case Resource::SHADER:	ret = (Node*) new Shader(); break;
//		case Resource::SVG:		ret = (Node*) new Svg(); break;
//	}
//	return ret;
//}
//static struct Node* createFromTypeName(char *type_name){
//	u32_t type_id = ResNameToType(type_name);
//	return createFromTypeId(type_id);
//}
//template <class Type>
struct ResourceDB {

	HashTable<str, u32_t> str2id;
	typedef HashTable<str, u32_t>::node s2i_node;

	HashTable<u32_t, Resource*> id2res;// why not vector, - data stored here
	typedef HashTable<u32_t, Resource*>::node i2r_node;

	u32_t static_counter;// = 0;

	ResourceDB() : str2id(), id2res(), static_counter(0) {}
	~ResourceDB() {}

	u32_t get_new_id() {
		return ++static_counter;
	}

	void add(Resource *res, const str &filename) {// res must be allocated
		res->res_id = get_new_id();
		str2id[filename] = res->res_id;
		id2res[res->res_id] = res;
	}

	Resource *find(const str &filename) {
		s2i_node *id = str2id.find(filename);
		if (id == nullptr) return nullptr;
		i2r_node *res = id2res.find(id->value);
		return res ? res->value : nullptr;
	}

	Resource *operator[](u32_t res_id) {return id2res[res_id];}
	Resource *operator[](const str &res_name) {return id2res[str2id[res_name]];}

	void remove(u32_t res_id) {
		i2r_node *res = id2res.find(res_id);
		if (res == nullptr) return;
		s2i_node *id = str2id.find(*res->value->res_path);
		if (id != nullptr) id->unuse();
		res->unuse();
	}

	// keep id
	void rename(u32_t res_id, const str &new_filename) {
		i2r_node *res = id2res.find(res_id);
		if (res == nullptr) return;
		s2i_node *id = str2id.find(*res->value->res_path);
		if (id != nullptr) id->unuse();
		res->unuse();
		str2id[new_filename] = res_id;
		id2res[res_id] = res->value;
	}
};

#endif
