#ifndef __LOG_H__
#define __LOG_H__

#include "DLL_API.h"

//DLL_API FILE *file;

struct DLL_API LOG{
	static  void init(const char *filename);
	static  void exit(const char *format,...);
	static  void msg(const char *format,...);
	static  void warn(const char *format,...);
	static  void err(const char *format,...);
};

#endif
