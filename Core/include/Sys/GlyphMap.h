#ifndef __GLYPH_MAP_H__
#define __GLYPH_MAP_H__

#include "Sys/HashTable.h"
#include "Render/Texture.h"

struct DLL_API GlyphMap {// XID font; in "X.h"

	float m_width, m_height;// 256x256 px

	struct glyph{
		float width, height;// 16k/16k px
		vec4 uv;
		glyph() { width = 8; height = 16; uv.set(0,0,1,1); }
	};

	typedef HashTable<u32_t, glyph*>::node GlyphHash;
	HashTable<u32_t, glyph*> _glyphs;
	Texture tex;

	void init();
	GlyphMap();
	void on();
	void off();
	u32_t width(u32_t cpos, const str *text);
	glyph *operator [](u32_t utf32);
	void PrintW(float x, float y, float w, float h, float gy, float gyh, int center, str &msg);
	float char_width(u32_t cc);
	void update(const str &text);
	bool wrap(float &x, float startx, float &y, float w, const str &text, const char *s, glyph *&G);
	vec2 textpos_to_cursor(u32_t char_pos, float startx, float w, str &text);
	u32_t cursor_to_textpos(vec2 local_cursor, float startx, float w, const str &text);
};
#endif
