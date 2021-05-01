#ifndef __SKELANIM_H__
#define __SKELANIM_H__

#include "Sys/DLL_API.h"
#include "Sys/vector.h"

#include "Math/Maths.h"

#include "Scene/Node.h"

struct Camera;//FD

struct DLL_API AnimCurve{
	u32_t num;
		float *val, *time;// vec4 union?
		float *tanS, *tanE;
		u32_t *modS, *modE;

	AnimCurve();
	~AnimCurve();
	void resize(u32_t sz);

	void set(u32_t i, float t, float v);
	void set(u32_t i, float t, float v, float s, float e, u32_t mode);
	bool has(float t, u32_t &i);
	u32_t get(float t);
	float get(u32_t i);
	u32_t ins(float t);
	void del(float t);
};

struct DLL_API SkelFrame{
	u32_t mt, mr, ms;
	quat *r;
	vec3 *t, *s;
	float *Ttime, *Rtime, *Stime;

	SkelFrame();
	~SkelFrame();
	void init();
	void del();

	void setT(u32_t i, float time, const vec3 &pos);
	bool hasT(float time, u32_t &frame);
	void pushT(float time, const vec3 &pos);
	vec3 getT(float time, u32_t mf);
	vec3 *getT(u32_t frameNum);
	u32_t insT(float time);
	void resizeT(u32_t nmt);
	void delT(float time);

	void setR(u32_t i, float time, const quat &rot);
	bool hasR(float time, u32_t &frame);
	void pushR(float time, const quat &rot);
	quat getR(float time, u32_t mf);
	quat *getR(u32_t frameNum);
	u32_t insR(float time);
	void resizeR(u32_t nmr);
	void delR(float time);

	void setS(u32_t i, float time, const vec3 &scl);
	bool hasS(float time, u32_t &frame);
	void pushS(float time, const vec3 &scl);
	vec3 getS(float time, u32_t mf);
	vec3 *getS(u32_t frameNum);
	u32_t insS(float time);
	void resizeS(u32_t nms);
	void delS(float time);
};

struct DLL_API SkelAnim{
	u32_t mf, mb;
		SkelFrame *f;// mb
	str *abname;// to bind curve to bone by name, if there is
	str name;
	u32_t lap;// animation loop counter
	float frame, w, speed;// move to model?

	SkelAnim();
	~SkelAnim();

	void init();
	void del();
	void resizeB(u32_t nmb);

	void scale(float x);
	bool load(const str *fname);
	//void saveAQTS(BUFFER *B);
	//bool loadAQTS(BUFFER *B);
	vec3 getT(u32_t i);
	quat getR(u32_t i);
	vec3 getS(u32_t i);
};

#endif