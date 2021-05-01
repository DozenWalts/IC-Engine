#ifndef __PROFILER_H__
#define __PROFILER_H__
//=============================================================================
#include "BaseTypes.h"
#include "Sys/Timer.h"
#include "Sys/Tlist.h"
#include "Sys/HashTable.h"
#include "Sys/Str.h"
#include "Sys/DLL_API.h"
struct UI_Panel;//FD
//=============================================================================
struct DLL_API Profiler_element {
	const char *id,*tag;//or name pointer
	float start_time, end_time;
	u32_t calls, tid;
	u32_t vhash;
	float avg_sec, avg_frametime, ftime, ui_x, ui_prog, seconds, fcalls;
	bool inuse_now;
	Profiler_element *parent;
	UI_Panel *panel;
	//-----------------------------------------------------------------------------
	void init(const char *c = nullptr, const char *t = nullptr, Profiler_element *np = nullptr);
	Profiler_element(const char *c = nullptr, const char *t = nullptr, Profiler_element *np = nullptr);
	~Profiler_element(){}
	//-----------------------------------------------------------------------------
	void end_tick(float new_end_time);
	//-----------------------------------------------------------------------------
	float timeout()const;// seconds
	//-----------------------------------------------------------------------------
	void update_frame_info(float frame_time);
};//Profiler_element
//=============================================================================
//=============================================================================
////  SYMBOL_INFO  *symbol[2];
////  symbol[0]               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 64 * sizeof( char ), 1 );
////  symbol[0]->MaxNameLen   = 64;
////  symbol[0]->SizeOfStruct = sizeof( SYMBOL_INFO );
////  symbol[1]               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 64 * sizeof( char ), 1 );
////  symbol[1]->MaxNameLen   = 64;
////  symbol[1]->SizeOfStruct = sizeof( SYMBOL_INFO );
////  void *stack[32];
//// // u8_t frames=CaptureStackBackTrace(1,32,stack,NULL);//(1-skip this,2-+parent,stack,NULL)
//// //it=nullptr;
//// //last_get=nullptr;
//// //bool found=false;
//// //while(E.iterate(it)){
//// // loopi(1,32){ gnm((u64_t)stack[i],0);//cached parent name - dont saved further
//// //  if(!symbol[0]->NameLen)break;
//// //  if(strcmp(gnm((*it)->CA,1),symbol[0]->Name)==0){last_get=it->data_ptr;found=true;break;}//LOG::MSG("FOUND PARENT [%s]==[%s]",symbol[0]->Name,symbol[1]->Name); gnm((*it)->CA,0)
//// // }
//// // if(found)break;
//// //};
//// //LOG::MSG("parent of [%s] - is [%s] --[%s]",gnm((u64_t)stack[0],0),gnm((u64_t)stack[1],1),last_get?last_get->id:"none");
//////-----------------------------------------------------------------------------
////char *gnm(const u64_t &a,u32_t idx){
//// HANDLE process = GetCurrentProcess();
//// SymInitialize( process, NULL, TRUE );
//// SymFromAddr(  process, a, 0, symbol[idx] );
//// return symbol[idx]->Name;
////}
//=============================================================================
//=============================================================================
struct DLL_API sProfiler {																	//Profiler

	Tlist<Profiler_element> E;
	typedef Tlist<Profiler_element>::node elem;

	//KeyValueHashTable<u32_t, Profiler_element*> HE;//hashed elements
	//typedef KeyValueHashTable<u32_t, Profiler_element *>::Element H_elem;
	HashTable<u32_t, Profiler_element*> HE;
	typedef HashTable<u32_t, Profiler_element*>::node H_elem;

	//Tlist<Profiler_element*> call_stack;//vector[thread]
	//typedef Tlist<Profiler_element*>::node cs_elem;
	Profiler_element **call_stack;
	u32_t stack_pos, stack_size;

	Profiler_element **frame_calls;
	u32_t frame_size, frame_calls_max, skipped_;

	Profiler_element **frame_list;
	u32_t frame_list_size;

	Profiler_element *last_get, *last_call, *last_parent;

	UI_Panel *panel;
	//Mutex Pmut;
	//float proc_time,avg_proc_time;

	//u32_t state;
	//enum STT{OFF,ACTIVE};
//-----------------------------------------------------------------------------
	sProfiler();
	~sProfiler();
	//-----------------------------------------------------------------------------
	Profiler_element *get_TList(const char *e, const char *tag);
	Profiler_element *get_Hash(const char *e, const char *tag);
	//-----------------------------------------------------------------------------
	const char *get_fullname(const Profiler_element *it);
	//-----------------------------------------------------------------------------
	void print();
	//-----------------------------------------------------------------------------
	void update_frame_info(Timer T);
	//-----------------------------------------------------------------------------
	bool Down()const;
};//Profiler
//=============================================================================
//usage: PROFILE FT(__FUNCTION__);
//static sProfiler Profiler;
//=============================================================================
struct DLL_API PROFILE {
	Profiler_element *ref;
	int print;
	//-----------------------------------------------------------------------------
	PROFILE(const char *fnm, const char *tag, bool print_info = false);
	//-----------------------------------------------------------------------------
	float elapsed_sec()const;
	//-----------------------------------------------------------------------------
	float elapsed_ms()const { return elapsed_sec() * 1000; }
	//-----------------------------------------------------------------------------
	~PROFILE();
	//-----------------------------------------------------------------------------
};
//=============================================================================
#define PROFILER(tag)PROFILE _##tag(FUNC_NAME,#tag);
#define PROFILER_INFO(tag)PROFILE _##tag(FUNC_NAME,#tag, true);
//#define PROFILER_item(tag)_##tag;
//#define PROFILER_INFO(tag) LOG::msg("%s(%s): %f ms", FUNC_NAME, #tag, _##tag.elapsed_ms());
#endif
