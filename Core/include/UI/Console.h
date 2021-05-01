#ifndef __CONSOLE_H__
#define __CONSOLE_H__
//=============================================================================
#include "Sys/DLL_API.h"
#include "Sys/Str.h"
#include "UI/UI_Panel.h"
//=============================================================================
struct TextWindow {
	int start_offset;
	int lines_from_start;
	Vector<str> lines;// visible screen lines of font.height, page?
	void setNumLines(int lines);
	void push(const str &line);
	void split(int line, int pos);
	void merge(int line, int pos);
	void del(int aline, int apos, int bline, int bpos);
	//void load(BUFFER *B);
};
//=============================================================================
struct DLL_API Console /*: UI_Panel*/ {
	bool show;
	UI_Panel *panel;
	Vector<str> lines;// visible screen lines of font.height, page?
	Console() { 
		LOG::msg(FUNC_NAME);
		show = false;
		panel = nullptr;
	}
	~Console() {
		LOG::msg(FUNC_NAME);
		DELETE(panel);
	}
	void Message(const str &msg);
	void Toggle();
};
//=============================================================================
#endif
