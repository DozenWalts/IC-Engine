#ifndef __BUFFER_H__
#define __BUFFER_H__
//=============================================================================
#include "BaseTypes.h"
#include "Sys/Str.h"
//=============================================================================
union FourCC{
	u32_t c;
	u8_t f[4];
	FourCC(u32_t a){ c = a; }
	FourCC(u8_t a, u8_t b, u8_t c, u8_t d){ f[0] = a;f[1] = b;f[2] = c;f[3] = d; }
};
//=============================================================================
static char* fourCC(u32_t code4cc){
	static u64_t rez=0;// 64 to have termzero
	char *st=(char*)&rez;
	st[0] =  code4cc        & 0xff;
	st[1] = (code4cc >>  8) & 0xff;
	st[2] = (code4cc >> 16) & 0xff;
	st[3] = (code4cc >> 24) & 0xff;
	return st;
};
//=============================================================================
static u32_t fourCC(u8_t a, u8_t b, u8_t c, u8_t d){ return a | (b << 8) | (c << 16) | (d << 24); };
static u32_t fourCC(const char *st){return st[0] | (st[1] << 8) | (st[2] << 16) | (st[3] << 24);};
//=============================================================================
//const char *MKB(u32_t size){
//	static Str rez;
//	rez.size=0;
//	u32_t kb=size>>10, mb=kb>>10, gb=mb>>10, b=size-(kb<<10);
//	//if(gb) rez.print(0,"%iGb",gb);
//	//if(mb) rez.print(0,"%s %iMb",rez.text,mb);
//	//if(kb) rez.print(0,"%s %iKb",rez.text,kb);
//	if(b)  rez.print(0,"%ub",b);
//	return rez.text;
//}

//=============================================================================
struct DLL_API BUFFER{
	u32_t size, pos, msize, ready;//ready used_in_thread
	u8_t *buf;
	str fname;
	bool verbose;
	//-----------------------------------------------------------------------------
	BUFFER(){ init(); }
	//-----------------------------------------------------------------------------
	BUFFER(const char *file_name){
		//LOG::msg("BUFFER(%s)",file_name);
		init();
		load(file_name);
	}
	//-----------------------------------------------------------------------------
	void init() {
		size = pos = msize = 0; buf = NULL; fname.init(); verbose = true;
	}
	//-----------------------------------------------------------------------------
	~BUFFER(){
		//if(verbose)LOG::msg("~BUFFER(%s)",fname.text);
		FREE(buf);
	}
	//-----------------------------------------------------------------------------
	void reset(){ size = pos = 0; }
	//-----------------------------------------------------------------------------
	char *ascii(){ return (char*) &buf[pos]; }
	//-----------------------------------------------------------------------------
	bool ascii_next_line(){
		if(pos >= size)return false;
		const u32_t skips = pos;
		//CON_write(0,"start %i",pos);
		while(pos < size && buf[pos] != 0x0D && buf[pos] != 0x0A){ ++pos; };//move untill next line
		while(pos < size && (buf[pos] == 13 || buf[pos] == 10 || buf[pos] == 32))++pos;// skip empty lines
		//CON_write(0, "end %i", pos);
		if(pos >= size)pos = size;
		return skips != pos;
	}
	//-----------------------------------------------------------------------------
	void resize(const u32_t &nsz){
		if(nsz < msize){ size = nsz;return; };
		while(msize <= nsz)msize += 4 * 32;//4*32=128
		RESIZE(buf, u8_t, (msize + 1));// +1 for string ending
		size = nsz;
	}                                                                                        // [pos] not [size] else last chars bugs
	//-----------------------------------------------------------------------------// BUG:resize(size+len+1);size--; (+1 & size--)  (size>>pos)	   CON_write(0,"test pos(%i) len(%i) size=%i mzise=%i",pos,len,size,msize);
	void write(const void *sf, u32_t len){
		if (len == 0 || sf == nullptr)return;
		resize(pos + len);
		memcpy(buf + pos, sf, len);
		pos += len;
		*(buf + pos) = '\0';// if text 
		//CON_write(0,"BUF::write size [%i] %i",len,pos); ok
	}//buf[pos]=0;//CON_write(0,"write:%i",len);loop0i(size)CON_write(0,"buf:%i '%c'",buf[i],buf[i]);
	//-----------------------------------------------------------------------------
	void write(const str &text){
		if(text.size == 0 || text.text == nullptr)return;
		resize(pos + text.size);
		memcpy(buf + pos, text.text, text.size);
		pos += text.size;
		*(buf + pos) = '\0';// if text 
	}
	//-----------------------------------------------------------------------------
	bool read(void *sf, u32_t len){
		if(!len || !size || pos + len > size)return false;
		if(sf != nullptr) memcpy(sf, &buf[pos], len);
		pos += len;
		return true;
	}
	//-----------------------------------------------------------------------------
	bool save(const char *name){
		fname = name;
		FILE *in = fopen(name, "wb");if(!in){ LOG::err("BUFFER::can't save [%s]", name);return false; };
		fwrite(buf, sizeof(u8_t), size, in);
		fclose(in);

		//u32_t kb=size>>10, mb=size>>20;if(mb)kb-=mb<<10;
		str ts;
		LOG::msg("BUFFER::saved [%s] size=%s", name, ts.MKB(size));
		return true;
	}
	//-----------------------------------------------------------------------------
	bool load(const char *name, bool verbose = true){//,const char *mode="rb"){
		//if(verbose)CON_write(2, "BUFFER::from [%s]", fname.text);
		if(name == nullptr) return false;
		this->verbose = verbose;
		fname = name;
		pos = 0;
		FILE *in = fopen(name, "rb");
		if(!in){
			if(verbose) LOG::err("BUFFER::can't load [%s]", name);
			size = 0;
			return false;
		}

		fseek(in, 0, SEEK_END);
		u32_t rsz = ftell(in);
		if(rsz == U32_MAX){
			LOG::err("Buffer [%s] corrupted, ftell=-1");
			return false;
		}
		//if(verbose){LOG::msg("file size = %i",rsz);}
		fseek(in, 0, SEEK_SET);

		resize(rsz);
		fread(buf, sizeof(u8_t), rsz, in);
		buf[rsz] = 0;// clean ending for text files EOS

		fclose(in);
		if(verbose){
			str ts;
			LOG::msg("BUFFER::read [%s] size = %s", name, ts.MKB(rsz));
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	template <typename T> T get_s(u32_t off){ return *(T*) (buf + off); }//u32_t a=BUF.get_s<u32_t>(0);//get 4 bytes call(a)
	template <typename T> T* get_p(u32_t off){ return (T*) (buf + off); }//u32_t *a=BUF.get_p<u32_t>(0);//get 4 bytes call(*a)
	//-----------------------------------------------------------------------------
	u32_t start_chunk(){ u32_t s = 0;write(&s, 4);return pos - 4; }//1
	//-----------------------------------------------------------------------------
	void write_end_chunk(u32_t start_pos){//2
		//CON_write(0,"end chunk pos=%i start=%i size=%i",pos,start_pos,size);
		u32_t c_end = pos;//save end to restore buf pos
		pos = start_pos;//return to chunk_size_pos
		start_pos = (c_end - start_pos);//calc chunk size
		//CON_write(0,"write at %i size=%i",pos,start_pos);
		
		//write(&start_pos, 4);//write chunk size	ALSO makes size=pos+len(1)	< - was bug since write() add '\0' to the end
		memcpy(buf + pos, &start_pos, 4);

		pos = size = c_end;//restore buffer pos & size(2)
		//CON_write(0,"return pos %i size %i",pos,size);
	}
	//-----------------------------------------------------------------------------
	bool read_chunk(u32_t fcc, bool skip){
		u32_t rfcc;read(&rfcc, 4);
		u32_t cs;read(&cs, 4);
		//CON_write(0,"read at %i size=%i",pos-4,cs);
		if(fcc != rfcc){
			pos += skip ? cs : -8;//skip_or_restart
			return false;
		};
		return true;
	}
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
};
//=============================================================================
#endif//BUFFER BUF;
