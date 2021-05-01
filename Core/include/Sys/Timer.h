#ifndef __TIMER_H__
#define __TIMER_H__

#include "BaseTypes.h"
#include "Sys/DLL_API.h"

struct DLL_API Timer{
	double lastTime, frameTime, frameTimeAvg, _ms, _acc , step;
	u32_t frames;
	float fps;
	bool ready;
		
	enum{
		CLOCKS_PER_SECOND = 1000000,
	};

	Timer(const double &new_step = 1.0/10.0);
	~Timer();
		
	static i64_t clocks();
	static double time();// seconds
	static void usleep(u32_t usec);
	static struct str time_str();

	void reset(const double &new_step);
	void getReady();
	bool once();
	bool loop();
};

#endif
