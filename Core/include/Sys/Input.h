#ifndef __INPUT_H__
#define __INPUT_H__ 1

#include "Core.h"
#include "Sys/Timer.h"
#include "App/App.h"

enum keycodes {
	//0-7		unused
	K_BACK = 8,//ASCII
	K_TAB = 9,//ASCII
	// 10,11,12 unused
	K_ENTER = 13,//ASCII
	// 14,15 - shift out/in
	K_SHIFT = 16,
	K_CTRL = 17,
	K_ALT = 18,
	K_PAUSE = 19,// pause/break
	K_CAPS = 20,
	// 21-26	unused
	K_ESC = 27,//ASCII
	// 28-31	unused
	K_SPACE = 32,// printables 32-126
	K_PGUP = 33,// !
	K_PGDN = 34,// "
	K_END = 35,// #
	K_HOME = 36,// $
	K_LEFT = 37,// %
	K_UP = 38,// &
	K_RIGHT = 39,// '
	K_DOWN = 40,// (
	// 41-44	')', '*', '+', ','
	K_INS = 45,// -
	K_DEL = 46,// '.' ASCII 127
	// 47	'/'

	// ASCII nums
	K_0 = 48, K_1 = 49, K_2 = 50, K_3 = 51, K_4 = 52, K_5 = 53, K_6 = 54, K_7 = 55, K_8 = 56, K_9 = 57,

	// 58-64	ASCII :;<=>?@

	// ASCII BIG ALPHA 65-90
	K_A = 65, K_B = 66, K_C = 67, K_D = 68, K_E = 69, K_F = 70, K_G = 71, K_H = 72, K_I = 73, K_J = 74, K_K = 75, K_L = 76, K_M = 77, K_N = 78, K_O = 79, K_P = 80, K_Q = 81, K_R = 82, K_S = 83, K_T = 84, K_U = 85, K_V = 86, K_W = 87, K_X = 88, K_Y = 89, K_Z = 90,

	K_LWIN = 91,// [
	K_RWIN = 92,// '\'
	K_SEL = 93,// ]
	// 94,95	^, _

	//		`		a		b			c			d			e			f			g			h			i
	K_NUM0 = 96, K_NUM1 = 97, K_NUM2 = 98, K_NUM3 = 99, K_NUM4 = 100, K_NUM5 = 101, K_NUM6 = 102, K_NUM7 = 103, K_NUM8 = 104, K_NUM9 = 105,

	K_MUL = 106,// j
	K_ADD = 107,// k
	//		108	// l
	K_SUB = 109,// m
	K_POINT = 110,// n
	K_DIV = 111,// o

	//	p			q		r			s		t			u		v			w		x			y		z			{
	K_F1 = 112, K_F2 = 113, K_F3 = 114, K_F4 = 115, K_F5 = 116, K_F6 = 117, K_F7 = 118, K_F8 = 119, K_F9 = 120, K_F10 = 121, K_F11 = 122, K_F12 = 123,

	// 124-143		// printables 32-126

	// extended ASCII
	K_NUMLOCK = 144,// numlock
	K_SCROLLOCK = 145,// scroll lock
	// 146-185
	K_SEMI = 186,// ';'
	K_EQUAL = 187,// '='
	K_COMMA = 188,// ','
	K_MINUS = 189,// '-'
	K_DOT = 190,// '.'
	K_SLASH = 191,// '/'
	K_TILDA = 192,// '`'
	// 193-218
	K_OPEN = 219,// '('
	K_BSLASH = 220,// '\'
	K_CLOSE = 221,// ')'
	K_QUOTE = 222,//  '
	// 223-255
};

struct DLL_API Inputs {
	int mx, my, lmx, lmy, wheel, gx, gy, dx, dy;
	bool mouse[3], lmouse[3], mousemove;
	float mouse_time[3], lmouse_time[3], llmouse_time[3];//hold time,doubleclick...

	bool key[256], lkey[256], keypressed;
	u32_t kb_key, char_key, key_pressed, prev_key_pressed;
	double prev_key_pressed_time, key_pressed_time;

	Inputs() {
		LOG::msg(FUNC_NAME);
		mx = my = lmx = lmy = wheel = gx = gy = dx = dy = 0;
		loop0i(3) mouse[i] = lmouse[i] = 0;//   =mouseclick[i]=lmouseclick[i]
		keypressed = mousemove = 0;
		char_key = 0;
		memset(lkey, 0, 256);
		memset(key, 0, 256);
		prev_key_pressed = key_pressed = 0;
		prev_key_pressed_time = key_pressed_time = 0.0;
	}
	~Inputs() {
		LOG::msg(FUNC_NAME);
	}

	void process_keycode(u32_t i, char state) {
		//LOG::msg("%s key = %i",state==0?"released":"pressed",i);
		//if (i >= 255) { LOG::warn("key %i >= 255", i); return; }
		keypressed = (state != 0);
		if (state == 2) { char_key = i; return; } else char_key = 0;
		if (i < 255) {
			lkey[i] = key[i];
			key[i] = (state != 0);
		}
		kb_key = i;
		if (state) {
			prev_key_pressed = key_pressed;
			prev_key_pressed_time = key_pressed_time;
			key_pressed = keyp(i) ? i : 0;
			key_pressed_time = Timer::time();
		}
	}

	u32_t sys_spec(u32_t i) {
		switch (i) {
			case 188:return ',';
			case 190:return '.';
			case 191:return '/';//47
			case 186:return ';';
			case 222:return 34;//'"';
			case 220:return 92;//'\';
			case 219:return '[';
			case 221:return ']';
			case 192:return '`';
			case 189:return '-';
			case 187:return '=';
		};
		return i;
	}

	u32_t sys_shift_num(u32_t i) {
		switch (i) {
			case '1':return '!';
			case '2':return '@';
			case '3':return '#';
			case '4':return '$';
			case '5':return '%';
			case '6':return '^';
			case '7':return '&';
			case '8':return '*';
			case '9':return '(';
			case '0':return ')';

			case '`':return '~';
			case '-':return '_';
			case '=':return '+';
			case ',':return '<';
			case '.':return '>';
			case '/':return '?';
			case ';':return ':';
			case 34:return 39;//''' '"'; case '\'':ret='"';break;
			case 92:return '|';//'\'  case '\\':ret='|';break;
			case '[':return '{';
			case ']':return '}';
		};
		return i;
	}

	void setMousePos(int x, int y) {
		_App->setMouse(x, y);
		getMousePos();
	}

	void getMousePos() {
		lmx = mx;
		lmy = my;
		_App->getMouse(mx, my);
		dx = mx - lmx;
		dy = my - lmy;
		mousemove = lmx != mx || lmy != my;
	}

	void setMouseClick(int i, bool new_state) {
		if (i >= 3) {
			if (i < 5)wheel = (i == 3 ? 1 : -1);
			return;
		}
		lmouse[i] = mouse[i];
		mouse[i] = new_state;
	}

	void prepare() {
		lmouse[0] = lmouse[1] = lmouse[2] = 0;
		getMousePos();
#ifdef _WIN32
		lmouse[0] = mouse[0]; mouse[0] = GetAsyncKeyState(VK_LBUTTON) != 0;
		lmouse[1] = mouse[1]; mouse[1] = GetAsyncKeyState(VK_RBUTTON) != 0;
		lmouse[2] = mouse[2]; mouse[2] = GetAsyncKeyState(VK_MBUTTON) != 0;
#endif
		wheel = 0;//!! clear each frame
		if (mouse_start_click()) gx = mx, gy = my;
		//clear each frame for input.keyp(i)==1 once
		memcpy(lkey, key, 256);// do not comment
		keypressed = 0;//	=mousemove ? do not? !not! else gui input repeats
		kb_key = 0;
	}

	void clear_inputs() {
		for (int i = 0; i < 3; i++) {
			//lmouse[i] = mouse[i] = 0;
			//lmouseclick[i]=mouseclick[i]=0;
			//llmouse_time[i] = lmouse_time[i] = mouse_time[i] = 0;
		}
		memcpy(lkey, key, 256); keypressed = mousemove = 0;
		kb_key = 0;//key_press = prev_key_press = 0;
	}

	bool keyp(int kk) { return kk<255 && (key[kk] && !lkey[kk]); }
	bool mouse_hold(int i = -1) { return i >= 0 ? (mouse[i] && lmouse[i]) : ((mouse[0] && lmouse[0]) || (mouse[1] && lmouse[1]) || (mouse[2] && lmouse[2])); }
	bool mouse_end_click(int i = -1) { return i >= 0 ? (!mouse[i] && lmouse[i]) : ((!mouse[0] && lmouse[0]) || (!mouse[1] && lmouse[1]) || (!mouse[2] && lmouse[2])); }//start releasing
	bool mouse_start_click(int i = -1) { return i >= 0 ? (mouse[i] && !lmouse[i]) : ((mouse[0] && !lmouse[0]) || (mouse[1] && !lmouse[1]) || (mouse[2] && !lmouse[2])); }//start holding

	void get_doubleclick(float UpdateTimer_frameTime) {
		for (int i = 0; i < 3; i++) {
			if (mouse[i] != lmouse[i]) { llmouse_time[i] = lmouse_time[i]; lmouse_time[i] = mouse_time[i]; mouse_time[i] = 0; } else mouse_time[i] += UpdateTimer_frameTime;
			//float dc=(llmouse_time[i]+lmouse_time[i]+mouse_time[i]);
			//if(!lmouse[i] && mouse[i] && dc<0.25)LOG::ERR("Double click %i [%f]",i,dc);
		}
	}

	bool doubleclick(int i) {
		float dc = (llmouse_time[i] + lmouse_time[i] + mouse_time[i]);
		//if(!lmouse[i] && mouse[i] && dc<0.25f)LOG::ERR("Double click %i [%f]",i,dc);
		return (!lmouse[i] && mouse[i] && dc < 0.25f);//
	}

	bool doubleclicked(int i) {
		float dc = (llmouse_time[i] + lmouse_time[i] + mouse_time[i]);
		//if(lmouse[i] && !mouse[i] && dc<0.25f)LOG::ERR("Double clicked %i [%f]",i,dc);
		return (lmouse[i] && !mouse[i] && dc < 0.25f);//
	}

	bool double_keyp(int i) {
		return (keyp(i) && prev_key_pressed == i && Timer::time() - prev_key_pressed_time < 0.25);
	}

};

#endif
