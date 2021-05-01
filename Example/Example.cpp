
// @include "engine_include.h"
#include "Core.h"
#include "App/App.h"
#include "Math/Maths.h"

#include "Sys/Input.h"
#include "Sys/Str.h"
#include "Sys/Profiler.h"
#include "Sys/Buffer.h"
#include "Sys/Socket.h"

#include "Render/GLRender.h"
#include "Render/FFP.h"
#include "Render/Texture.h"

#include "UI/UI_Panel.h"
#include "UI/Graph.h"
#include "UI/Console.h"
#include "UI/Chat.h"

#include "Scene/Scene.h"
#include "Scene/Camera.h"
#include "Scene/Mesh.h"
#include "Scene/Model.h"
#include "Scene/Gizmo.h"
#include "Scene/svg.h"
#include "Math/ray.h"


struct Example final :App{
	Graph GMS;
	Chat chat;

	Example() : App() { LOG::msg(FUNC_NAME); }
	~Example(){ LOG::msg(FUNC_NAME); }

	void init(){
		LOG::msg(FUNC_NAME);

		GMS.create_UI(_Gui->find("Main"));

		chat.add_chat_ui();
	}

	void update(){
		//if (_Input->keyp(K_F4)) { _Editor->toggle(); }
		if (_Input->keyp(K_ESC)) { LOG::msg("K_ESC"); loop = false; return; }
		if (_Input->keyp(K_V)) _Render->VSync(!_Render->vsync);
		if (_Input->keyp(K_TILDA)) _Console->Toggle();
		//https://www.ibm.com/developerworks/ru/library/l-inotify/index.html
		//http://netcode.ru/cpp/?artID=5263 Отслеживание изменений в директории
		if(timer.once()){
			//_App->setTitle(str(0," FPS:%.0f(%.2f) frameTime = %f ms", timer.fps, 1.0/timer.frameTimeAvg, timer.frameTimeAvg*1000).text);
		}
		chat.update();
	}

	void draw(){
	}
	
	void flush(){
		PROFILER(0);// 27%
		GMS.Update_every_tick(); //move to update? or place at end
	}
	
	void exit(){LOG::msg(FUNC_NAME);}
};

#include <exception>

int main(int argc, wchar_t **argv)try{
	LOG::init(str(0, "%s/engine_log.html", App::exe_path().text).text);
	Example *app = new Example();
	Engine::init(argc, (char**)argv, app);
	_App->setUpdateFocuslost(true);

	str *args = new str[argc]();
	loop0i(argc) {
		args[i].push16w(argv[i], lstrlenW(argv[i]));
		LOG::msg("%i:%s", i, args[i].text);
	}
	if(argc>1)_Scene->load(args[1]);
	delete[] args;

	LOG::msg("----------------------------------");
	while (Engine::loop()) {
		{
			PROFILER(0);
			Engine::update();
			Engine::draw();
			Engine::flush();
		}
		_Profiler->update_frame_info(_App->timer);
	}

	LOG::msg("----------------------------------");
	Engine::exit();
	return 0;
}ERROR_CATCHER
