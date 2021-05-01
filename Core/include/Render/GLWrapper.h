#ifndef __GL_WRAPPER_H__
#define __GL_WRAPPER_H__ 1

struct GLWrapper{
	GLWrapper();
	static int init();
	static int exit();
};

#ifdef _WIN32
	#include <windows.h>
#endif

#include <GL/gl.h>

#ifndef GET_PROC_NAME
	#define GET_PROC_NAME(NAME) dl ## NAME
#endif

#ifdef _WIN32
	extern HGLRC	(WINAPI *GET_PROC_NAME(wglCreateContext))(HDC);
	extern BOOL		(WINAPI *GET_PROC_NAME(wglDeleteContext))(HGLRC);
	extern HGLRC	(WINAPI *GET_PROC_NAME(wglGetCurrentContext))(VOID);
	extern HDC		(WINAPI *GET_PROC_NAME(wglGetCurrentDC))(VOID);
	extern PROC		(WINAPI *GET_PROC_NAME(wglGetProcAddress))(LPCSTR);
	extern BOOL		(WINAPI *GET_PROC_NAME(wglMakeCurrent))(HDC,HGLRC);
	extern BOOL		(WINAPI *GET_PROC_NAME(wglShareLists))(HGLRC,HGLRC);
#else
	#ifdef GLX_VERSION_1_1
		extern XVisualInfo *	(*GET_PROC_NAME(glXChooseVisual))(Display*,int,int*);
		extern GLXContext		(*GET_PROC_NAME(glXCreateContext))(Display*,XVisualInfo*,GLXContext,Bool);
		extern void				(*GET_PROC_NAME(glXDestroyContext))(Display*,GLXContext);
		extern GLXContext		(*GET_PROC_NAME(glXGetCurrentContext))(void);
		extern GLXDrawable		(*GET_PROC_NAME(glXGetCurrentDrawable))(void);
		extern Bool				(*GET_PROC_NAME(glXMakeCurrent))(Display*,GLXDrawable,GLXContext);
		extern void				(*GET_PROC_NAME(glXSwapBuffers))(Display*,GLXDrawable);
		extern const char *		(*GET_PROC_NAME(glXGetClientString))(Display*,int);
		extern Display *		(*GET_PROC_NAME(glXGetCurrentDisplay))(void);
		extern GLXFBConfig *	(*GET_PROC_NAME(glXChooseFBConfig))(Display*,int,const int*,int*);
		extern GLXPbuffer		(*GET_PROC_NAME(glXCreatePbuffer))(Display*,GLXFBConfig,const int*);
		extern void				(*GET_PROC_NAME(glXDestroyPbuffer))(Display*,GLXPbuffer);
		extern XVisualInfo *	(*GET_PROC_NAME(glXGetVisualFromFBConfig))(Display*,GLXFBConfig);
		extern __GLXextFuncPtr	(*GET_PROC_NAME(glXGetProcAddressARB))(const GLubyte*);
	#endif
#endif

extern void			(APIENTRY *GET_PROC_NAME(glAccum))(GLenum op,GLfloat value);
extern void			(APIENTRY *GET_PROC_NAME(glAlphaFunc))(GLenum func,GLclampf ref);
extern GLboolean	(APIENTRY *GET_PROC_NAME(glAreTexturesResident))(GLsizei n,const GLuint *textures,GLboolean *residences);
extern void			(APIENTRY *GET_PROC_NAME(glArrayElement))(GLint i);
extern void			(APIENTRY *GET_PROC_NAME(glBegin))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glBindTexture))(GLenum target,GLuint texture);
extern void			(APIENTRY *GET_PROC_NAME(glBitmap))(GLsizei width,GLsizei height,GLfloat xorig,GLfloat yorig,GLfloat xmove,GLfloat ymove,const GLubyte *bitmap);
extern void			(APIENTRY *GET_PROC_NAME(glBlendFunc))(GLenum sfactor,GLenum dfactor);
extern void			(APIENTRY *GET_PROC_NAME(glCallList))(GLuint list);
extern void			(APIENTRY *GET_PROC_NAME(glCallLists))(GLsizei n,GLenum type,const GLvoid *lists);
extern void			(APIENTRY *GET_PROC_NAME(glClear))(GLbitfield mask);
extern void			(APIENTRY *GET_PROC_NAME(glClearAccum))(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha);
extern void			(APIENTRY *GET_PROC_NAME(glClearColor))(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha);
extern void			(APIENTRY *GET_PROC_NAME(glClearDepth))(GLclampd depth);
extern void			(APIENTRY *GET_PROC_NAME(glClearIndex))(GLfloat c);
extern void			(APIENTRY *GET_PROC_NAME(glClearStencil))(GLint s);
extern void			(APIENTRY *GET_PROC_NAME(glClipPlane))(GLenum plane,const GLdouble *equation);
extern void			(APIENTRY *GET_PROC_NAME(glColor3b))(GLbyte red,GLbyte green,GLbyte blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3bv))(const GLbyte *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3d))(GLdouble red,GLdouble green,GLdouble blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3f))(GLfloat red,GLfloat green,GLfloat blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3i))(GLint red,GLint green,GLint blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3s))(GLshort red,GLshort green,GLshort blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3ub))(GLubyte red,GLubyte green,GLubyte blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3ubv))(const GLubyte *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3ui))(GLuint red,GLuint green,GLuint blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3uiv))(const GLuint *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor3us))(GLushort red,GLushort green,GLushort blue);
extern void			(APIENTRY *GET_PROC_NAME(glColor3usv))(const GLushort *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4b))(GLbyte red,GLbyte green,GLbyte blue,GLbyte alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4bv))(const GLbyte *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4d))(GLdouble red,GLdouble green,GLdouble blue,GLdouble alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4f))(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4i))(GLint red,GLint green,GLint blue,GLint alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4s))(GLshort red,GLshort green,GLshort blue,GLshort alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4ub))(GLubyte red,GLubyte green,GLubyte blue,GLubyte alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4ubv))(const GLubyte *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4ui))(GLuint red,GLuint green,GLuint blue,GLuint alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4uiv))(const GLuint *v);
extern void			(APIENTRY *GET_PROC_NAME(glColor4us))(GLushort red,GLushort green,GLushort blue,GLushort alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColor4usv))(const GLushort *v);
extern void			(APIENTRY *GET_PROC_NAME(glColorMask))(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha);
extern void			(APIENTRY *GET_PROC_NAME(glColorMaterial))(GLenum face,GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glColorPointer))(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glCopyPixels))(GLint x,GLint y,GLsizei width,GLsizei height,GLenum type);
extern void			(APIENTRY *GET_PROC_NAME(glCopyTexImage1D))(GLenum target,GLint level,GLenum internalFormat,GLint x,GLint y,GLsizei width,GLint border);
extern void			(APIENTRY *GET_PROC_NAME(glCopyTexImage2D))(GLenum target,GLint level,GLenum internalFormat,GLint x,GLint y,GLsizei width,GLsizei height,GLint border);
extern void			(APIENTRY *GET_PROC_NAME(glCopyTexSubImage1D))(GLenum target,GLint level,GLint xoffset,GLint x,GLint y,GLsizei width);
extern void			(APIENTRY *GET_PROC_NAME(glCopyTexSubImage2D))(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei width,GLsizei height);
extern void			(APIENTRY *GET_PROC_NAME(glCullFace))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glDeleteLists))(GLuint list,GLsizei range);
extern void			(APIENTRY *GET_PROC_NAME(glDeleteTextures))(GLsizei n,const GLuint *textures);
extern void			(APIENTRY *GET_PROC_NAME(glDepthFunc))(GLenum func);
extern void			(APIENTRY *GET_PROC_NAME(glDepthMask))(GLboolean flag);
extern void			(APIENTRY *GET_PROC_NAME(glDepthRange))(GLclampd zNear,GLclampd zFar);
extern void			(APIENTRY *GET_PROC_NAME(glDisable))(GLenum cap);
extern void			(APIENTRY *GET_PROC_NAME(glDisableClientState))(GLenum array);
extern void			(APIENTRY *GET_PROC_NAME(glDrawArrays))(GLenum mode,GLint first,GLsizei count);
extern void			(APIENTRY *GET_PROC_NAME(glDrawBuffer))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glDrawElements))(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices);
extern void			(APIENTRY *GET_PROC_NAME(glDrawPixels))(GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glEdgeFlag))(GLboolean flag);
extern void			(APIENTRY *GET_PROC_NAME(glEdgeFlagPointer))(GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glEdgeFlagv))(const GLboolean *flag);
extern void			(APIENTRY *GET_PROC_NAME(glEnable))(GLenum cap);
extern void			(APIENTRY *GET_PROC_NAME(glEnableClientState))(GLenum array);
extern void			(APIENTRY *GET_PROC_NAME(glEnd))(void);
extern void			(APIENTRY *GET_PROC_NAME(glEndList))(void);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord1d))(GLdouble u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord1dv))(const GLdouble *u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord1f))(GLfloat u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord1fv))(const GLfloat *u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord2d))(GLdouble u,GLdouble v);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord2dv))(const GLdouble *u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord2f))(GLfloat u,GLfloat v);
extern void			(APIENTRY *GET_PROC_NAME(glEvalCoord2fv))(const GLfloat *u);
extern void			(APIENTRY *GET_PROC_NAME(glEvalMesh1))(GLenum mode,GLint i1,GLint i2);
extern void			(APIENTRY *GET_PROC_NAME(glEvalMesh2))(GLenum mode,GLint i1,GLint i2,GLint j1,GLint j2);
extern void			(APIENTRY *GET_PROC_NAME(glEvalPoint1))(GLint i);
extern void			(APIENTRY *GET_PROC_NAME(glEvalPoint2))(GLint i,GLint j);
extern void			(APIENTRY *GET_PROC_NAME(glFeedbackBuffer))(GLsizei size,GLenum type,GLfloat *buffer);
extern void			(APIENTRY *GET_PROC_NAME(glFinish))(void);
extern void			(APIENTRY *GET_PROC_NAME(glFlush))(void);
extern void			(APIENTRY *GET_PROC_NAME(glFogf))(GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glFogfv))(GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glFogi))(GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glFogiv))(GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glFrontFace))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glFrustum))(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar);
extern GLuint		(APIENTRY *GET_PROC_NAME(glGenLists))(GLsizei range);
extern void			(APIENTRY *GET_PROC_NAME(glGenTextures))(GLsizei n,GLuint *textures);
extern void			(APIENTRY *GET_PROC_NAME(glGetBooleanv))(GLenum pname,GLboolean *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetClipPlane))(GLenum plane,GLdouble *equation);
extern void			(APIENTRY *GET_PROC_NAME(glGetDoublev))(GLenum pname,GLdouble *params);
extern GLenum		(APIENTRY *GET_PROC_NAME(glGetError))(void);
extern void			(APIENTRY *GET_PROC_NAME(glGetFloatv))(GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetIntegerv))(GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetLightfv))(GLenum light,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetLightiv))(GLenum light,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetMapdv))(GLenum target,GLenum query,GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glGetMapfv))(GLenum target,GLenum query,GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glGetMapiv))(GLenum target,GLenum query,GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glGetMaterialfv))(GLenum face,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetMaterialiv))(GLenum face,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetPixelMapfv))(GLenum map,GLfloat *values);
extern void			(APIENTRY *GET_PROC_NAME(glGetPixelMapuiv))(GLenum map,GLuint *values);
extern void			(APIENTRY *GET_PROC_NAME(glGetPixelMapusv))(GLenum map,GLushort *values);
extern void			(APIENTRY *GET_PROC_NAME(glGetPointerv))(GLenum pname,GLvoid* *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetPolygonStipple))(GLubyte *mask);
extern const char *	(APIENTRY *GET_PROC_NAME(glGetString))(GLenum name);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexEnvfv))(GLenum target,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexEnviv))(GLenum target,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexGendv))(GLenum coord,GLenum pname,GLdouble *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexGenfv))(GLenum coord,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexGeniv))(GLenum coord,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexImage))(GLenum target,GLint level,GLenum format,GLenum type,GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexLevelParameterfv))(GLenum target,GLint level,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexLevelParameteriv))(GLenum target,GLint level,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexParameterfv))(GLenum target,GLenum pname,GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glGetTexParameteriv))(GLenum target,GLenum pname,GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glHint))(GLenum target,GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glIndexMask))(GLuint mask);
extern void			(APIENTRY *GET_PROC_NAME(glIndexPointer))(GLenum type,GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glIndexd))(GLdouble c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexdv))(const GLdouble *c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexf))(GLfloat c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexfv))(const GLfloat *c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexi))(GLint c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexiv))(const GLint *c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexs))(GLshort c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexsv))(const GLshort *c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexub))(GLubyte c);
extern void			(APIENTRY *GET_PROC_NAME(glIndexubv))(const GLubyte *c);
extern void			(APIENTRY *GET_PROC_NAME(glInitNames))(void);
extern void			(APIENTRY *GET_PROC_NAME(glInterleavedArrays))(GLenum format,GLsizei stride,const GLvoid *pointer);
extern GLboolean	(APIENTRY *GET_PROC_NAME(glIsEnabled))(GLenum cap);
extern GLboolean	(APIENTRY *GET_PROC_NAME(glIsList))(GLuint list);
extern GLboolean	(APIENTRY *GET_PROC_NAME(glIsTexture))(GLuint texture);
extern void			(APIENTRY *GET_PROC_NAME(glLightModelf))(GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glLightModelfv))(GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glLightModeli))(GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glLightModeliv))(GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glLightf))(GLenum light,GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glLightfv))(GLenum light,GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glLighti))(GLenum light,GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glLightiv))(GLenum light,GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glLineStipple))(GLint factor,GLushort pattern);
extern void			(APIENTRY *GET_PROC_NAME(glLineWidth))(GLfloat width);
extern void			(APIENTRY *GET_PROC_NAME(glListBase))(GLuint base);
extern void			(APIENTRY *GET_PROC_NAME(glLoadIdentity))(void);
extern void			(APIENTRY *GET_PROC_NAME(glLoadMatrixd))(const GLdouble *m);
extern void			(APIENTRY *GET_PROC_NAME(glLoadMatrixf))(const GLfloat *m);
extern void			(APIENTRY *GET_PROC_NAME(glLoadName))(GLuint name);
extern void			(APIENTRY *GET_PROC_NAME(glLogicOp))(GLenum opcode);
extern void			(APIENTRY *GET_PROC_NAME(glMap1d))(GLenum target,GLdouble u1,GLdouble u2,GLint stride,GLint order,const GLdouble *points);
extern void			(APIENTRY *GET_PROC_NAME(glMap1f))(GLenum target,GLfloat u1,GLfloat u2,GLint stride,GLint order,const GLfloat *points);
extern void			(APIENTRY *GET_PROC_NAME(glMap2d))(GLenum target,GLdouble u1,GLdouble u2,GLint ustride,GLint uorder,GLdouble v1,GLdouble v2,GLint vstride,GLint vorder,const GLdouble *points);
extern void			(APIENTRY *GET_PROC_NAME(glMap2f))(GLenum target,GLfloat u1,GLfloat u2,GLint ustride,GLint uorder,GLfloat v1,GLfloat v2,GLint vstride,GLint vorder,const GLfloat *points);
extern void			(APIENTRY *GET_PROC_NAME(glMapGrid1d))(GLint un,GLdouble u1,GLdouble u2);
extern void			(APIENTRY *GET_PROC_NAME(glMapGrid1f))(GLint un,GLfloat u1,GLfloat u2);
extern void			(APIENTRY *GET_PROC_NAME(glMapGrid2d))(GLint un,GLdouble u1,GLdouble u2,GLint vn,GLdouble v1,GLdouble v2);
extern void			(APIENTRY *GET_PROC_NAME(glMapGrid2f))(GLint un,GLfloat u1,GLfloat u2,GLint vn,GLfloat v1,GLfloat v2);
extern void			(APIENTRY *GET_PROC_NAME(glMaterialf))(GLenum face,GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glMaterialfv))(GLenum face,GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glMateriali))(GLenum face,GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glMaterialiv))(GLenum face,GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glMatrixMode))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glMultMatrixd))(const GLdouble *m);
extern void			(APIENTRY *GET_PROC_NAME(glMultMatrixf))(const GLfloat *m);
extern void			(APIENTRY *GET_PROC_NAME(glNewList))(GLuint list,GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3b))(GLbyte nx,GLbyte ny,GLbyte nz);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3bv))(const GLbyte *v);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3d))(GLdouble nx,GLdouble ny,GLdouble nz);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3f))(GLfloat nx,GLfloat ny,GLfloat nz);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3i))(GLint nx,GLint ny,GLint nz);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3s))(GLshort nx,GLshort ny,GLshort nz);
extern void			(APIENTRY *GET_PROC_NAME(glNormal3sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glNormalPointer))(GLenum type,GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glOrtho))(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar);
extern void			(APIENTRY *GET_PROC_NAME(glPassThrough))(GLfloat token);
extern void			(APIENTRY *GET_PROC_NAME(glPixelMapfv))(GLenum map,GLsizei mapsize,const GLfloat *values);
extern void			(APIENTRY *GET_PROC_NAME(glPixelMapuiv))(GLenum map,GLsizei mapsize,const GLuint *values);
extern void			(APIENTRY *GET_PROC_NAME(glPixelMapusv))(GLenum map,GLsizei mapsize,const GLushort *values);
extern void			(APIENTRY *GET_PROC_NAME(glPixelStoref))(GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glPixelStorei))(GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glPixelTransferf))(GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glPixelTransferi))(GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glPixelZoom))(GLfloat xfactor,GLfloat yfactor);
extern void			(APIENTRY *GET_PROC_NAME(glPointSize))(GLfloat size);
extern void			(APIENTRY *GET_PROC_NAME(glPolygonMode))(GLenum face,GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glPolygonOffset))(GLfloat factor,GLfloat units);
extern void			(APIENTRY *GET_PROC_NAME(glPolygonStipple))(const GLubyte *mask);
extern void			(APIENTRY *GET_PROC_NAME(glPopAttrib))(void);
extern void			(APIENTRY *GET_PROC_NAME(glPopClientAttrib))(void);
extern void			(APIENTRY *GET_PROC_NAME(glPopMatrix))(void);
extern void			(APIENTRY *GET_PROC_NAME(glPopName))(void);
extern void			(APIENTRY *GET_PROC_NAME(glPrioritizeTextures))(GLsizei n,const GLuint *textures,const GLclampf *priorities);
extern void			(APIENTRY *GET_PROC_NAME(glPushAttrib))(GLbitfield mask);
extern void			(APIENTRY *GET_PROC_NAME(glPushClientAttrib))(GLbitfield mask);
extern void			(APIENTRY *GET_PROC_NAME(glPushMatrix))(void);
extern void			(APIENTRY *GET_PROC_NAME(glPushName))(GLuint name);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2d))(GLdouble x,GLdouble y);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2f))(GLfloat x,GLfloat y);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2i))(GLint x,GLint y);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2s))(GLshort x,GLshort y);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos2sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3d))(GLdouble x,GLdouble y,GLdouble z);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3f))(GLfloat x,GLfloat y,GLfloat z);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3i))(GLint x,GLint y,GLint z);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3s))(GLshort x,GLshort y,GLshort z);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos3sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4d))(GLdouble x,GLdouble y,GLdouble z,GLdouble w);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4f))(GLfloat x,GLfloat y,GLfloat z,GLfloat w);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4i))(GLint x,GLint y,GLint z,GLint w);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4s))(GLshort x,GLshort y,GLshort z,GLshort w);
extern void			(APIENTRY *GET_PROC_NAME(glRasterPos4sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glReadBuffer))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glReadPixels))(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glRectd))(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2);
extern void			(APIENTRY *GET_PROC_NAME(glRectdv))(const GLdouble *v1,const GLdouble *v2);
extern void			(APIENTRY *GET_PROC_NAME(glRectf))(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);
extern void			(APIENTRY *GET_PROC_NAME(glRectfv))(const GLfloat *v1,const GLfloat *v2);
extern void			(APIENTRY *GET_PROC_NAME(glRecti))(GLint x1,GLint y1,GLint x2,GLint y2);
extern void			(APIENTRY *GET_PROC_NAME(glRectiv))(const GLint *v1,const GLint *v2);
extern void			(APIENTRY *GET_PROC_NAME(glRects))(GLshort x1,GLshort y1,GLshort x2,GLshort y2);
extern void			(APIENTRY *GET_PROC_NAME(glRectsv))(const GLshort *v1,const GLshort *v2);
extern GLint		(APIENTRY *GET_PROC_NAME(glRenderMode))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glRotated))(GLdouble angle,GLdouble x,GLdouble y,GLdouble z);
extern void			(APIENTRY *GET_PROC_NAME(glRotatef))(GLfloat angle,GLfloat x,GLfloat y,GLfloat z);
extern void			(APIENTRY *GET_PROC_NAME(glScaled))(GLdouble x,GLdouble y,GLdouble z);
extern void			(APIENTRY *GET_PROC_NAME(glScalef))(GLfloat x,GLfloat y,GLfloat z);
extern void			(APIENTRY *GET_PROC_NAME(glScissor))(GLint x,GLint y,GLsizei width,GLsizei height);
extern void			(APIENTRY *GET_PROC_NAME(glSelectBuffer))(GLsizei size,GLuint *buffer);
extern void			(APIENTRY *GET_PROC_NAME(glShadeModel))(GLenum mode);
extern void			(APIENTRY *GET_PROC_NAME(glStencilFunc))(GLenum func,GLint ref,GLuint mask);
extern void			(APIENTRY *GET_PROC_NAME(glStencilMask))(GLuint mask);
extern void			(APIENTRY *GET_PROC_NAME(glStencilOp))(GLenum fail,GLenum zfail,GLenum zpass);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1d))(GLdouble s);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1f))(GLfloat s);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1i))(GLint s);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1s))(GLshort s);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord1sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2d))(GLdouble s,GLdouble t);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2f))(GLfloat s,GLfloat t);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2i))(GLint s,GLint t);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2s))(GLshort s,GLshort t);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord2sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3d))(GLdouble s,GLdouble t,GLdouble r);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3f))(GLfloat s,GLfloat t,GLfloat r);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3i))(GLint s,GLint t,GLint r);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3s))(GLshort s,GLshort t,GLshort r);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord3sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4d))(GLdouble s,GLdouble t,GLdouble r,GLdouble q);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4f))(GLfloat s,GLfloat t,GLfloat r,GLfloat q);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4i))(GLint s,GLint t,GLint r,GLint q);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4s))(GLshort s,GLshort t,GLshort r,GLshort q);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoord4sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glTexCoordPointer))(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glTexEnvf))(GLenum target,GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glTexEnvfv))(GLenum target,GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexEnvi))(GLenum target,GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glTexEnviv))(GLenum target,GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexGend))(GLenum coord,GLenum pname,GLdouble param);
extern void			(APIENTRY *GET_PROC_NAME(glTexGendv))(GLenum coord,GLenum pname,const GLdouble *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexGenf))(GLenum coord,GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glTexGenfv))(GLenum coord,GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexGeni))(GLenum coord,GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glTexGeniv))(GLenum coord,GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexImage1D))(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,const GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glTexImage2D))(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,const GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glTexParameterf))(GLenum target,GLenum pname,GLfloat param);
extern void			(APIENTRY *GET_PROC_NAME(glTexParameterfv))(GLenum target,GLenum pname,const GLfloat *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexParameteri))(GLenum target,GLenum pname,GLint param);
extern void			(APIENTRY *GET_PROC_NAME(glTexParameteriv))(GLenum target,GLenum pname,const GLint *params);
extern void			(APIENTRY *GET_PROC_NAME(glTexSubImage1D))(GLenum target,GLint level,GLint xoffset,GLsizei width,GLenum format,GLenum type,const GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glTexSubImage2D))(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid *pixels);
extern void			(APIENTRY *GET_PROC_NAME(glTranslated))(GLdouble x,GLdouble y,GLdouble z);
extern void			(APIENTRY *GET_PROC_NAME(glTranslatef))(GLfloat x,GLfloat y,GLfloat z);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2d))(GLdouble x,GLdouble y);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2f))(GLfloat x,GLfloat y);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2i))(GLint x,GLint y);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2s))(GLshort x,GLshort y);
extern void			(APIENTRY *GET_PROC_NAME(glVertex2sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3d))(GLdouble x,GLdouble y,GLdouble z);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3f))(GLfloat x,GLfloat y,GLfloat z);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3i))(GLint x,GLint y,GLint z);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3s))(GLshort x,GLshort y,GLshort z);
extern void			(APIENTRY *GET_PROC_NAME(glVertex3sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4d))(GLdouble x,GLdouble y,GLdouble z,GLdouble w);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4dv))(const GLdouble *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4f))(GLfloat x,GLfloat y,GLfloat z,GLfloat w);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4fv))(const GLfloat *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4i))(GLint x,GLint y,GLint z,GLint w);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4iv))(const GLint *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4s))(GLshort x,GLshort y,GLshort z,GLshort w);
extern void			(APIENTRY *GET_PROC_NAME(glVertex4sv))(const GLshort *v);
extern void			(APIENTRY *GET_PROC_NAME(glVertexPointer))(GLint size,GLenum type,GLsizei stride,const GLvoid *pointer);
extern void			(APIENTRY *GET_PROC_NAME(glViewport))(GLint x,GLint y,GLsizei width,GLsizei height);

#ifdef _WIN32
	#define wglCreateContext		GET_PROC_NAME(wglCreateContext)
	#define wglDeleteContext		GET_PROC_NAME(wglDeleteContext)
	#define wglGetCurrentContext	GET_PROC_NAME(wglGetCurrentContext)
	#define wglGetCurrentDC			GET_PROC_NAME(wglGetCurrentDC)
	#define wglGetProcAddress		GET_PROC_NAME(wglGetProcAddress)
	#define wglMakeCurrent			GET_PROC_NAME(wglMakeCurrent)
	#define wglShareLists			GET_PROC_NAME(wglShareLists)
#else
	#ifdef GLX_VERSION_1_1
		#define glXChooseVisual				GET_PROC_NAME(glXChooseVisual)
		#define glXCreateContext			GET_PROC_NAME(glXCreateContext)
		#define glXDestroyContext			GET_PROC_NAME(glXDestroyContext)
		#define glXGetCurrentContext		GET_PROC_NAME(glXGetCurrentContext)
		#define glXGetCurrentDrawable		GET_PROC_NAME(glXGetCurrentDrawable)
		#define glXMakeCurrent				GET_PROC_NAME(glXMakeCurrent)
		#define glXSwapBuffers				GET_PROC_NAME(glXSwapBuffers)
		#define glXGetClientString			GET_PROC_NAME(glXGetClientString)
		#define glXGetCurrentDisplay		GET_PROC_NAME(glXGetCurrentDisplay)
		#define glXChooseFBConfig			GET_PROC_NAME(glXChooseFBConfig)
		#define glXCreatePbuffer			GET_PROC_NAME(glXCreatePbuffer)
		#define glXDestroyPbuffer			GET_PROC_NAME(glXDestroyPbuffer)
		#define glXGetVisualFromFBConfig	GET_PROC_NAME(glXGetVisualFromFBConfig)
		#define glXGetProcAddressARB		GET_PROC_NAME(glXGetProcAddressARB)
	#endif
#endif

#define glAccum						GET_PROC_NAME(glAccum)
#define glAlphaFunc					GET_PROC_NAME(glAlphaFunc)
#define glAreTexturesResident		GET_PROC_NAME(glAreTexturesResident)
#define glArrayElement				GET_PROC_NAME(glArrayElement)
#define glBegin						GET_PROC_NAME(glBegin)
#define glBindTexture				GET_PROC_NAME(glBindTexture)
#define glBitmap					GET_PROC_NAME(glBitmap)
#define glBlendFunc					GET_PROC_NAME(glBlendFunc)
#define glCallList					GET_PROC_NAME(glCallList)
#define glCallLists					GET_PROC_NAME(glCallLists)
#define glClear						GET_PROC_NAME(glClear)
#define glClearAccum				GET_PROC_NAME(glClearAccum)
#define glClearColor				GET_PROC_NAME(glClearColor)
#define glClearDepth				GET_PROC_NAME(glClearDepth)
#define glClearIndex				GET_PROC_NAME(glClearIndex)
#define glClearStencil				GET_PROC_NAME(glClearStencil)
#define glClipPlane					GET_PROC_NAME(glClipPlane)
#define glColor3b					GET_PROC_NAME(glColor3b)
#define glColor3bv					GET_PROC_NAME(glColor3bv)
#define glColor3d					GET_PROC_NAME(glColor3d)
#define glColor3dv					GET_PROC_NAME(glColor3dv)
#define glColor3f					GET_PROC_NAME(glColor3f)
#define glColor3fv					GET_PROC_NAME(glColor3fv)
#define glColor3i					GET_PROC_NAME(glColor3i)
#define glColor3iv					GET_PROC_NAME(glColor3iv)
#define glColor3s					GET_PROC_NAME(glColor3s)
#define glColor3sv					GET_PROC_NAME(glColor3sv)
#define glColor3ub					GET_PROC_NAME(glColor3ub)
#define glColor3ubv					GET_PROC_NAME(glColor3ubv)
#define glColor3ui					GET_PROC_NAME(glColor3ui)
#define glColor3uiv					GET_PROC_NAME(glColor3uiv)
#define glColor3us					GET_PROC_NAME(glColor3us)
#define glColor3usv					GET_PROC_NAME(glColor3usv)
#define glColor4b					GET_PROC_NAME(glColor4b)
#define glColor4bv					GET_PROC_NAME(glColor4bv)
#define glColor4d					GET_PROC_NAME(glColor4d)
#define glColor4dv					GET_PROC_NAME(glColor4dv)
#define glColor4f					GET_PROC_NAME(glColor4f)
#define glColor4fv					GET_PROC_NAME(glColor4fv)
#define glColor4i					GET_PROC_NAME(glColor4i)
#define glColor4iv					GET_PROC_NAME(glColor4iv)
#define glColor4s					GET_PROC_NAME(glColor4s)
#define glColor4sv					GET_PROC_NAME(glColor4sv)
#define glColor4ub					GET_PROC_NAME(glColor4ub)
#define glColor4ubv					GET_PROC_NAME(glColor4ubv)
#define glColor4ui					GET_PROC_NAME(glColor4ui)
#define glColor4uiv					GET_PROC_NAME(glColor4uiv)
#define glColor4us					GET_PROC_NAME(glColor4us)
#define glColor4usv					GET_PROC_NAME(glColor4usv)
#define glColorMask					GET_PROC_NAME(glColorMask)
#define glColorMaterial				GET_PROC_NAME(glColorMaterial)
#define glColorPointer				GET_PROC_NAME(glColorPointer)
#define glCopyPixels				GET_PROC_NAME(glCopyPixels)
#define glCopyTexImage1D			GET_PROC_NAME(glCopyTexImage1D)
#define glCopyTexImage2D			GET_PROC_NAME(glCopyTexImage2D)
#define glCopyTexSubImage1D			GET_PROC_NAME(glCopyTexSubImage1D)
#define glCopyTexSubImage2D			GET_PROC_NAME(glCopyTexSubImage2D)
#define glCullFace					GET_PROC_NAME(glCullFace)
#define glDeleteLists				GET_PROC_NAME(glDeleteLists)
#define glDeleteTextures			GET_PROC_NAME(glDeleteTextures)
#define glDepthFunc					GET_PROC_NAME(glDepthFunc)
#define glDepthMask					GET_PROC_NAME(glDepthMask)
#define glDepthRange				GET_PROC_NAME(glDepthRange)
#define glDisable					GET_PROC_NAME(glDisable)
#define glDisableClientState		GET_PROC_NAME(glDisableClientState)
#define glDrawArrays				GET_PROC_NAME(glDrawArrays)
#define glDrawBuffer				GET_PROC_NAME(glDrawBuffer)
#define glDrawElements				GET_PROC_NAME(glDrawElements)
#define glDrawPixels				GET_PROC_NAME(glDrawPixels)
#define glEdgeFlag					GET_PROC_NAME(glEdgeFlag)
#define glEdgeFlagPointer			GET_PROC_NAME(glEdgeFlagPointer)
#define glEdgeFlagv					GET_PROC_NAME(glEdgeFlagv)
#define glEnable					GET_PROC_NAME(glEnable)
#define glEnableClientState			GET_PROC_NAME(glEnableClientState)
#define glEnd						GET_PROC_NAME(glEnd)
#define glEndList					GET_PROC_NAME(glEndList)
#define glEvalCoord1d				GET_PROC_NAME(glEvalCoord1d)
#define glEvalCoord1dv				GET_PROC_NAME(glEvalCoord1dv)
#define glEvalCoord1f				GET_PROC_NAME(glEvalCoord1f)
#define glEvalCoord1fv				GET_PROC_NAME(glEvalCoord1fv)
#define glEvalCoord2d				GET_PROC_NAME(glEvalCoord2d)
#define glEvalCoord2dv				GET_PROC_NAME(glEvalCoord2dv)
#define glEvalCoord2f				GET_PROC_NAME(glEvalCoord2f)
#define glEvalCoord2fv				GET_PROC_NAME(glEvalCoord2fv)
#define glEvalMesh1					GET_PROC_NAME(glEvalMesh1)
#define glEvalMesh2					GET_PROC_NAME(glEvalMesh2)
#define glEvalPoint1				GET_PROC_NAME(glEvalPoint1)
#define glEvalPoint2				GET_PROC_NAME(glEvalPoint2)
#define glFeedbackBuffer			GET_PROC_NAME(glFeedbackBuffer)
#define glFinish					GET_PROC_NAME(glFinish)
#define glFlush						GET_PROC_NAME(glFlush)
#define glFogf						GET_PROC_NAME(glFogf)
#define glFogfv						GET_PROC_NAME(glFogfv)
#define glFogi						GET_PROC_NAME(glFogi)
#define glFogiv						GET_PROC_NAME(glFogiv)
#define glFrontFace					GET_PROC_NAME(glFrontFace)
#define glFrustum					GET_PROC_NAME(glFrustum)
#define glGenLists					GET_PROC_NAME(glGenLists)
#define glGenTextures				GET_PROC_NAME(glGenTextures)
#define glGetBooleanv				GET_PROC_NAME(glGetBooleanv)
#define glGetClipPlane				GET_PROC_NAME(glGetClipPlane)
#define glGetDoublev				GET_PROC_NAME(glGetDoublev)
#define glGetError					GET_PROC_NAME(glGetError)
#define glGetFloatv					GET_PROC_NAME(glGetFloatv)
#define glGetIntegerv				GET_PROC_NAME(glGetIntegerv)
#define glGetLightfv				GET_PROC_NAME(glGetLightfv)
#define glGetLightiv				GET_PROC_NAME(glGetLightiv)
#define glGetMapdv					GET_PROC_NAME(glGetMapdv)
#define glGetMapfv					GET_PROC_NAME(glGetMapfv)
#define glGetMapiv					GET_PROC_NAME(glGetMapiv)
#define glGetMaterialfv				GET_PROC_NAME(glGetMaterialfv)
#define glGetMaterialiv				GET_PROC_NAME(glGetMaterialiv)
#define glGetPixelMapfv				GET_PROC_NAME(glGetPixelMapfv)
#define glGetPixelMapuiv			GET_PROC_NAME(glGetPixelMapuiv)
#define glGetPixelMapusv			GET_PROC_NAME(glGetPixelMapusv)
#define glGetPointerv				GET_PROC_NAME(glGetPointerv)
#define glGetPolygonStipple			GET_PROC_NAME(glGetPolygonStipple)
#define glGetString					GET_PROC_NAME(glGetString)
#define glGetTexEnvfv				GET_PROC_NAME(glGetTexEnvfv)
#define glGetTexEnviv				GET_PROC_NAME(glGetTexEnviv)
#define glGetTexGendv				GET_PROC_NAME(glGetTexGendv)
#define glGetTexGenfv				GET_PROC_NAME(glGetTexGenfv)
#define glGetTexGeniv				GET_PROC_NAME(glGetTexGeniv)
#define glGetTexImage				GET_PROC_NAME(glGetTexImage)
#define glGetTexLevelParameterfv	GET_PROC_NAME(glGetTexLevelParameterfv)
#define glGetTexLevelParameteriv	GET_PROC_NAME(glGetTexLevelParameteriv)
#define glGetTexParameterfv			GET_PROC_NAME(glGetTexParameterfv)
#define glGetTexParameteriv			GET_PROC_NAME(glGetTexParameteriv)
#define glHint						GET_PROC_NAME(glHint)
#define glIndexMask					GET_PROC_NAME(glIndexMask)
#define glIndexPointer				GET_PROC_NAME(glIndexPointer)
#define glIndexd					GET_PROC_NAME(glIndexd)
#define glIndexdv					GET_PROC_NAME(glIndexdv)
#define glIndexf					GET_PROC_NAME(glIndexf)
#define glIndexfv					GET_PROC_NAME(glIndexfv)
#define glIndexi					GET_PROC_NAME(glIndexi)
#define glIndexiv					GET_PROC_NAME(glIndexiv)
#define glIndexs					GET_PROC_NAME(glIndexs)
#define glIndexsv					GET_PROC_NAME(glIndexsv)
#define glIndexub					GET_PROC_NAME(glIndexub)
#define glIndexubv					GET_PROC_NAME(glIndexubv)
#define glInitNames					GET_PROC_NAME(glInitNames)
#define glInterleavedArrays			GET_PROC_NAME(glInterleavedArrays)
#define glIsEnabled					GET_PROC_NAME(glIsEnabled)
#define glIsList					GET_PROC_NAME(glIsList)
#define glIsTexture					GET_PROC_NAME(glIsTexture)
#define glLightModelf				GET_PROC_NAME(glLightModelf)
#define glLightModelfv				GET_PROC_NAME(glLightModelfv)
#define glLightModeli				GET_PROC_NAME(glLightModeli)
#define glLightModeliv				GET_PROC_NAME(glLightModeliv)
#define glLightf					GET_PROC_NAME(glLightf)
#define glLightfv					GET_PROC_NAME(glLightfv)
#define glLighti					GET_PROC_NAME(glLighti)
#define glLightiv					GET_PROC_NAME(glLightiv)
#define glLineStipple				GET_PROC_NAME(glLineStipple)
#define glLineWidth					GET_PROC_NAME(glLineWidth)
#define glListBase					GET_PROC_NAME(glListBase)
#define glLoadIdentity				GET_PROC_NAME(glLoadIdentity)
#define glLoadMatrixd				GET_PROC_NAME(glLoadMatrixd)
#define glLoadMatrixf				GET_PROC_NAME(glLoadMatrixf)
#define glLoadName					GET_PROC_NAME(glLoadName)
#define glLogicOp					GET_PROC_NAME(glLogicOp)
#define glMap1d						GET_PROC_NAME(glMap1d)
#define glMap1f						GET_PROC_NAME(glMap1f)
#define glMap2d						GET_PROC_NAME(glMap2d)
#define glMap2f						GET_PROC_NAME(glMap2f)
#define glMapGrid1d					GET_PROC_NAME(glMapGrid1d)
#define glMapGrid1f					GET_PROC_NAME(glMapGrid1f)
#define glMapGrid2d					GET_PROC_NAME(glMapGrid2d)
#define glMapGrid2f					GET_PROC_NAME(glMapGrid2f)
#define glMaterialf					GET_PROC_NAME(glMaterialf)
#define glMaterialfv				GET_PROC_NAME(glMaterialfv)
#define glMateriali					GET_PROC_NAME(glMateriali)
#define glMaterialiv				GET_PROC_NAME(glMaterialiv)
#define glMatrixMode				GET_PROC_NAME(glMatrixMode)
#define glMultMatrixd				GET_PROC_NAME(glMultMatrixd)
#define glMultMatrixf				GET_PROC_NAME(glMultMatrixf)
#define glNewList					GET_PROC_NAME(glNewList)
#define glNormal3b					GET_PROC_NAME(glNormal3b)
#define glNormal3bv					GET_PROC_NAME(glNormal3bv)
#define glNormal3d					GET_PROC_NAME(glNormal3d)
#define glNormal3dv					GET_PROC_NAME(glNormal3dv)
#define glNormal3f					GET_PROC_NAME(glNormal3f)
#define glNormal3fv					GET_PROC_NAME(glNormal3fv)
#define glNormal3i					GET_PROC_NAME(glNormal3i)
#define glNormal3iv					GET_PROC_NAME(glNormal3iv)
#define glNormal3s					GET_PROC_NAME(glNormal3s)
#define glNormal3sv					GET_PROC_NAME(glNormal3sv)
#define glNormalPointer				GET_PROC_NAME(glNormalPointer)
#define glOrtho						GET_PROC_NAME(glOrtho)
#define glPassThrough				GET_PROC_NAME(glPassThrough)
#define glPixelMapfv				GET_PROC_NAME(glPixelMapfv)
#define glPixelMapuiv				GET_PROC_NAME(glPixelMapuiv)
#define glPixelMapusv				GET_PROC_NAME(glPixelMapusv)
#define glPixelStoref				GET_PROC_NAME(glPixelStoref)
#define glPixelStorei				GET_PROC_NAME(glPixelStorei)
#define glPixelTransferf			GET_PROC_NAME(glPixelTransferf)
#define glPixelTransferi			GET_PROC_NAME(glPixelTransferi)
#define glPixelZoom					GET_PROC_NAME(glPixelZoom)
#define glPointSize					GET_PROC_NAME(glPointSize)
#define glPolygonMode				GET_PROC_NAME(glPolygonMode)
#define glPolygonOffset				GET_PROC_NAME(glPolygonOffset)
#define glPolygonStipple			GET_PROC_NAME(glPolygonStipple)
#define glPopAttrib					GET_PROC_NAME(glPopAttrib)
#define glPopClientAttrib			GET_PROC_NAME(glPopClientAttrib)
#define glPopMatrix					GET_PROC_NAME(glPopMatrix)
#define glPopName					GET_PROC_NAME(glPopName)
#define glPrioritizeTextures		GET_PROC_NAME(glPrioritizeTextures)
#define glPushAttrib				GET_PROC_NAME(glPushAttrib)
#define glPushClientAttrib			GET_PROC_NAME(glPushClientAttrib)
#define glPushMatrix				GET_PROC_NAME(glPushMatrix)
#define glPushName					GET_PROC_NAME(glPushName)
#define glRasterPos2d				GET_PROC_NAME(glRasterPos2d)
#define glRasterPos2dv				GET_PROC_NAME(glRasterPos2dv)
#define glRasterPos2f				GET_PROC_NAME(glRasterPos2f)
#define glRasterPos2fv				GET_PROC_NAME(glRasterPos2fv)
#define glRasterPos2i				GET_PROC_NAME(glRasterPos2i)
#define glRasterPos2iv				GET_PROC_NAME(glRasterPos2iv)
#define glRasterPos2s				GET_PROC_NAME(glRasterPos2s)
#define glRasterPos2sv				GET_PROC_NAME(glRasterPos2sv)
#define glRasterPos3d				GET_PROC_NAME(glRasterPos3d)
#define glRasterPos3dv				GET_PROC_NAME(glRasterPos3dv)
#define glRasterPos3f				GET_PROC_NAME(glRasterPos3f)
#define glRasterPos3fv				GET_PROC_NAME(glRasterPos3fv)
#define glRasterPos3i				GET_PROC_NAME(glRasterPos3i)
#define glRasterPos3iv				GET_PROC_NAME(glRasterPos3iv)
#define glRasterPos3s				GET_PROC_NAME(glRasterPos3s)
#define glRasterPos3sv				GET_PROC_NAME(glRasterPos3sv)
#define glRasterPos4d				GET_PROC_NAME(glRasterPos4d)
#define glRasterPos4dv				GET_PROC_NAME(glRasterPos4dv)
#define glRasterPos4f				GET_PROC_NAME(glRasterPos4f)
#define glRasterPos4fv				GET_PROC_NAME(glRasterPos4fv)
#define glRasterPos4i				GET_PROC_NAME(glRasterPos4i)
#define glRasterPos4iv				GET_PROC_NAME(glRasterPos4iv)
#define glRasterPos4s				GET_PROC_NAME(glRasterPos4s)
#define glRasterPos4sv				GET_PROC_NAME(glRasterPos4sv)
#define glReadBuffer				GET_PROC_NAME(glReadBuffer)
#define glReadPixels				GET_PROC_NAME(glReadPixels)
#define glRectd						GET_PROC_NAME(glRectd)
#define glRectdv					GET_PROC_NAME(glRectdv)
#define glRectf						GET_PROC_NAME(glRectf)
#define glRectfv					GET_PROC_NAME(glRectfv)
#define glRecti						GET_PROC_NAME(glRecti)
#define glRectiv					GET_PROC_NAME(glRectiv)
#define glRects						GET_PROC_NAME(glRects)
#define glRectsv					GET_PROC_NAME(glRectsv)
#define glRenderMode				GET_PROC_NAME(glRenderMode)
#define glRotated					GET_PROC_NAME(glRotated)
#define glRotatef					GET_PROC_NAME(glRotatef)
#define glScaled					GET_PROC_NAME(glScaled)
#define glScalef					GET_PROC_NAME(glScalef)
#define glScissor					GET_PROC_NAME(glScissor)
#define glSelectBuffer				GET_PROC_NAME(glSelectBuffer)
#define glShadeModel				GET_PROC_NAME(glShadeModel)
#define glStencilFunc				GET_PROC_NAME(glStencilFunc)
#define glStencilMask				GET_PROC_NAME(glStencilMask)
#define glStencilOp					GET_PROC_NAME(glStencilOp)
#define glTexCoord1d				GET_PROC_NAME(glTexCoord1d)
#define glTexCoord1dv				GET_PROC_NAME(glTexCoord1dv)
#define glTexCoord1f				GET_PROC_NAME(glTexCoord1f)
#define glTexCoord1fv				GET_PROC_NAME(glTexCoord1fv)
#define glTexCoord1i				GET_PROC_NAME(glTexCoord1i)
#define glTexCoord1iv				GET_PROC_NAME(glTexCoord1iv)
#define glTexCoord1s				GET_PROC_NAME(glTexCoord1s)
#define glTexCoord1sv				GET_PROC_NAME(glTexCoord1sv)
#define glTexCoord2d				GET_PROC_NAME(glTexCoord2d)
#define glTexCoord2dv				GET_PROC_NAME(glTexCoord2dv)
#define glTexCoord2f				GET_PROC_NAME(glTexCoord2f)
#define glTexCoord2fv				GET_PROC_NAME(glTexCoord2fv)
#define glTexCoord2i				GET_PROC_NAME(glTexCoord2i)
#define glTexCoord2iv				GET_PROC_NAME(glTexCoord2iv)
#define glTexCoord2s				GET_PROC_NAME(glTexCoord2s)
#define glTexCoord2sv				GET_PROC_NAME(glTexCoord2sv)
#define glTexCoord3d				GET_PROC_NAME(glTexCoord3d)
#define glTexCoord3dv				GET_PROC_NAME(glTexCoord3dv)
#define glTexCoord3f				GET_PROC_NAME(glTexCoord3f)
#define glTexCoord3fv				GET_PROC_NAME(glTexCoord3fv)
#define glTexCoord3i				GET_PROC_NAME(glTexCoord3i)
#define glTexCoord3iv				GET_PROC_NAME(glTexCoord3iv)
#define glTexCoord3s				GET_PROC_NAME(glTexCoord3s)
#define glTexCoord3sv				GET_PROC_NAME(glTexCoord3sv)
#define glTexCoord4d				GET_PROC_NAME(glTexCoord4d)
#define glTexCoord4dv				GET_PROC_NAME(glTexCoord4dv)
#define glTexCoord4f				GET_PROC_NAME(glTexCoord4f)
#define glTexCoord4fv				GET_PROC_NAME(glTexCoord4fv)
#define glTexCoord4i				GET_PROC_NAME(glTexCoord4i)
#define glTexCoord4iv				GET_PROC_NAME(glTexCoord4iv)
#define glTexCoord4s				GET_PROC_NAME(glTexCoord4s)
#define glTexCoord4sv				GET_PROC_NAME(glTexCoord4sv)
#define glTexCoordPointer			GET_PROC_NAME(glTexCoordPointer)
#define glTexEnvf					GET_PROC_NAME(glTexEnvf)
#define glTexEnvfv					GET_PROC_NAME(glTexEnvfv)
#define glTexEnvi					GET_PROC_NAME(glTexEnvi)
#define glTexEnviv					GET_PROC_NAME(glTexEnviv)
#define glTexGend					GET_PROC_NAME(glTexGend)
#define glTexGendv					GET_PROC_NAME(glTexGendv)
#define glTexGenf					GET_PROC_NAME(glTexGenf)
#define glTexGenfv					GET_PROC_NAME(glTexGenfv)
#define glTexGeni					GET_PROC_NAME(glTexGeni)
#define glTexGeniv					GET_PROC_NAME(glTexGeniv)
#define glTexImage1D				GET_PROC_NAME(glTexImage1D)
#define glTexImage2D				GET_PROC_NAME(glTexImage2D)
#define glTexParameterf				GET_PROC_NAME(glTexParameterf)
#define glTexParameterfv			GET_PROC_NAME(glTexParameterfv)
#define glTexParameteri				GET_PROC_NAME(glTexParameteri)
#define glTexParameteriv			GET_PROC_NAME(glTexParameteriv)
#define glTexSubImage1D				GET_PROC_NAME(glTexSubImage1D)
#define glTexSubImage2D				GET_PROC_NAME(glTexSubImage2D)
#define glTranslated				GET_PROC_NAME(glTranslated)
#define glTranslatef				GET_PROC_NAME(glTranslatef)
#define glVertex2d					GET_PROC_NAME(glVertex2d)
#define glVertex2dv					GET_PROC_NAME(glVertex2dv)
#define glVertex2f					GET_PROC_NAME(glVertex2f)
#define glVertex2fv					GET_PROC_NAME(glVertex2fv)
#define glVertex2i					GET_PROC_NAME(glVertex2i)
#define glVertex2iv					GET_PROC_NAME(glVertex2iv)
#define glVertex2s					GET_PROC_NAME(glVertex2s)
#define glVertex2sv					GET_PROC_NAME(glVertex2sv)
#define glVertex3d					GET_PROC_NAME(glVertex3d)
#define glVertex3dv					GET_PROC_NAME(glVertex3dv)
#define glVertex3f					GET_PROC_NAME(glVertex3f)
#define glVertex3fv					GET_PROC_NAME(glVertex3fv)
#define glVertex3i					GET_PROC_NAME(glVertex3i)
#define glVertex3iv					GET_PROC_NAME(glVertex3iv)
#define glVertex3s					GET_PROC_NAME(glVertex3s)
#define glVertex3sv					GET_PROC_NAME(glVertex3sv)
#define glVertex4d					GET_PROC_NAME(glVertex4d)
#define glVertex4dv					GET_PROC_NAME(glVertex4dv)
#define glVertex4f					GET_PROC_NAME(glVertex4f)
#define glVertex4fv					GET_PROC_NAME(glVertex4fv)
#define glVertex4i					GET_PROC_NAME(glVertex4i)
#define glVertex4iv					GET_PROC_NAME(glVertex4iv)
#define glVertex4s					GET_PROC_NAME(glVertex4s)
#define glVertex4sv					GET_PROC_NAME(glVertex4sv)
#define glVertexPointer				GET_PROC_NAME(glVertexPointer)
#define glViewport					GET_PROC_NAME(glViewport)

#endif
