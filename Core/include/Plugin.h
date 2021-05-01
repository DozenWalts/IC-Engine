#ifndef __PLUGIN_H__
#define __PLUGIN_H__

struct Script;//FD
#include "Sys/Str.h"

struct Plugin {
	//#ifdef _WIN32
	//	HMODULE handle;
	//#else
	//	void *handle;
	//#endif
	str name;
	Script *code;
	virtual void init() = 0;
	virtual void exit() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
};

#endif
