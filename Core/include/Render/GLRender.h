#ifndef __GLWINDOW_H__
#define __GLWINDOW_H__

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
	#include <X11/Xlib.h>
	#include <X11/Xatom.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>
	#include <X11/extensions/Xrandr.h>
	#include <X11/extensions/Xinerama.h>
	#include <GL/gl.h>
	#include <GL/glx.h>
#endif

#include "Render/Render.h"
#include "Math/Maths.h"

struct GLRender final : Render {

	#ifdef _WIN32
		HDC hdc;
		HGLRC context;
	#else
		//XVisualInfo *visual;
		//GLXFBConfig config;
		GLXContext context;
		int need_destroy;
	#endif
	

	DLL_API GLRender();
	virtual ~GLRender();

	void init();
	void cls()const;
	void draw();
	void *init_visual();
	void swap();
	void flush();
	void exit();
	
	void init_visualizer();

	bool VSync(bool state);

	void setCamMat(const Camera &cam);
	void setVP(const vec4 &VP);
	void setOrtho(const float *VP);
	void Scissor(const float *s);
	void Enable(Render::STATE state);
	void Disable(Render::STATE state);
	void BindTexture(Render::STATE, u32_t texid);
	void setModelMatrix(const mat4 &m);
	
	//void Begin(Render::MODE mode);
	void Color(float r, float g, float b, float a);
	void Color(const vec4 &c);
	void Color(const vec3 &c, float a);
	//	void TexCoord(float x, float y);
	//	void Vertex(float x, float y);
	//	void Vertex(float x, float y, float z);
	//	void Vertex(const vec3 &v);
	//void End();

	void Text(const vec3 &scenepos, int center,const str &msg);
	void Text(float x, float y, float w, float h, float gy, float gyh, int center,const str &msg);
	void Axis(const mat4 &m,float len=1.0f);

	void Line(const vec3 &a, const vec3 &b, const vec4 &color, u32_t style = 0);
	void Point(const vec3 &a, const vec4 &color, u32_t style = 0);
	void Triangle(const vec3 &a, const vec3 &b, const vec3 &c,const vec4 &color, u32_t style = 0);
	void Quad(const vec2 &mn, const vec2 &mx, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0);
	void Quad(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0);

	void TextQuad2D(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d, const vec4 &color, const vec4 &uv, u32_t style = 0);
	void TextQuad3D(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec4 &color, const vec4 *uv = nullptr, u32_t style = 0);

	void DrawPoints();
	void DrawLines();
	void DrawTriangles();
	void DrawText2D();
	void DrawText3D();

	void Circle(const vec3 &Rxr, const vec3 &Uxr, const vec3 &pos, const vec4 &col, u32_t segs = 60, int mode=LINE_LOOP, float ang_lim=999);
	void CircleSS(const vec3 &pos, float rad, const vec4 &col, u32_t segs = 60, int mode = LINE_LOOP, float ang_lim = 999);
	void QuadGrid(const mat4 &RM,const vec3 &pos,float fade,float pdist);

	FBOdescriptor *CreateFBO(int w, int h);
	void FBO_begin(const FBOdescriptor *fbo)const;
	void FBO_end(const FBOdescriptor *fbo)const;
	void FBO_bind(const FBOdescriptor *fbo)const;
	void FBO_read(const FBOdescriptor *fbo, Texture *tex)const;
	void LogErrors();

	void StencilShapeBegin();
	void StencilShapeImage(vec2 mn, vec2 mx);
	void StencilShapeEnd();

	void UIInfoPanel();
};

#endif
