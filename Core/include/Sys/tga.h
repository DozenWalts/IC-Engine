#ifndef __NANOTGA_H__
#define __NANOTGA_H__

struct NanoTgaLoader {
	int texFormat;
	int width;
	int height;
	unsigned char *data;

	int checkSize(int x) {
		if (x == 2 || x == 4 ||
			x == 8 || x == 16 ||
			x == 32 || x == 64 ||
			x == 128 || x == 256 ||
			x == 512 || x == 1024 ||
			x == 2048 || x == 4096)
			return 1;
		else return 0;
	}

	unsigned char *getRGBA(BUFFER *B, int size) {
		unsigned char temp;
		int i;
		unsigned char *rgba = (unsigned char *)malloc(size * 4); if (rgba == NULL) return 0;
		B->read(rgba, size * 4);
		// TGA is stored in BGRA, make it RGBA
		for (i = 0; i < size * 4; i += 4) {
			temp = rgba[i];
			rgba[i] = rgba[i + 2]; //swap 
			rgba[i + 2] = temp;
		}
		texFormat = Texture::RGBA;
		return rgba;
	}

	unsigned char *getRGB(BUFFER *B, int size) {
		unsigned char temp;
		int i;
		unsigned char *rgb = (unsigned char *)malloc(size * 3); if (rgb == NULL) return 0;
		B->read(rgb, size * 3);
		// TGA is stored in BGR, make it RGB
		for (i = 0; i < size * 3; i += 3) {
			temp = rgb[i];
			rgb[i] = rgb[i + 2];
			rgb[i + 2] = temp;
		}
		texFormat = Texture::RGB;
		return rgb;
	}

	unsigned char *getGray(BUFFER *B, int size) {
		unsigned char *grayData;
		grayData = (unsigned char *)malloc(size); if (grayData == NULL) return 0;
		B->read(grayData, size);
		texFormat = Texture::RED;// ALPHA;
		//texFormat = GL_LUMINANCE;
		return grayData;
	}

	unsigned char *getData(BUFFER *B, int sz, int iBits) {
		if (iBits == 32)return getRGBA(B, sz);
		else if (iBits == 24)return getRGB(B, sz);
		else if (iBits == 8)return getGray(B, sz);
		return NULL;
	}

	bool Load(BUFFER *B) {
		unsigned char type[4];
		unsigned char info[7];

		B->read(&type, 3);// read in colormap info and image type, byte 0 ignored
		if (type[1] != 0 || (type[2] != 2 && type[2] != 3)) { LOG::err("TGA_BAD_IMAGE_TYPE"); return false; }

		B->pos = 12;// seek past the header and useless info
		B->read(&info, 6);
		width = info[0] + info[1] * 256;
		height = info[2] + info[3] * 256;
		if (!checkSize(width) || !checkSize(height)) { LOG::err("TGA_NPOT_SIZE"); return false; }

		int imageBits = info[4];
		if (imageBits != 32 && imageBits != 24 && imageBits != 8) { LOG::err("TGA_UNSUPPORTED_BPP_TYPE"); return false; }

		int size = width * height;
		data = getData(B, size, imageBits);

		// no image data
		if (!data) { LOG::err("TGA_BAD_DATA"); return false; }
		return true;
	}

#pragma pack (push)
#pragma pack (1)	//dont pad the following struct
	struct TGAHeader {//18
		char idlength;				//length of optional identification sequence
		char colourmaptype;			//indicates whether a palette is present
		char datatypecode;			//image data type (e.g., uncompressed RGB)
		short int colourmaporigin;	//first palette index, if present
		short int colourmaplength;	//number of palette entries, if present
		char colourmapdepth;		//number of bits per palette entry
		short int x_origin;			//horiz pixel coordinate of lower left of image
		short int y_origin;//12		//vert pixel coordinate of lower left of image
		short width;
		short height;
		char bitsperpixel;			//image color depth (bits per pixel)
		char imagedescriptor;		//image attribute flags
	};
#pragma pack (pop)

	void Write(BUFFER *B, const char *RGBApixels, int w, int h) {
		TGAHeader header;
		int sz = sizeof(TGAHeader);
		assert(sz == 18);
		memset(&header, 0, sizeof(TGAHeader));
		header.datatypecode = 2;
		header.width = (short)w;
		header.height = (short)h;
		header.bitsperpixel = 32;
		B->write(&header, sizeof(TGAHeader));

		char *offset = 0;
		//for (int y = header.height - 1; y >= 0; y--) {
		loop0i(header.height){
			offset = (char*)RGBApixels + i * header.width * 4;
			for (int x = 0; x < header.width; x++) {
				B->write(offset + 2, 1);//B
				B->write(offset + 1, 1);//G
				B->write(offset + 0, 1);//R
				B->write(offset + 3, 1);//A
				offset += 4;
			}
		}
	}
};
#endif