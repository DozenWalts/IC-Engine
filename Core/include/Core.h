#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "BaseTypes.h"
#include "Sys/DLL_API.h"
#include "Sys/vector.h"
#include "Plugins.h"
#include "Script/Function.h"
#include "Winnie/closure.h"
//#pragma GCC diagnostic ignored "-fno-fpermissive"

struct EngineData;

struct sProfiler;
struct Plugins;
struct Console;
struct Render;
struct Inputs;
struct Scene;
struct App;
struct GUI;
struct Net;

struct DLL_API Engine{

	static EngineData *get();

	// req init in exe
	//Render *render;
	//Inputs *input;
	//App *app;
	//Engine() {};
	
	static sProfiler *Profiler();
	static Plugins *Plugins();
	static Console *Console();
	static Render *Render();
	static Inputs *Input();
	static Scene *Scene();
	static App *App();
	static GUI *Gui();
	static Net *Net();

	static void init(int argc,char **argv, ::App *new_app, ::Render *new_render = nullptr);
	static bool loop();
	static void update();
	static void draw();
	static void RenderScene();
	static void setRenderSceneFunc(FunctionBase *func);// Plugin &c, void(Plugin::*mfunc)());// void(*void_lambda)());
	static void flush();
	static void exit();
};

struct EngineData{
	//Engine *engine;
	sProfiler *profiler;
	Plugins *plugins;
	Console *console;
	Render *render;
	Inputs *input;
	Scene *scene;
	App *app;
	GUI *gui;
	Net *net;

	//void(*void_lambda)();
	FunctionBase *RenderSceneCallback;
};

/*extern "C" DLL_API */extern EngineData engine;// to use DLL_API on 'engine' it MUST be a pointer
//static Engine engine;// null inside dll

/*
void test1() {
	UI_Panel *Main = _Gui->ADD(GUI::PANEL, "Main");// 2x mov + 1x call
 // 00000	8b 0d 00 00 00
	//00		 mov	 ecx, DWORD PTR __imp_?_Gui@@3PAUGUI@@A
 // 00006	6a 00		 push	 0
 // 00008	68 00 00 00 00	 push	 OFFSET ??_C@_04KGFMLCPK@Main?$AA@
 // 0000d	6a 00		 push	 0
 // 0000f	8b 09		 mov	 ecx, DWORD PTR [ecx]
 // 00011	ff 15 00 00 00
	//00		 call	 DWORD PTR __imp_?ADD@GUI@@QAEPAUUI_Panel@@EPBDPAU2@@Z
}
void test2() {
	UI_Panel *Main = Engine::Gui()->ADD(GUI::PANEL, "Main");// 2x call + 1x mov
 // 00009	ff 15 00 00 00
	//00		 call	 DWORD PTR __imp_?Gui@Engine@@SAPAUGUI@@XZ
 // 00000	6a 00		 push	 0
 // 00002	68 00 00 00 00	 push	 OFFSET ??_C@_04KGFMLCPK@Main?$AA@
 // 00007	6a 00		 push	 0
 // 0000f	8b c8		 mov	 ecx, eax
 // 00011	ff 15 00 00 00
	//00		 call	 DWORD PTR __imp_?ADD@GUI@@QAEPAUUI_Panel@@EPBDPAU2@@Z
}
void test3() {
	//GUI &LGUI = *_Gui; - local var
	UI_Panel *Main = LGUI.ADD(GUI::PANEL, "Main");// - x1 mov 1x call
 // 00000	8b 0d 00 00 00
	//00		 mov	 ecx, DWORD PTR ?_LGui@@3PAUGUI@@A ; _LGui
 // 00006	6a 00		 push	 0
 // 00008	68 00 00 00 00	 push	 OFFSET ??_C@_04KGFMLCPK@Main?$AA@
 // 0000d	6a 00		 push	 0
 // 0000f	ff 15 00 00 00
	//00		 call	 DWORD PTR __imp_?ADD@GUI@@QAEPAUUI_Panel@@EPBDPAU2@@Z
}*/
// Optimization Engine::Gui()->Add() vs _Gui->Add() -> call(push+jmp+ret) vs mov
DLL_API extern sProfiler *_Profiler;
DLL_API extern Plugins *_Plugins;
DLL_API extern Console *_Console;
DLL_API extern Render *_Render;
DLL_API extern Inputs *_Input;
DLL_API extern Scene *_Scene;
DLL_API extern App *_App;
DLL_API extern GUI *_Gui;
DLL_API extern Net *_Net;

#ifndef _DLL_
#ifndef _PLUGIN_
	#ifdef _WIN64
		#pragma comment(lib,"../bin/Core_x64.lib")
	#else
		#ifdef _WIN32
			#pragma comment(lib,"../bin/Core_x32.lib")
		#endif
	#endif

	#ifdef _WIN32
		int main(int argc, wchar_t **argv);
		//#include <windows.h>
		int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
			int num=0;
			return main(__argc, CommandLineToArgvW(GetCommandLineW(), &num));//CommandLineToArgvW(__argv, __argc));//https://stackoverflow.com/questions/291424/canonical-way-to-parse-the-command-line-into-arguments-in-plain-c-windows-api/42048224#42048224
		};
	#endif

#endif
#endif
//#ifdef _DEBUG

#endif
