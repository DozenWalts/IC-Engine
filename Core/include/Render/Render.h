#ifndef __RENDER_H__
#define __RENDER_H__

#include "Sys/DLL_API.h"
#include "Sys/Log.h"
#include "Math/Maths.h"
#include "Render/Texture.h"

#include "Sys/GlyphMap.h"

#include "Render/FFP.h"

//struct mat4;
//struct vec4;
//struct vec3;
struct str;//FD
struct Camera;//FD

struct DLL_API Render{
	mat4 Proj, View, Model, MVP;
	vec4 VP;
	vec4 color;
	u16_t pointSize, lineWidth;// float?	

	u32_t DrawCalls;

	GlyphMap Font;

	FFP Points, Lines, Tris, Text2D, Text3D;

	enum MODE { POINTS=0, LINES, LINE_LOOP, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, QUADS, QUAD_STRIP, POLYGON};//x10 id same as GL_* (PT,L,LL,LS,T,TS,TF,Q,QS,PL)
	//enum MODE_SIZE { POINTS_SIZE = 1, LINES_SIZE = 1, LINE_LOOP_SIZE = 1, LINE_STRIP_SIZE = 1, TRIANGLES_SIZE = 3, TRIANGLE_STRIP_SIZE = 1, TRIANGLE_FAN_SIZE = 1, QUADS_SIZE = 4, QUAD_STRIP_SIZE = 2, POLYGON_SIZE = 1 };
	enum STATE{ NOSTATE = 0, SCISSOR_TEST, TEXTURE_2D, DEPTH_TEST, CULL_FACE, LIGHTING, BLEND,};
	struct FBOdescriptor {
		u32_t DepthBufferId;
		u32_t StencilBufferId;
		u32_t RenderTextureId;
		u32_t RenderFramebufferId;
		u32_t ResolveTextureId;
		u32_t ResolveFramebufferId;
		u32_t Width;
		u32_t Height;
	};
	bool vsync;

	Render(){}
	virtual ~Render(){}

	virtual void init() = 0;
	virtual void cls()const = 0;
	virtual void draw() = 0;
	virtual void *init_visual() = 0;
	virtual void swap() = 0;
	virtual void flush() = 0;
	virtual void exit() = 0;

	virtual void init_visualizer() = 0;

	virtual bool VSync(bool state) = 0;

	virtual void setCamMat(const Camera &cam) = 0;
	virtual void setVP(const vec4 &VP) = 0;
	virtual void setOrtho(const float *VP) = 0;
	virtual void Scissor(const float *s) = 0;
	virtual void Enable(STATE state) = 0;
	virtual void Disable(STATE state) = 0;
	virtual void BindTexture(Render::STATE, u32_t texid) = 0;
	virtual void setModelMatrix(const mat4 &m) = 0;
	
	//virtual void Begin(MODE mode) = 0;
	virtual void Color(float r, float g, float b, float a=1.0f) = 0;
	virtual void Color(const vec4 &c)=0;
	virtual void Color(const vec3 &c, float a) = 0;
	//virtual void TexCoord(float x, float y) = 0;
	//virtual void Vertex(float x, float y) = 0;
	//virtual void Vertex(float x, float y, float z) = 0;
	//virtual void Vertex(vec3 v) = 0;
	//virtual void End() = 0;

    virtual void Text(const vec3 &scenepos, int center,const str &msg) = 0;
    virtual void Text(float x, float y, float w, float h, float gy, float gyh, int center,const str &msg) = 0;
	virtual void Axis(const mat4 &m,float len=1.0f) = 0;

	virtual void Line(const vec3 &a, const vec3 &b, const vec4 &color, u32_t style = 0) = 0;
	virtual void Point(const vec3 &a, const vec4 &color, u32_t style = 0) = 0;
	virtual void Triangle(const vec3 &a, const vec3 &b, const vec3 &c,const vec4 &color, u32_t style = 0) = 0;
	virtual void Quad(const vec2 &mn, const vec2 &mx, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0) = 0;
	virtual void Quad(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0) = 0;

	virtual void TextQuad2D(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d, const vec4 &color, const vec4 &uv, u32_t style = 0) = 0;
	virtual void TextQuad3D(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0) = 0;

	virtual void DrawPoints() = 0;
	virtual void DrawLines() = 0;
	virtual void DrawTriangles() = 0;
	virtual void DrawText2D() = 0;
	virtual void DrawText3D() = 0;

	virtual void Circle(const vec3 &Rxr, const vec3 &Uxr, const vec3 &pos, const vec4 &col, u32_t segs = 60, int mode = LINE_LOOP, float ang_lim = 999) = 0;
	virtual void CircleSS(const vec3 &pos, float rad, const vec4 &col, u32_t segs = 60, int mode = LINE_LOOP, float ang_lim = 999) = 0;

	virtual void QuadGrid(const mat4 &RM,const vec3 &pos,float fade,float pdist) = 0;

	virtual FBOdescriptor *CreateFBO(int w, int h) = 0;
	virtual void FBO_begin(const FBOdescriptor *fbo)const = 0;
	virtual void FBO_end(const FBOdescriptor *fbo)const = 0;
	virtual void FBO_bind(const FBOdescriptor *fbo)const = 0;
	virtual void FBO_read(const FBOdescriptor *fbo, Texture *tex)const = 0;
	virtual void LogErrors() = 0;

	virtual void StencilShapeBegin() = 0;
	virtual void StencilShapeImage(vec2 mn, vec2 mx) = 0;
	virtual void StencilShapeEnd() = 0;

	virtual void UIInfoPanel() = 0;
};

static u32_t PrimSize(u32_t p) {
	switch (p) {
	case Render::QUAD_STRIP: return 2;
	case Render::TRIANGLES: return 3;
	case Render::QUADS: return 4;
	default: return 1;
	}
}

#endif
