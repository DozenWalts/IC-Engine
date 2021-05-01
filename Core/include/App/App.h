#ifndef __APP_H__
#define __APP_H__

#include "Sys/Log.h"
#include "Sys/DLL_API.h"
#include "Sys/Timer.h"
#include "Sys/vector.h"// dir

#ifdef _WIN32
	#define _WIN32_WINDOWS	0x0500
	//#define _WIN32_WINNT	0x0500
	//https://aras-p.info/blog/2018/01/12/Minimizing-windows.h/
	//https://github.com/Leandros/WindowsHModular/tree/master/include/win32
	#define WIN32_LEAN_AND_MEAN //69100 lines -> 33375 lines
	#include <windows.h>
#else
	#include <unistd.h>
	#include <X11/Xlib.h>
	#include <X11/Xatom.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>
	#include <X11/extensions/Xrandr.h>
	#include <X11/extensions/Xinerama.h>
	#include <GL/gl.h>
	#include <GL/glx.h>
#endif

struct DLL_API App{
	int width, height;
	float aspect;
	int left, top;
	int flags;
	Timer timer;

	bool active, force_active;
	bool mouse_show;
	bool loop;

	u32_t num_drop_files, num_drop_files_mem;
	int df_accessed;
	str **drop_file_name;//private

	#ifdef _WIN32
		HWND window;
		HCURSOR mouse_cursor;
		POINT mpos;
		HHOOK key_hook;
	#else
		Display *display;
		int screen;

		Window root_window;

		int num_screens;					// xinerama screens
		XineramaScreenInfo *screens;

		XRRScreenConfiguration *xrandr;
		Rotation default_rotation;
		int default_video_mode;
		int current_video_mode;
		int num_video_modes;				// xrandr video modes
		XRRScreenSize *video_modes;

		XVisualInfo *visual;
		GLXFBConfig config;

		Window window;
		char window_title[1024];
		int *window_icon;
		Cursor window_cursor;
		int window_flags;
		int window_update;
		int window_unmapped;
		int window_focused;

		Atom wm_delete_window;				// atoms
		Atom utf8_string;
		Atom net_wm_icon;

		XIM xim;							// input methods
		XIC xic;

		int mouse_x;						// mouse
		int mouse_y;
		int mouse_button;
		int mouse_release;
		int mouse_grab;
		//int mouse_show;
		Time mouse_time;
		int mouse_button_x;
		int mouse_button_y;
		Cursor mouse_cursor;

		//int keys[App::NUM_KEYS];			// keyboard
		//int num_released_keys;
		//unsigned int released_keys[64];

		int is_done;

		char *clipboard;
	#endif

	App();
	virtual ~App();

	void initWindow(int new_width=-1,int new_height=-1);
	void updateWindow();
	void setTitle(const char *title);
	int getMonitorHZ();
	void OnResize(int x,int y,int w,int h);

	bool setMouse(int x,int y);
	bool getMouse(int &x, int &y);
	void setMouseShow(bool show);
	void setUpdateFocuslost(bool up);

	bool OpenUserFile(str &path, const str &filter);
	static str getWorkingDir();
	static str exe_path();
	static Vector<str> *DIR(const str &start_path, bool only_folders = false);

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void flush() = 0;
	virtual void exit() = 0;

	static bool isDirExist(const char *const path);

	void add_drop_file_name(str *dfn);
	str *get_next_drop_file_name();

};

#endif
