#ifndef __TEXTURE_H__
#define __TEXTURE_H__
//=============================================================================
#include "BaseTypes.h"
#include "Sys/Str.h"
#include "Scene/Resource.h"
struct BUFFER;//FD
//=============================================================================
struct DLL_API Texture final : Resource{
	u32_t id;//gl_id
	u16_t w, h, bpp;
	float aspect;
	int param, mode, format, compressed;
	str name;
	enum params { REPEAT = 0, CLAMP, };
	enum formats { DEPTH = 0, DEPTH_STENCIL, RED, RG, RGB, RGBA, RGBA8, COMPRESSED_RGB_S3TC_DXT1, COMPRESSED_RGBA_S3TC_DXT1, COMPRESSED_RGBA_S3TC_DXT3, COMPRESSED_RGBA_S3TC_DXT5, COMPRESSED_RG_RGTC2 };
	enum format_size { DEPTH_SIZE = 1, DEPTH_STENCIL_SIZE = 1, RED_SIZE = 1, RG_SIZE = 2, RGB_SIZE = 3, RGBA_SIZE = 4, RGBA8_SIZE = 4, COMPRESSED_RGB_S3TC_DXT1_SIZE = 1, COMPRESSED_RGBA_S3TC_DXT1_SIZE = 1, COMPRESSED_RGBA_S3TC_DXT3_SIZE = 1, COMPRESSED_RGBA_S3TC_DXT5_SIZE = 1, COMPRESSED_RG_RGTC2_SIZE = 1 };
	u8_t *data;
	//-----------------------------------------------------------------------------
	Texture();
	~Texture();
	//-----------------------------------------------------------------------------
	void Init();
	//-----------------------------------------------------------------------------
	// Setup(w,h, Texture::REPEAT, 0, Texture::RGBA);
	void Setup(u16_t width, u16_t height, int sparam = REPEAT, int smode = 0, int sformat = RGBA8);
	void allocate();
	//-----------------------------------------------------------------------------
	void delGPU();
	void on()const;
	void off()const;
	//-----------------------------------------------------------------------------
	void copy(const Texture &ST);
	//-----------------------------------------------------------------------------
	u32_t GPU(int from_format = RGBA8, bool mipgen = false);
	//-----------------------------------------------------------------------------
	u32_t CheckBoard(const char *nm);
	//-----------------------------------------------------------------------------
	bool Load(BUFFER *B);
	//----------------------------------------------------------------------------- Resource
	//void init() {}
	bool load(const str &filename);
	bool save(const str &filename);
	static const Texture *fallback();
	u32_t res_type() const{ return Resource::TEXTURE; }
	//-----------------------------------------------------------------------------
};
//=============================================================================
#endif
