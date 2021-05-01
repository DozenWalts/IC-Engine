struct DDS_IMAGE_DATA{
    GLsizei  width;
    GLsizei  height;
    GLint    components;
    GLenum   format;
    int      numMipMaps;
    GLubyte *pixels;
};
//#include <ddraw.h>
#ifndef MAKEFOURCC
	#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
				((u32_t)(u8_t)(ch0) | ((u32_t)(u8_t)(ch1) << 8) |   \
				((u32_t)(u8_t)(ch2) << 16) | ((u32_t)(u8_t)(ch3) << 24 ))
#endif //defined(MAKEFOURCC)
//typedef enum
//{
//	DDS_COMPRESS_NONE = 0,
//	DDS_COMPRESS_BC1, /* DXT1 */
//	DDS_COMPRESS_BC2, /* DXT3 */
//	DDS_COMPRESS_BC3, /* DXT5 */
//	DDS_COMPRESS_BC3N, /* DXT5n */
//	DDS_COMPRESS_BC4, /* ATI1 */
//	DDS_COMPRESS_BC5, /* ATI2 */
//	DDS_COMPRESS_AEXP, /* DXT5 */
//	DDS_COMPRESS_YCOCG, /* DXT5 */
//	DDS_COMPRESS_YCOCGS, /* DXT5 */
//	DDS_COMPRESS_MAX
//} DDS_COMPRESSION_TYPE;
/*
 * FOURCC codes for DX compressed-texture pixel formats
 */
#define FOURCC_DXT1  (MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2  (MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3  (MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4  (MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5  (MAKEFOURCC('D','X','T','5'))
#define FOURCC_ATI2  (MAKEFOURCC('A','T','I','2'))

struct DDCOLORKEY{
	u32_t l,h;
};
typedef struct _DDPIXELFORMAT
{
	u32_t       dwSize;                 // size of structure
	u32_t       dwFlags;                // pixel format flags
	u32_t       dwFourCC;               // (FOURCC code)
	union
	{
		u32_t   dwRGBBitCount;          // how many bits per pixel
		u32_t   dwYUVBitCount;          // how many bits per pixel
		u32_t   dwZBufferBitDepth;      // how many total bits/pixel in z buffer (including any stencil bits)
		u32_t   dwAlphaBitDepth;        // how many bits for alpha channels
		u32_t   dwLuminanceBitCount;    // how many bits per pixel
		u32_t   dwBumpBitCount;         // how many bits per "buxel", total
		u32_t   dwPrivateFormatBitCount;// Bits per pixel of private driver formats. Only valid in texture
										// format list and if DDPF_D3DFORMAT is set
	};// DUMMYUNIONNAMEN(1);
	union
	{
		u32_t   dwRBitMask;             // mask for red bit
		u32_t   dwYBitMask;             // mask for Y bits
		u32_t   dwStencilBitDepth;      // how many stencil bits (note: dwZBufferBitDepth-dwStencilBitDepth is total Z-only bits)
		u32_t   dwLuminanceBitMask;     // mask for luminance bits
		u32_t   dwBumpDuBitMask;        // mask for bump map U delta bits
		u32_t   dwOperations;           // DDPF_D3DFORMAT Operations
	};// DUMMYUNIONNAMEN(2);
	union
	{
		u32_t   dwGBitMask;             // mask for green bits
		u32_t   dwUBitMask;             // mask for U bits
		u32_t   dwZBitMask;             // mask for Z bits
		u32_t   dwBumpDvBitMask;        // mask for bump map V delta bits
		struct
		{
			u16_t    wFlipMSTypes;       // Multisample methods supported via flip for this D3DFORMAT
			u16_t    wBltMSTypes;        // Multisample methods supported via blt for this D3DFORMAT
		} MultiSampleCaps;

	};// DUMMYUNIONNAMEN(3);
	union
	{
		u32_t   dwBBitMask;             // mask for blue bits
		u32_t   dwVBitMask;             // mask for V bits
		u32_t   dwStencilBitMask;       // mask for stencil bits
		u32_t   dwBumpLuminanceBitMask; // mask for luminance in bump map
	};// DUMMYUNIONNAMEN(4);
	union
	{
		u32_t   dwRGBAlphaBitMask;      // mask for alpha channel
		u32_t   dwYUVAlphaBitMask;      // mask for alpha channel
		u32_t   dwLuminanceAlphaBitMask;// mask for alpha channel
		u32_t   dwRGBZBitMask;          // mask for Z channel
		u32_t   dwYUVZBitMask;          // mask for Z channel
	};// DUMMYUNIONNAMEN(5);
} DDPIXELFORMAT;

typedef struct _DDSCAPS2
{
	u32_t       dwCaps;         // capabilities of surface wanted
	u32_t       dwCaps2;
	u32_t       dwCaps3;
	union
	{
		u32_t       dwCaps4;
		u32_t       dwVolumeDepth;
	};// DUMMYUNIONNAMEN(1);
} DDSCAPS2;

struct DDSURFACEDESC2 {
  u32_t      dwSize;
  u32_t      dwFlags;
  u32_t      dwHeight;
  u32_t      dwWidth;
  union {
	i32_t  lPitch;
	u32_t dwLinearSize;
  };
  union {
	u32_t dwBackBufferCount;
	u32_t dwDepth;
  };
  union {
	u32_t dwMipMapCount;
	u32_t dwRefreshRate;
	u32_t dwSrcVBHandle;
  };
  u32_t      dwAlphaBitDepth;
  u32_t      dwReserved;
  void*     lpSurface;
  union {
	DDCOLORKEY ddckCKDestOverlay;
	u32_t      dwEmptyFaceColor;
  };
  DDCOLORKEY ddckCKDestBlt;
  DDCOLORKEY ddckCKSrcOverlay;
  DDCOLORKEY ddckCKSrcBlt;
  union {
	DDPIXELFORMAT ddpfPixelFormat;
	u32_t         dwFVF;
  };
  DDSCAPS2   ddsCaps;
  u32_t      dwTextureStage;
};
/*
struct DDCOLORKEY {
  u32_t dwColorSpaceLowValue;
  u32_t dwColorSpaceHighValue;
};

struct DDPIXELFORMAT {
  u32_t dwSize;
  u32_t dwFlags;
  u32_t dwFourCC;
  union {
	u32_t dwRGBBitCount;
	u32_t dwYUVBitCount;
	u32_t dwZBufferBitDepth;
	u32_t dwAlphaBitDepth;
	u32_t dwLuminanceBitCount;
	u32_t dwBumpBitCount;
	u32_t dwPrivateFormatBitCount;
  };
  union {
	u32_t dwRBitMask;
	u32_t dwYBitMask;
	u32_t dwStencilBitDepth;
	u32_t dwLuminanceBitMask;
	u32_t dwBumpDuBitMask;
	u32_t dwOperations;
  };
  union {
	u32_t  dwGBitMask;
	u32_t  dwUBitMask;
	u32_t  dwZBitMask;
	u32_t  dwBumpDvBitMask;
    struct {
      WORD wFlipMSTypes;
      WORD wBltMSTypes;
    } MultiSampleCaps;
  };
  union {
	u32_t dwBBitMask;
	u32_t dwVBitMask;
	u32_t dwStencilBitMask;
	u32_t dwBumpLuminanceBitMask;
  };
  union {
	u32_t dwRGBAlphaBitMask, dwYUVAlphaBitMask;
	u32_t dwLuminanceAlphaBitMask;
	u32_t dwRGBZBitMask, dwYUVZBitMask;
  };
};

struct DDSCAPS2 {
  u32_t dwCaps;
  u32_t dwCaps2;
  u32_t dwCaps3;
  union {
	u32_t dwCaps4;
	u32_t dwVolumeDepth;
  } DUMMYUNIONNAMEN;
};

struct DDSURFACEDESC2{
  u32_t      dwSize;
  u32_t      dwFlags;
  u32_t      dwHeight;
  u32_t      dwWidth;
  union {
    LONG  lPitch;
	u32_t dwLinearSize;
  };
  union {
	u32_t dwBackBufferCount;
	u32_t dwDepth;
  };
  union {
	u32_t dwMipMapCount;
	u32_t dwRefreshRate;
	u32_t dwSrcVBHandle;
  };
  u32_t      dwAlphaBitDepth;
  u32_t      dwReserved;
  LPVOID     lpSurface;
  union {
    DDCOLORKEY ddckCKDestOverlay;
	u32_t      dwEmptyFaceColor;
  };
  DDCOLORKEY ddckCKDestBlt;
  DDCOLORKEY ddckCKSrcOverlay;
  DDCOLORKEY ddckCKSrcBlt;
  union {
    DDPIXELFORMAT ddpfPixelFormat;
	u32_t         dwFVF;
  };
  DDSCAPS2   ddsCaps;
  u32_t      dwTextureStage;
};
*/
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                  0x83F3

//#include "Render/Texture.h"
int toEngineFormat(int from) {
	switch(from) {
		case GL_COMPRESSED_RGB_S3TC_DXT1_EXT: return Texture::COMPRESSED_RGB_S3TC_DXT1;
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: return Texture::COMPRESSED_RGBA_S3TC_DXT1;
		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT: return Texture::COMPRESSED_RGBA_S3TC_DXT3;
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: return Texture::COMPRESSED_RGBA_S3TC_DXT5;
		case GL_COMPRESSED_RG_RGTC2: return Texture::COMPRESSED_RG_RGTC2;
	}
	return 0;
}

struct DDSLoader{
    DDS_IMAGE_DATA header;
    DDSURFACEDESC2 *ddsd;
    u8_t factor;

//https://developer.unigine.com/docs/2.2/tools/imagedds/
bool Load(BUFFER *B){
    u32_t tag=B->get_s<u32_t>(0);
   // LOG::MSG("tag==[%i]",tag);
    ddsd=B->get_p<DDSURFACEDESC2>(4);
    switch( ddsd->ddpfPixelFormat.dwFourCC ){
        case FOURCC_DXT1:// DXT1's compression ratio is 8:1;	 6:1 (RGB8) RGB
            header.format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
            break;
        case FOURCC_DXT3:// DXT3's compression ratio is 4:1
            header.format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
            break;
        case FOURCC_DXT5:// DXT5's compression ratio is 4:1
            header.format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
            break;
		case FOURCC_ATI2:// ATI2's compression ratio is 2:1 (RG8)  Supported by all DirectX 10 cards and all ATI cards since X800.
			header.format = GL_COMPRESSED_RG_RGTC2;
			factor = 2;
			break;
        default:
            LOG::err("DDS:: format[%s] not compressed DXT1, DXT3, or DXT5", fourCC(ddsd->ddpfPixelFormat.dwFourCC));
            return false;
    }
    header.pixels=B->get_p<GLubyte>(4+sizeof(DDSURFACEDESC2));//fread( pDDSImageData->pixels, 1, bufferSize, pFile );
    header.width      = ddsd->dwWidth;
    header.height     = ddsd->dwHeight;
    header.numMipMaps = ddsd->dwMipMapCount;
	
	header.format = toEngineFormat(header.format);

    if( ddsd->ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        header.components = 3;
    else
        header.components = 4;
    return true;
}
};
