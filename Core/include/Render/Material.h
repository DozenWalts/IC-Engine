#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "BaseTypes.h"
#include "Sys/DLL_API.h"
#include "Sys/Str.h"
#include "Sys/Buffer.h"
#include "Scene/Resource.h"
#include "Sys/vector.h"

struct Texture;// FD
//struct Shader;// FD

struct DLL_API Material : Resource {
	str name;
	int order;
	//Vector<u32_t> tex;// all textures, index in scene.db resources
	//u32_t diffuse;
	//u32_t normal;
	//Texture *diffuse();
	//Texture *normal();

	Vector<Texture*> tex;// all textures
	Texture *diffuse;// pointer to tex[i]
	Texture *normal;// pointer to tex[i]
	//Shader *shader;
	//int albedo, normal, metalic, ambient, emmisive, lightmap;
	union {
		u8_t flags;
		struct { int depth_test : 1, blend : 1, wirefarme : 1, flag4 : 1, flag5 : 1, flag6 : 1, flag7 : 1, flag8 : 1; };
	};

	Material();
	Material(const Texture *diff);
	~Material();
	Material *clone();
	void on()const;
	void off()const;
	bool Load(BUFFER *B);
	void Save(BUFFER *B);
};

#endif
