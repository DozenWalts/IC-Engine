#ifndef __PLUGINS_H__
#define __PLUGINS_H__

#include "Plugin.h"
#include "Sys/Str.h"
#include "Script/Script.h"

typedef void *(*CreatePlugin_func)();

struct Plugins {

	HashTable<str, Plugin*> plugins;

	DLL_API Plugins();
	DLL_API ~Plugins();

	DLL_API void Update();
	DLL_API void Render();

	DLL_API bool find(const char *name);
	DLL_API bool run(const str &func_name, void *data_ptr);
	DLL_API bool run(const char *type, const char *func, void *data_ptr, const str &name);
	DLL_API FunctionBase *get(const char *lib_name, const char *func);
};

#endif
