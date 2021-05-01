#ifndef __SHADER_H__
#define __SHADER_H__ 1

#include "Sys/Str.h"
//#include "Maths.h"
#include "Sys/vector.h"
#include "Scene/Resource.h"

struct mat4;
struct vec3;
struct vec4;

struct DLL_API Shader final : Resource {
	str name;
	int program_id;
	int vertex_id;
	int fragment_id;

	int num_attribs;
	int activeAttributes;
	int activeUniforms;
	int numTextures;
	int *texid;

	struct var{
		str name;
		u16_t size;
		u16_t type;
		int id;
		enum{
			Attrib = 0, Uniform1=1, Uniform2=2, Uniform3=3, Uniform4=4, Uniform16=16,
		};
		var():name(){}
	};
	Vector<Shader::var*> shader_vars;
	//vector<Variable> vars;
	//SIHT<str> var_names;
	//int addVar(str var_name);
	//int &find_var_id(str var_name);
	//void setVar(str var_name, mat4 val);
	bool create(const char *shader_name,const char *vert_code, const char *fragment_code);
	int getUniform(const char *name);
	void setUniform(int id,const mat4 &M);
	void setUniform(int id,const vec3 &V);
	void setUniform(int id,const vec4 &V);
	void setUniform(int id, const int &V);
	void bindAttrib(const char *var_attrib);
	void bind();
	void unbind();
	//----------------------------------------------------------------------------- Resource
	//void init() {}
	bool load(const str &filename);
	bool save(const str &filename);
	static const Resource *fallback();
	u32_t res_type() const { return Resource::SHADER; }
};
#endif