#ifndef __STR_H__
#define __STR_H__

#include "BaseTypes.h"

//eng
#define t_eng_big(c)  (c>64 && c<91)
#define t_eng_small(c)                  (c>96 && c<123)
#define t_eng(c)     ((c>64 && c<91) || (c>96 && c<123))
//rus ASCII
#define t_rus_Ee(c)(c==240 || c==241)
#define t_rus_big(c)(c>127 && c<160 || c==240)
#define t_rus_small(c)((c>159 && c<176) || (c>223 && c<240) || c==241)
#define t_rus(c)((c>127 && c<176) || (c>223 && c<242))
//rus ANSI
#define t_rus_Ee_ANSI(c)(c==168 || c==184)
#define t_rus_big_ANSI(c)((c>191 && c<224) || c==168)
#define t_rus_small_ANSI(c)(c>223 || c==184)
#define t_rus_ANSI(c)(c>191 || c==184 || c==168)
//special
#define t_nums(c)(c>47 && c<58)//0123456789
#define t_special(c)  ((c>57 && c<65) || (c>90 && c<97) || (c>122 && c<128) || (c>31 && c<42) || (c>41 && c<48) || c==9 || c==10 || c==13)
#define t_special_p(c)((c>57 && c<65) || (c>90 && c<97) || (c>122 && c<128) || (c>31 && c<42) || (c>41 && c<48))
//system                 :;<=>?@            [\]^_`           {|}~           (space)!"#$%&'()      *+,-./        tab      /r      /n
#define t_system(c)(c<32)
#define t_ASCIIGraph(c)(c>175 && c<224)
#define t_dop_ASCII(c)(c>241)//242 - 255 DOPx     
//globals                                                     tab      /r      /n
#define t_printable(c)((c>31 && c<176) || (c>223 && c<242))// || c==9 || c==10 || c==13)
#define t_numeric(c)((c>47 && c<58) || (c>42 && c<47))//0123456789 +,-.
#define t_printable2(c)(t_nums(c) || t_special_p(c) || t_eng(c) || t_rus_ANSI(c) )// || t_rus(c)

//const u32_t STR_STACK_SIZE = 128-16;//-16 on x86, -24 on x64
const u32_t STR_MAX = U32_MAX;

#define UNI_SUR_HIGH_START		(u32_t) 0xD800
#define UNI_SUR_LOW_END			(u32_t) 0xDFFF
#define UNI_MAX_LEGAL_UTF32		(u32_t) 0x0010FFFF
//#define UNI_REPLACEMENT_CHAR	(u32_t) 0x0000FFFD

////// skip encoding autodetection if input buffer is too small
////if (size < 4) return encoding_utf8;
////
////uint8_t d0 = data[0], d1 = data[1], d2 = data[2], d3 = data[3];
////
////// look for BOM in first few bytes
////if (d0 == 0 && d1 == 0 && d2 == 0xfe && d3 == 0xff) return encoding_utf32_be;
////if (d0 == 0xff && d1 == 0xfe && d2 == 0 && d3 == 0) return encoding_utf32_le;
////if (d0 == 0xfe && d1 == 0xff) return encoding_utf16_be;
////if (d0 == 0xff && d1 == 0xfe) return encoding_utf16_le;
////if (d0 == 0xef && d1 == 0xbb && d2 == 0xbf) return encoding_utf8;
////
////// look for <, <? or <?xm in various encodings
////if (d0 == 0 && d1 == 0 && d2 == 0 && d3 == 0x3c) return encoding_utf32_be;
////if (d0 == 0x3c && d1 == 0 && d2 == 0 && d3 == 0) return encoding_utf32_le;
////if (d0 == 0 && d1 == 0x3c && d2 == 0 && d3 == 0x3f) return encoding_utf16_be;
////if (d0 == 0x3c && d1 == 0 && d2 == 0x3f && d3 == 0) return encoding_utf16_le;
////
////// look for utf16 < followed by node name (this may fail, but is better than utf8 since it's zero terminated so early)
////if (d0 == 0 && d1 == 0x3c) return encoding_utf16_be;
////if (d0 == 0x3c && d1 == 0) return encoding_utf16_le;

bool isalpha(char c);//FD

#ifdef __linux__
	#include <ctype.h>//tolower
#endif

#ifndef _WIN32
#ifndef _vscprintf
static int _vscprintf(const char *format, va_list pargs){
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}
#endif
#endif

// t>192?(t<224?1:(t<240?2:(t<248?3:(t<252?5:5)))):0
// t>192?trailingBytesForUTF8[t]:0
static const char trailingBytesForUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//16+16=32
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//4
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//5
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//6*32=192bytes
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//32
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5//16,8,4,4
};

static void memcpy4(char *dst, const char *src, u32_t size) {// TODO compare to memcpy()
	if (dst == nullptr || src == nullptr || size == 0) DEBUG_BREAK
	if (dst > src && (u32_t)(dst - src) < size) {
		dst += size - 1;
		src += size - 1;
		iloop0i(size) *dst-- = *src--;
	} else {
		if (size & ~3) {
			iloop0i(size >> 2) {
				dst[0] = src[0];
				dst[1] = src[1];
				dst[2] = src[2];
				dst[3] = src[3];
				dst += 4;
				src += 4;
			}
			size &= 3;
		}
		if (size) iloop0i(size) *dst++ = *src++;
	}
}
struct PoolStr;//FD

//http://www.reedbeta.com/blog/programmers-intro-to-unicode/
struct DLL_API str{
	u32_t size, mem;
	char *text;// , stack[STR_STACK_SIZE];
	static const str null;

	void init();

	str();
	//str(str &&s);
	str(const str &s);
	str(int any, const char *fmt, ...);
	//https://tproger.ru/articles/move-semantics-and-rvalue/
	explicit str(int prealloc_size);// c++11 [str a = 5;] will not go here, only [str a(5);]
	
	//str(const char *s); 
	explicit str(const char *s, u32_t len = STR_MAX);// c++11

	~str();

	INLINE operator const char*() const { return text; }
	INLINE operator const void*() const { return text; }

	str &operator += (const char c);

	str &operator =  (const char *s);
	str &operator += (const char *s);
	void copy(const char *s, u32_t len = STR_MAX);
	
	str &operator =  (const str &s);
	str &operator += (const str &s);
	void copy(const str &s, u32_t len = STR_MAX);

	void reserve(u32_t nsize);
	//void resize(u32_t nsize);
	void clear();
	void EOS();

	void vprint(const char *fmt,va_list ap);
	void print(const char *fmt, ...);
	void printa(const char *fmt, ...);

	u32_t glyph_len(const char *position)const;
	//------------------------------------------------------------------------------
	void append(u32_t at, const char c);
	void append(u32_t at, const char *s, int slen);
	void ins(u32_t &p, const char *s, u32_t slen);
	void remove(u32_t at, u32_t num);
	void del(u32_t &p, u32_t &e, bool back);
	INLINE bool valid(const char *position)const;
	bool iterate(const char *&position, const char *start_pos = nullptr)const;
	//------------------------------------------------------------------------------
	//static str unicodeToUtf8(const wchar_t *src);
	static int utf8ToUnicode(const char *src,wchar_t &code);
	static int utf8ToUnicode(const char *src,wchar_t *dest,int size);
	wchar_t *toWchar(int *w_size = nullptr)const;
	//------------------------------------------------------------------------------ utf8
	const char *utf_one_char_str(const char *position)const;
	u32_t sub_chr_pos(const char &chr, u32_t after = 0);
	void dec_pos(u32_t &p);
	void inc_pos(u32_t &p);
	//------------------------------------------------------------------------------
	u32_t word_start(const u32_t cpos)const;
	u32_t word_end(const u32_t cpos)const;
	u32_t line_start(const u32_t cpos)const;
	u32_t line_end(const u32_t cpos)const;
	u32_t num_lines()const;
	//------------------------------------------------------------------------------
	bool next(char *&cpos)const;
	bool prev(char *&position)const;
	//------------------------------------------------------------------------------
	bool isLegalUTF8(const char *source, int char_length)const;
	bool is_valid_utf8(const char *value, u32_t extrabytes)const;
	bool is_glyph_valid(const char *cpos)const;
	//------------------------------------------------------------------------------
	u32_t glyphs_num(u32_t from = 0, u32_t to = STR_MAX)const;
	//------------------------------------------------------------------------------
	u32_t utf32(const char *str_ptr_pos)const;
	u16_t utf16(const char *str_ptr_pos)const;
	//------------------------------------------------------------------------------ utf8
	void push8(char c);
	void push32(u32_t utf32);
    void push16w(wchar_t *wc, u32_t num);
	str &strip_zeros(int n = 6);
	//------------------------------------------------------------------------------
	// u32_t lim == 1024*1024*1024*4 == 2^32 ~eq 4Gb -> no Tb
	// u64_t lim == 1024*1024*1024*1024*1024*1024*16 = 2^64 ~ 18Eb
	const char *MKB(const u32_t &i);
	const char *MSEC(const float &sec);
	//------------------------------------------------------------------------------
	u64_t hash()const;
	//------------------------------------------------------------------------------
	int  find(char c)const;
	int rfind(char c)const;
	int  find(const str &s)const;
	int rfind(const str &s)const;
	int  find(const char *s)const;
	int rfind(const char *s)const;
	//------------------------------------------------------------------------------
	const str get_path()const;
	const str get_path_name()const;
	const str get_name_ext()const;
	const str get_ext()const;
	const str get_name()const;
	const str get_last_dir_name() const;
	//------------------------------------------------------------------------------
	static u32_t match(const char *pattern, const char *src);
	//------------------------------------------------------------------------------
	static int get_i32(const char *str);
	static i64_t get_i64(const char *str);
	static float get_f32(const char *str);
	static double get_f64(const char *str);
	static double parse_f64(const char *&s);
	static bool parse_bool(const char *&s);
	static void skip_spaces(const char *&s);
	static bool isnumber(const char *&s);
	static bool parse_name(const char *s, str &rname);
	static u32_t parse_hex(const char *s);
	//------------------------------------------------------------------------------
	static str replace(const str &src, const char *what, const char *to);
};
	
DLL_API bool operator==(const str &s0, const str &s1);
DLL_API	bool operator==(const str &s0, const char *s1);
DLL_API bool operator==(const char *s0, const str &s1);

DLL_API	bool operator!=(const str &s0, const str &s1);
DLL_API	bool operator!=(const str &s0, const char *s1);
DLL_API	bool operator!=(const char *s0, const str &s1);

DLL_API	bool operator>=(const str &s0, const str &s1);
DLL_API	bool operator>=(const str &s0, const char *s1);
DLL_API	bool operator>=(const char *s0, const str &s1);

DLL_API	void str_test_cmp();

static u32_t utf32(const char *chr){
	u32_t result = 0;
	if(!chr)return result;
	if((chr[0] & 0x80) == 0x0)result = chr[0];
	if((chr[0] & 0xC0) == 0xC0)result = ((chr[0] & 0x3F) << 6) | (chr[1] & 0x3F);
	if((chr[0] & 0xE0) == 0xE0)result = ((chr[0] & 0x1F) << (6 + 6)) | ((chr[1] & 0x3F) << 6) | (chr[2] & 0x3F);
	if((chr[0] & 0xF0) == 0xF0)result = ((chr[0] & 0x0F) << (6 + 6 + 6)) | ((chr[1] & 0x3F) << (6 + 6)) | ((chr[2] & 0x3F) << 6) | (chr[3] & 0x3F);
	if((chr[0] & 0xF8) == 0xF8)result = ((chr[0] & 0x07) << (6 + 6 + 6 + 6)) | ((chr[1] & 0x3F) << (6 + 6 + 6)) | ((chr[2] & 0x3F) << (6 + 6)) | ((chr[3] & 0x3F) << 6) | (chr[4] & 0x3F);
	return result;
}
//============================================================================= <SmartStr>
#include "Sys/Tlist.h"
struct PoolStr{//RAII	 sizeof()=4
	TPool<str>::pnode iter;

	PoolStr(){ iter = TPool<str>::Inst().get();iter->data_ptr->clear(); }
	~PoolStr(){ TPool<str>::Inst().free(iter); }
	operator str*()			  { return iter->data_ptr; }
	operator const str*()const{ return iter->data_ptr; }
	str     *operator->()     { return iter->data_ptr; }
	bool operator==(const char *strp)const{ return (*iter->data_ptr) == strp; }
	//str *operator
};//SmartStr
static PoolStr _firstPoolStr_toHoldPoolInstance;

#endif
