#ifndef __GRAPH_H__
#define __GRAPH_H__
//=============================================================================
#ifdef __linux__
	#include <sys/sysinfo.h>
#elif _WIN32 || _WIN64
	#include <psapi.h> //GetProcessMemoryInfo
	//#pragma comment(lib, "psapi.lib")
	//#include "..\\sys\\GetMemorySize.h"
#endif
//=============================================================================
#include "BaseTypes.h"
#include "Sys/Str.h"
#include "Sys/Timer.h"
#include "UI/UI.h"
//=============================================================================
struct DLL_API Graph :UI_Widget {
	u32_t mv, memv;
	vec3 *v, *va, *vb, *vc;
	str name;
	Timer *ptimer;
	Timer GraphTimer;
	int lframes, vline_idx;
	u32_t used_mem;
	#ifdef _WIN32
		PROCESS_MEMORY_COUNTERS memCounter;
	#endif
	//-----------------------------------------------------------------------------
	Graph();
	~Graph();
	void init();
	UI_Panel *create_UI(UI_Panel *Main);
	//-----------------------------------------------------------------------------
	void resize(const u32_t &nmv);
	//-----------------------------------------------------------------------------
	void add(const vec3 &p, u32_t num);
	void add_va(const vec3 &p, u32_t num);
	void add_vb(const vec3 &p, u32_t num);
	void add_vc(const vec3 &p, u32_t num);
	//-----------------------------------------------------------------------------
	void update_profiler();
	void Update_every_tick();
	//-----------------------------------------------------------------------------
	void Draw_UI()override;
	//-----------------------------------------------------------------------------
};
//=============================================================================
#endif
