#include <algorithm>
#include <string.h>
#include <stddef.h>
#include "ogl4.5.hpp"

#if defined(__APPLE__)
#include <dlfcn.h>

static void* AppleGLGetProcAddress (const char *name)
{
	static void* image = NULL;
	
	if (NULL == image)
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

	return (image ? dlsym(image, name) : NULL);
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#pragma warning(disable: 4996)
#endif

static int TestPointer(const PROC pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

static PROC WinGetProcAddress(const char *name)
{
	HMODULE glMod = NULL;
	PROC pFunc = wglGetProcAddress((LPCSTR)name);
	if(TestPointer(pFunc))
	{
		return pFunc;
	}
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}
	
#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
	#if defined(__APPLE__)
		#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define IntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
		    #include <GL/glx.h>

			#define IntGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
		#endif
	#endif
#endif

namespace gl
{
	namespace exts
	{
	}
	
	// Extension: 1.0
	typedef void (CODEGEN_FUNCPTR *PFNBLENDFUNCPROC)(GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARPROC)(GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARDEPTHPROC)(GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARSTENCILPROC)(GLint);
	typedef void (CODEGEN_FUNCPTR *PFNCOLORMASKPROC)(GLboolean, GLboolean, GLboolean, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNCULLFACEPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHFUNCPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHMASKPROC)(GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHRANGEPROC)(GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNDISABLEPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWBUFFERPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNENABLEPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNFINISHPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNFLUSHPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNFRONTFACEPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNGETBOOLEANVPROC)(GLenum, GLboolean *);
	typedef void (CODEGEN_FUNCPTR *PFNGETDOUBLEVPROC)(GLenum, GLdouble *);
	typedef GLenum (CODEGEN_FUNCPTR *PFNGETERRORPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNGETFLOATVPROC)(GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTEGERVPROC)(GLenum, GLint *);
	typedef const GLubyte * (CODEGEN_FUNCPTR *PFNGETSTRINGPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXIMAGEPROC)(GLenum, GLint, GLenum, GLenum, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXLEVELPARAMETERFVPROC)(GLenum, GLint, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXLEVELPARAMETERIVPROC)(GLenum, GLint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXPARAMETERFVPROC)(GLenum, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXPARAMETERIVPROC)(GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNHINTPROC)(GLenum, GLenum);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISENABLEDPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNLINEWIDTHPROC)(GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNLOGICOPPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNPIXELSTOREFPROC)(GLenum, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPIXELSTOREIPROC)(GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPOINTSIZEPROC)(GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPOLYGONMODEPROC)(GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNREADBUFFERPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNREADPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
	typedef void (CODEGEN_FUNCPTR *PFNSCISSORPROC)(GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILFUNCPROC)(GLenum, GLint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILMASKPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILOPPROC)(GLenum, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNTEXIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERFPROC)(GLenum, GLenum, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERFVPROC)(GLenum, GLenum, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERIVPROC)(GLenum, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
	
	// Extension: 1.1
	typedef void (CODEGEN_FUNCPTR *PFNBINDTEXTUREPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDELETETEXTURESPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNGENTEXTURESPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPOINTERVPROC)(GLenum, void **);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISTEXTUREPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPOLYGONOFFSETPROC)(GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
	
	// Extension: 1.2
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWRANGEELEMENTSPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXIMAGE3DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
	
	// Extension: 1.3
	typedef void (CODEGEN_FUNCPTR *PFNACTIVETEXTUREPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXIMAGE3DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, void *);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLECOVERAGEPROC)(GLfloat, GLboolean);
	
	// Extension: 1.4
	typedef void (CODEGEN_FUNCPTR *PFNBLENDCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDEQUATIONPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDFUNCSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNMULTIDRAWARRAYSPROC)(GLenum, const GLint *, const GLsizei *, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNMULTIDRAWELEMENTSPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNPOINTPARAMETERFPROC)(GLenum, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPOINTPARAMETERFVPROC)(GLenum, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPOINTPARAMETERIPROC)(GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPOINTPARAMETERIVPROC)(GLenum, const GLint *);
	
	// Extension: 1.5
	typedef void (CODEGEN_FUNCPTR *PFNBEGINQUERYPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDBUFFERPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBUFFERDATAPROC)(GLenum, GLsizeiptr, const void *, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEBUFFERSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEQUERIESPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNENDQUERYPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNGENBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGENQUERIESPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETBUFFERPOINTERVPROC)(GLenum, GLenum, void **);
	typedef void (CODEGEN_FUNCPTR *PFNGETBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYOBJECTIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYOBJECTUIVPROC)(GLuint, GLenum, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYIVPROC)(GLenum, GLenum, GLint *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISBUFFERPROC)(GLuint);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISQUERYPROC)(GLuint);
	typedef void * (CODEGEN_FUNCPTR *PFNMAPBUFFERPROC)(GLenum, GLenum);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNUNMAPBUFFERPROC)(GLenum);
	
	// Extension: 2.0
	typedef void (CODEGEN_FUNCPTR *PFNATTACHSHADERPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDATTRIBLOCATIONPROC)(GLuint, GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDEQUATIONSEPARATEPROC)(GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPILESHADERPROC)(GLuint);
	typedef GLuint (CODEGEN_FUNCPTR *PFNCREATEPROGRAMPROC)(void);
	typedef GLuint (CODEGEN_FUNCPTR *PFNCREATESHADERPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEPROGRAMPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDELETESHADERPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDETACHSHADERPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWBUFFERSPROC)(GLsizei, const GLenum *);
	typedef void (CODEGEN_FUNCPTR *PFNENABLEVERTEXATTRIBARRAYPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEATTRIBPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEUNIFORMPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETATTACHEDSHADERSPROC)(GLuint, GLsizei, GLsizei *, GLuint *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETATTRIBLOCATIONPROC)(GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSHADERSOURCEPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSHADERIVPROC)(GLuint, GLenum, GLint *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETUNIFORMLOCATIONPROC)(GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMFVPROC)(GLuint, GLint, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMIVPROC)(GLuint, GLint, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBPOINTERVPROC)(GLuint, GLenum, void **);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBDVPROC)(GLuint, GLenum, GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBFVPROC)(GLuint, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBIVPROC)(GLuint, GLenum, GLint *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISPROGRAMPROC)(GLuint);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISSHADERPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNLINKPROGRAMPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar *const*, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILFUNCSEPARATEPROC)(GLenum, GLenum, GLint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILMASKSEPARATEPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNSTENCILOPSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1FPROC)(GLint, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1FVPROC)(GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1IPROC)(GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1IVPROC)(GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2FPROC)(GLint, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2FVPROC)(GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2IPROC)(GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2IVPROC)(GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3IPROC)(GLint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3IVPROC)(GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4FVPROC)(GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4IPROC)(GLint, GLint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4IVPROC)(GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUSEPROGRAMPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVALIDATEPROGRAMPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1DPROC)(GLuint, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1FPROC)(GLuint, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1FVPROC)(GLuint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1SPROC)(GLuint, GLshort);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB1SVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2DPROC)(GLuint, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2FPROC)(GLuint, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2FVPROC)(GLuint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2SPROC)(GLuint, GLshort, GLshort);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB2SVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3FPROC)(GLuint, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3FVPROC)(GLuint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3SPROC)(GLuint, GLshort, GLshort, GLshort);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB3SVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NBVPROC)(GLuint, const GLbyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NIVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NSVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NUBPROC)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NUBVPROC)(GLuint, const GLubyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NUIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4NUSVPROC)(GLuint, const GLushort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4BVPROC)(GLuint, const GLbyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4FPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4FVPROC)(GLuint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4IVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4SPROC)(GLuint, GLshort, GLshort, GLshort, GLshort);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4SVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4UBVPROC)(GLuint, const GLubyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4UIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIB4USVPROC)(GLuint, const GLushort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
	
	// Extension: 2.1
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
	
	// Extension: 3.0
	typedef void (CODEGEN_FUNCPTR *PFNBEGINCONDITIONALRENDERPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBEGINTRANSFORMFEEDBACKPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBINDBUFFERBASEPROC)(GLenum, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDBUFFERRANGEPROC)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNBINDFRAGDATALOCATIONPROC)(GLuint, GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDFRAMEBUFFERPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDRENDERBUFFERPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDVERTEXARRAYPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBLITFRAMEBUFFERPROC)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
	typedef GLenum (CODEGEN_FUNCPTR *PFNCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCLAMPCOLORPROC)(GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERFIPROC)(GLenum, GLint, GLfloat, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERFVPROC)(GLenum, GLint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERIVPROC)(GLenum, GLint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERUIVPROC)(GLenum, GLint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCOLORMASKIPROC)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEFRAMEBUFFERSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDELETERENDERBUFFERSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDISABLEIPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNENABLEIPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNENDCONDITIONALRENDERPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNENDTRANSFORMFEEDBACKPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNFLUSHMAPPEDBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERRENDERBUFFERPROC)(GLenum, GLenum, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERTEXTURE1DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERTEXTURE2DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERTEXTURE3DPROC)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERTEXTURELAYERPROC)(GLenum, GLenum, GLuint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNGENFRAMEBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGENRENDERBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGENVERTEXARRAYSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGENERATEMIPMAPPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNGETBOOLEANI_VPROC)(GLenum, GLuint, GLboolean *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETFRAGDATALOCATIONPROC)(GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum, GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTEGERI_VPROC)(GLenum, GLuint, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETRENDERBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
	typedef const GLubyte * (CODEGEN_FUNCPTR *PFNGETSTRINGIPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXPARAMETERIIVPROC)(GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXPARAMETERIUIVPROC)(GLenum, GLenum, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMUIVPROC)(GLuint, GLint, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBIIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBIUIVPROC)(GLuint, GLenum, GLuint *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISENABLEDIPROC)(GLenum, GLuint);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISFRAMEBUFFERPROC)(GLuint);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISRENDERBUFFERPROC)(GLuint);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISVERTEXARRAYPROC)(GLuint);
	typedef void * (CODEGEN_FUNCPTR *PFNMAPBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNRENDERBUFFERSTORAGEPROC)(GLenum, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERIIVPROC)(GLenum, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXPARAMETERIUIVPROC)(GLenum, GLenum, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNTRANSFORMFEEDBACKVARYINGSPROC)(GLuint, GLsizei, const GLchar *const*, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1UIPROC)(GLint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1UIVPROC)(GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2UIPROC)(GLint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2UIVPROC)(GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3UIPROC)(GLint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3UIVPROC)(GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4UIPROC)(GLint, GLuint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4UIVPROC)(GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI1IPROC)(GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI1IVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI1UIPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI1UIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI2IPROC)(GLuint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI2IVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI2UIPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI2UIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI3IPROC)(GLuint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI3IVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI3UIPROC)(GLuint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI3UIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4BVPROC)(GLuint, const GLbyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4IPROC)(GLuint, GLint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4IVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4SVPROC)(GLuint, const GLshort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4UBVPROC)(GLuint, const GLubyte *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4UIPROC)(GLuint, GLuint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4UIVPROC)(GLuint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBI4USVPROC)(GLuint, const GLushort *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBIPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const void *);
	
	// Extension: 3.1
	typedef void (CODEGEN_FUNCPTR *PFNCOPYBUFFERSUBDATAPROC)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWARRAYSINSTANCEDPROC)(GLenum, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSINSTANCEDPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEUNIFORMBLOCKIVPROC)(GLuint, GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEUNIFORMNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEUNIFORMSIVPROC)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
	typedef GLuint (CODEGEN_FUNCPTR *PFNGETUNIFORMBLOCKINDEXPROC)(GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMINDICESPROC)(GLuint, GLsizei, const GLchar *const*, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNPRIMITIVERESTARTINDEXPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNTEXBUFFERPROC)(GLenum, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMBLOCKBINDINGPROC)(GLuint, GLuint, GLuint);
	
	// Extension: 3.2
	typedef GLenum (CODEGEN_FUNCPTR *PFNCLIENTWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
	typedef void (CODEGEN_FUNCPTR *PFNDELETESYNCPROC)(GLsync);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
	typedef GLsync (CODEGEN_FUNCPTR *PFNFENCESYNCPROC)(GLenum, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERTEXTUREPROC)(GLenum, GLenum, GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNGETBUFFERPARAMETERI64VPROC)(GLenum, GLenum, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTEGER64I_VPROC)(GLenum, GLuint, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTEGER64VPROC)(GLenum, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETMULTISAMPLEFVPROC)(GLenum, GLuint, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSYNCIVPROC)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISSYNCPROC)(GLsync);
	typedef void (CODEGEN_FUNCPTR *PFNMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROVOKINGVERTEXPROC)(GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLEMASKIPROC)(GLuint, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNTEXIMAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNTEXIMAGE3DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
	
	// Extension: 3.3
	typedef void (CODEGEN_FUNCPTR *PFNBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint, GLuint, GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDSAMPLERPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDELETESAMPLERSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGENSAMPLERSPROC)(GLsizei, GLuint *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETFRAGDATAINDEXPROC)(GLuint, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYOBJECTI64VPROC)(GLuint, GLenum, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYOBJECTUI64VPROC)(GLuint, GLenum, GLuint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSAMPLERPARAMETERFVPROC)(GLuint, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSAMPLERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISSAMPLERPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNQUERYCOUNTERPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERFPROC)(GLuint, GLenum, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERFVPROC)(GLuint, GLenum, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERIPROC)(GLuint, GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNSAMPLERPARAMETERIVPROC)(GLuint, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBDIVISORPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP1UIPROC)(GLuint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP1UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP2UIPROC)(GLuint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP2UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP3UIPROC)(GLuint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP3UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP4UIPROC)(GLuint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBP4UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
	
	// Extension: 4.0
	typedef void (CODEGEN_FUNCPTR *PFNBEGINQUERYINDEXEDPROC)(GLenum, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDTRANSFORMFEEDBACKPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDEQUATIONSEPARATEIPROC)(GLuint, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDEQUATIONIPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDFUNCSEPARATEIPROC)(GLuint, GLenum, GLenum, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNBLENDFUNCIPROC)(GLuint, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDELETETRANSFORMFEEDBACKSPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWARRAYSINDIRECTPROC)(GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSINDIRECTPROC)(GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWTRANSFORMFEEDBACKPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNENDQUERYINDEXEDPROC)(GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNGENTRANSFORMFEEDBACKSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVESUBROUTINENAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint, GLenum, GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMSTAGEIVPROC)(GLuint, GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYINDEXEDIVPROC)(GLenum, GLuint, GLenum, GLint *);
	typedef GLuint (CODEGEN_FUNCPTR *PFNGETSUBROUTINEINDEXPROC)(GLuint, GLenum, const GLchar *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint, GLenum, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMSUBROUTINEUIVPROC)(GLenum, GLint, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETUNIFORMDVPROC)(GLuint, GLint, GLdouble *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISTRANSFORMFEEDBACKPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNMINSAMPLESHADINGPROC)(GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPATCHPARAMETERFVPROC)(GLenum, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPATCHPARAMETERIPROC)(GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPAUSETRANSFORMFEEDBACKPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNRESUMETRANSFORMFEEDBACKPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1DPROC)(GLint, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM1DVPROC)(GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2DPROC)(GLint, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM2DVPROC)(GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3DPROC)(GLint, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM3DVPROC)(GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4DPROC)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORM4DVPROC)(GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2X3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX2X4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3X2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX3X4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4X2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMMATRIX4X3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNUNIFORMSUBROUTINESUIVPROC)(GLenum, GLsizei, const GLuint *);
	
	// Extension: 4.1
	typedef void (CODEGEN_FUNCPTR *PFNACTIVESHADERPROGRAMPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBINDPROGRAMPIPELINEPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARDEPTHFPROC)(GLfloat);
	typedef GLuint (CODEGEN_FUNCPTR *PFNCREATESHADERPROGRAMVPROC)(GLenum, GLsizei, const GLchar *const*);
	typedef void (CODEGEN_FUNCPTR *PFNDELETEPROGRAMPIPELINESPROC)(GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHRANGEARRAYVPROC)(GLuint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHRANGEINDEXEDPROC)(GLuint, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNDEPTHRANGEFPROC)(GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNGENPROGRAMPIPELINESPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETDOUBLEI_VPROC)(GLenum, GLuint, GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNGETFLOATI_VPROC)(GLenum, GLuint, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMBINARYPROC)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMPIPELINEINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMPIPELINEIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETSHADERPRECISIONFORMATPROC)(GLenum, GLenum, GLint *, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXATTRIBLDVPROC)(GLuint, GLenum, GLdouble *);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNISPROGRAMPIPELINEPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMBINARYPROC)(GLuint, GLenum, const void *, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMPARAMETERIPROC)(GLuint, GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1DPROC)(GLuint, GLint, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1FPROC)(GLuint, GLint, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1IPROC)(GLuint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1IVPROC)(GLuint, GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1UIPROC)(GLuint, GLint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM1UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2DPROC)(GLuint, GLint, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2FPROC)(GLuint, GLint, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2IPROC)(GLuint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2IVPROC)(GLuint, GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2UIPROC)(GLuint, GLint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM2UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3DPROC)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3FPROC)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3IPROC)(GLuint, GLint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3IVPROC)(GLuint, GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3UIPROC)(GLuint, GLint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM3UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4DPROC)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4FPROC)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4IPROC)(GLuint, GLint, GLint, GLint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4IVPROC)(GLuint, GLint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4UIPROC)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORM4UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNRELEASESHADERCOMPILERPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNSCISSORARRAYVPROC)(GLuint, GLsizei, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNSCISSORINDEXEDPROC)(GLuint, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNSCISSORINDEXEDVPROC)(GLuint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNSHADERBINARYPROC)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNUSEPROGRAMSTAGESPROC)(GLuint, GLbitfield, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVALIDATEPROGRAMPIPELINEPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL1DPROC)(GLuint, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL1DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL2DPROC)(GLuint, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL2DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL3DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBL4DVPROC)(GLuint, const GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBLPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNVIEWPORTARRAYVPROC)(GLuint, GLsizei, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNVIEWPORTINDEXEDFPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNVIEWPORTINDEXEDFVPROC)(GLuint, const GLfloat *);
	
	// Extension: 4.2
	typedef void (CODEGEN_FUNCPTR *PFNBINDIMAGETEXTUREPROC)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum, GLint, GLsizei, GLsizei, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum, GLuint, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum, GLuint, GLuint, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint, GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTERNALFORMATIVPROC)(GLenum, GLenum, GLenum, GLsizei, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNMEMORYBARRIERPROC)(GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSTORAGE1DPROC)(GLenum, GLsizei, GLenum, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSTORAGE2DPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSTORAGE3DPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	
	// Extension: 4.3
	typedef void (CODEGEN_FUNCPTR *PFNBINDVERTEXBUFFERPROC)(GLuint, GLuint, GLintptr, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERDATAPROC)(GLenum, GLenum, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARBUFFERSUBDATAPROC)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYIMAGESUBDATAPROC)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNDEBUGMESSAGECONTROLPROC)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNDEBUGMESSAGEINSERTPROC)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNDISPATCHCOMPUTEPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNDISPATCHCOMPUTEINDIRECTPROC)(GLintptr);
	typedef void (CODEGEN_FUNCPTR *PFNFRAMEBUFFERPARAMETERIPROC)(GLenum, GLenum, GLint);
	typedef GLuint (CODEGEN_FUNCPTR *PFNGETDEBUGMESSAGELOGPROC)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETFRAMEBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETINTERNALFORMATI64VPROC)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETOBJECTLABELPROC)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETOBJECTPTRLABELPROC)(const void *, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMINTERFACEIVPROC)(GLuint, GLenum, GLenum, GLint *);
	typedef GLuint (CODEGEN_FUNCPTR *PFNGETPROGRAMRESOURCEINDEXPROC)(GLuint, GLenum, const GLchar *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETPROGRAMRESOURCELOCATIONPROC)(GLuint, GLenum, const GLchar *);
	typedef GLint (CODEGEN_FUNCPTR *PFNGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint, GLenum, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMRESOURCENAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNGETPROGRAMRESOURCEIVPROC)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATEBUFFERDATAPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATEBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATEFRAMEBUFFERPROC)(GLenum, GLsizei, const GLenum *);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATESUBFRAMEBUFFERPROC)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATETEXIMAGEPROC)(GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATETEXSUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNMULTIDRAWARRAYSINDIRECTPROC)(GLenum, const void *, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNMULTIDRAWELEMENTSINDIRECTPROC)(GLenum, GLenum, const void *, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNOBJECTLABELPROC)(GLenum, GLuint, GLsizei, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNOBJECTPTRLABELPROC)(const void *, GLsizei, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNPOPDEBUGGROUPPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNPUSHDEBUGGROUPPROC)(GLenum, GLuint, GLsizei, const GLchar *);
	typedef void (CODEGEN_FUNCPTR *PFNSHADERSTORAGEBLOCKBINDINGPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNTEXBUFFERRANGEPROC)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSTORAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNTEXSTORAGE3DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREVIEWPROC)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBBINDINGPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBFORMATPROC)(GLuint, GLint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBIFORMATPROC)(GLuint, GLint, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXATTRIBLFORMATPROC)(GLuint, GLint, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXBINDINGDIVISORPROC)(GLuint, GLuint);
	
	// Extension: 4.4
	typedef void (CODEGEN_FUNCPTR *PFNBINDBUFFERSBASEPROC)(GLenum, GLuint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDBUFFERSRANGEPROC)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDIMAGETEXTURESPROC)(GLuint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDSAMPLERSPROC)(GLuint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDTEXTURESPROC)(GLuint, GLsizei, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNBINDVERTEXBUFFERSPROC)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
	typedef void (CODEGEN_FUNCPTR *PFNBUFFERSTORAGEPROC)(GLenum, GLsizeiptr, const void *, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARTEXIMAGEPROC)(GLuint, GLint, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARTEXSUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
	
	// Extension: 4.5
	typedef void (CODEGEN_FUNCPTR *PFNBINDTEXTUREUNITPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNBLITNAMEDFRAMEBUFFERPROC)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
	typedef GLenum (CODEGEN_FUNCPTR *PFNCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDBUFFERDATAPROC)(GLuint, GLenum, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDBUFFERSUBDATAPROC)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint, GLenum, GLint, const GLfloat, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint, GLenum, GLint, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint, GLenum, GLint, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint, GLenum, GLint, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCLIPCONTROLPROC)(GLenum, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYNAMEDBUFFERSUBDATAPROC)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNCOPYTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNCREATEBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATEFRAMEBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATEPROGRAMPIPELINESPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATEQUERIESPROC)(GLenum, GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATERENDERBUFFERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATESAMPLERSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATETEXTURESPROC)(GLenum, GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATETRANSFORMFEEDBACKSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNCREATEVERTEXARRAYSPROC)(GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNDISABLEVERTEXARRAYATTRIBPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNENABLEVERTEXARRAYATTRIBPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNGENERATETEXTUREMIPMAPPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint, GLint, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
	typedef GLenum (CODEGEN_FUNCPTR *PFNGETGRAPHICSRESETSTATUSPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint, GLenum, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDBUFFERPOINTERVPROC)(GLuint, GLenum, void **);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint, GLenum, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYBUFFEROBJECTI64VPROC)(GLuint, GLuint, GLenum, GLintptr);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYBUFFEROBJECTIVPROC)(GLuint, GLuint, GLenum, GLintptr);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYBUFFEROBJECTUI64VPROC)(GLuint, GLuint, GLenum, GLintptr);
	typedef void (CODEGEN_FUNCPTR *PFNGETQUERYBUFFEROBJECTUIVPROC)(GLuint, GLuint, GLenum, GLintptr);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTUREIMAGEPROC)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTURELEVELPARAMETERFVPROC)(GLuint, GLint, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTURELEVELPARAMETERIVPROC)(GLuint, GLint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTUREPARAMETERIIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTUREPARAMETERIUIVPROC)(GLuint, GLenum, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTUREPARAMETERFVPROC)(GLuint, GLenum, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTUREPARAMETERIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTEXTURESUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTRANSFORMFEEDBACKI64_VPROC)(GLuint, GLenum, GLuint, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTRANSFORMFEEDBACKI_VPROC)(GLuint, GLenum, GLuint, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETTRANSFORMFEEDBACKIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXARRAYINDEXED64IVPROC)(GLuint, GLuint, GLenum, GLint64 *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXARRAYINDEXEDIVPROC)(GLuint, GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETVERTEXARRAYIVPROC)(GLuint, GLenum, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNTEXIMAGEPROC)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNUNIFORMDVPROC)(GLuint, GLint, GLsizei, GLdouble *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNUNIFORMFVPROC)(GLuint, GLint, GLsizei, GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNUNIFORMIVPROC)(GLuint, GLint, GLsizei, GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNGETNUNIFORMUIVPROC)(GLuint, GLint, GLsizei, GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint, GLsizei, const GLenum *);
	typedef void (CODEGEN_FUNCPTR *PFNINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
	typedef void * (CODEGEN_FUNCPTR *PFNMAPNAMEDBUFFERPROC)(GLuint, GLenum);
	typedef void * (CODEGEN_FUNCPTR *PFNMAPNAMEDBUFFERRANGEPROC)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNMEMORYBARRIERBYREGIONPROC)(GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDBUFFERDATAPROC)(GLuint, GLsizeiptr, const void *, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDBUFFERSTORAGEPROC)(GLuint, GLsizeiptr, const void *, GLbitfield);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint, GLsizei, const GLenum *);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint, GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint, GLenum);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint, GLenum, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint, GLenum, GLuint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint, GLenum, GLuint, GLint, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDRENDERBUFFERSTORAGEPROC)(GLuint, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNREADNPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREBARRIERPROC)(void);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREBUFFERPROC)(GLuint, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREBUFFERRANGEPROC)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERIIVPROC)(GLuint, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERIUIVPROC)(GLuint, GLenum, const GLuint *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERFPROC)(GLuint, GLenum, GLfloat);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERFVPROC)(GLuint, GLenum, const GLfloat *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERIPROC)(GLuint, GLenum, GLint);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTUREPARAMETERIVPROC)(GLuint, GLenum, const GLint *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESTORAGE1DPROC)(GLuint, GLsizei, GLenum, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESTORAGE2DPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESTORAGE3DPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
	typedef void (CODEGEN_FUNCPTR *PFNTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
	typedef GLboolean (CODEGEN_FUNCPTR *PFNUNMAPNAMEDBUFFERPROC)(GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYATTRIBBINDINGPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYATTRIBFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYATTRIBIFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYATTRIBLFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYBINDINGDIVISORPROC)(GLuint, GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYELEMENTBUFFERPROC)(GLuint, GLuint);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYVERTEXBUFFERPROC)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
	typedef void (CODEGEN_FUNCPTR *PFNVERTEXARRAYVERTEXBUFFERSPROC)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
	
	
	// Extension: 1.0
	PFNBLENDFUNCPROC BlendFunc;
	PFNCLEARPROC Clear;
	PFNCLEARCOLORPROC ClearColor;
	PFNCLEARDEPTHPROC ClearDepth;
	PFNCLEARSTENCILPROC ClearStencil;
	PFNCOLORMASKPROC ColorMask;
	PFNCULLFACEPROC CullFace;
	PFNDEPTHFUNCPROC DepthFunc;
	PFNDEPTHMASKPROC DepthMask;
	PFNDEPTHRANGEPROC DepthRange;
	PFNDISABLEPROC Disable;
	PFNDRAWBUFFERPROC DrawBuffer;
	PFNENABLEPROC Enable;
	PFNFINISHPROC Finish;
	PFNFLUSHPROC Flush;
	PFNFRONTFACEPROC FrontFace;
	PFNGETBOOLEANVPROC GetBooleanv;
	PFNGETDOUBLEVPROC GetDoublev;
	PFNGETERRORPROC GetError;
	PFNGETFLOATVPROC GetFloatv;
	PFNGETINTEGERVPROC GetIntegerv;
	PFNGETSTRINGPROC GetString;
	PFNGETTEXIMAGEPROC GetTexImage;
	PFNGETTEXLEVELPARAMETERFVPROC GetTexLevelParameterfv;
	PFNGETTEXLEVELPARAMETERIVPROC GetTexLevelParameteriv;
	PFNGETTEXPARAMETERFVPROC GetTexParameterfv;
	PFNGETTEXPARAMETERIVPROC GetTexParameteriv;
	PFNHINTPROC Hint;
	PFNISENABLEDPROC IsEnabled;
	PFNLINEWIDTHPROC LineWidth;
	PFNLOGICOPPROC LogicOp;
	PFNPIXELSTOREFPROC PixelStoref;
	PFNPIXELSTOREIPROC PixelStorei;
	PFNPOINTSIZEPROC PointSize;
	PFNPOLYGONMODEPROC PolygonMode;
	PFNREADBUFFERPROC ReadBuffer;
	PFNREADPIXELSPROC ReadPixels;
	PFNSCISSORPROC Scissor;
	PFNSTENCILFUNCPROC StencilFunc;
	PFNSTENCILMASKPROC StencilMask;
	PFNSTENCILOPPROC StencilOp;
	PFNTEXIMAGE1DPROC TexImage1D;
	PFNTEXIMAGE2DPROC TexImage2D;
	PFNTEXPARAMETERFPROC TexParameterf;
	PFNTEXPARAMETERFVPROC TexParameterfv;
	PFNTEXPARAMETERIPROC TexParameteri;
	PFNTEXPARAMETERIVPROC TexParameteriv;
	PFNVIEWPORTPROC Viewport;
	
	// Extension: 1.1
	PFNBINDTEXTUREPROC BindTexture;
	PFNCOPYTEXIMAGE1DPROC CopyTexImage1D;
	PFNCOPYTEXIMAGE2DPROC CopyTexImage2D;
	PFNCOPYTEXSUBIMAGE1DPROC CopyTexSubImage1D;
	PFNCOPYTEXSUBIMAGE2DPROC CopyTexSubImage2D;
	PFNDELETETEXTURESPROC DeleteTextures;
	PFNDRAWARRAYSPROC DrawArrays;
	PFNDRAWELEMENTSPROC DrawElements;
	PFNGENTEXTURESPROC GenTextures;
	PFNGETPOINTERVPROC GetPointerv;
	PFNISTEXTUREPROC IsTexture;
	PFNPOLYGONOFFSETPROC PolygonOffset;
	PFNTEXSUBIMAGE1DPROC TexSubImage1D;
	PFNTEXSUBIMAGE2DPROC TexSubImage2D;
	
	// Extension: 1.2
	PFNCOPYTEXSUBIMAGE3DPROC CopyTexSubImage3D;
	PFNDRAWRANGEELEMENTSPROC DrawRangeElements;
	PFNTEXIMAGE3DPROC TexImage3D;
	PFNTEXSUBIMAGE3DPROC TexSubImage3D;
	
	// Extension: 1.3
	PFNACTIVETEXTUREPROC ActiveTexture;
	PFNCOMPRESSEDTEXIMAGE1DPROC CompressedTexImage1D;
	PFNCOMPRESSEDTEXIMAGE2DPROC CompressedTexImage2D;
	PFNCOMPRESSEDTEXIMAGE3DPROC CompressedTexImage3D;
	PFNCOMPRESSEDTEXSUBIMAGE1DPROC CompressedTexSubImage1D;
	PFNCOMPRESSEDTEXSUBIMAGE2DPROC CompressedTexSubImage2D;
	PFNCOMPRESSEDTEXSUBIMAGE3DPROC CompressedTexSubImage3D;
	PFNGETCOMPRESSEDTEXIMAGEPROC GetCompressedTexImage;
	PFNSAMPLECOVERAGEPROC SampleCoverage;
	
	// Extension: 1.4
	PFNBLENDCOLORPROC BlendColor;
	PFNBLENDEQUATIONPROC BlendEquation;
	PFNBLENDFUNCSEPARATEPROC BlendFuncSeparate;
	PFNMULTIDRAWARRAYSPROC MultiDrawArrays;
	PFNMULTIDRAWELEMENTSPROC MultiDrawElements;
	PFNPOINTPARAMETERFPROC PointParameterf;
	PFNPOINTPARAMETERFVPROC PointParameterfv;
	PFNPOINTPARAMETERIPROC PointParameteri;
	PFNPOINTPARAMETERIVPROC PointParameteriv;
	
	// Extension: 1.5
	PFNBEGINQUERYPROC BeginQuery;
	PFNBINDBUFFERPROC BindBuffer;
	PFNBUFFERDATAPROC BufferData;
	PFNBUFFERSUBDATAPROC BufferSubData;
	PFNDELETEBUFFERSPROC DeleteBuffers;
	PFNDELETEQUERIESPROC DeleteQueries;
	PFNENDQUERYPROC EndQuery;
	PFNGENBUFFERSPROC GenBuffers;
	PFNGENQUERIESPROC GenQueries;
	PFNGETBUFFERPARAMETERIVPROC GetBufferParameteriv;
	PFNGETBUFFERPOINTERVPROC GetBufferPointerv;
	PFNGETBUFFERSUBDATAPROC GetBufferSubData;
	PFNGETQUERYOBJECTIVPROC GetQueryObjectiv;
	PFNGETQUERYOBJECTUIVPROC GetQueryObjectuiv;
	PFNGETQUERYIVPROC GetQueryiv;
	PFNISBUFFERPROC IsBuffer;
	PFNISQUERYPROC IsQuery;
	PFNMAPBUFFERPROC MapBuffer;
	PFNUNMAPBUFFERPROC UnmapBuffer;
	
	// Extension: 2.0
	PFNATTACHSHADERPROC AttachShader;
	PFNBINDATTRIBLOCATIONPROC BindAttribLocation;
	PFNBLENDEQUATIONSEPARATEPROC BlendEquationSeparate;
	PFNCOMPILESHADERPROC CompileShader;
	PFNCREATEPROGRAMPROC CreateProgram;
	PFNCREATESHADERPROC CreateShader;
	PFNDELETEPROGRAMPROC DeleteProgram;
	PFNDELETESHADERPROC DeleteShader;
	PFNDETACHSHADERPROC DetachShader;
	PFNDISABLEVERTEXATTRIBARRAYPROC DisableVertexAttribArray;
	PFNDRAWBUFFERSPROC DrawBuffers;
	PFNENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray;
	PFNGETACTIVEATTRIBPROC GetActiveAttrib;
	PFNGETACTIVEUNIFORMPROC GetActiveUniform;
	PFNGETATTACHEDSHADERSPROC GetAttachedShaders;
	PFNGETATTRIBLOCATIONPROC GetAttribLocation;
	PFNGETPROGRAMINFOLOGPROC GetProgramInfoLog;
	PFNGETPROGRAMIVPROC GetProgramiv;
	PFNGETSHADERINFOLOGPROC GetShaderInfoLog;
	PFNGETSHADERSOURCEPROC GetShaderSource;
	PFNGETSHADERIVPROC GetShaderiv;
	PFNGETUNIFORMLOCATIONPROC GetUniformLocation;
	PFNGETUNIFORMFVPROC GetUniformfv;
	PFNGETUNIFORMIVPROC GetUniformiv;
	PFNGETVERTEXATTRIBPOINTERVPROC GetVertexAttribPointerv;
	PFNGETVERTEXATTRIBDVPROC GetVertexAttribdv;
	PFNGETVERTEXATTRIBFVPROC GetVertexAttribfv;
	PFNGETVERTEXATTRIBIVPROC GetVertexAttribiv;
	PFNISPROGRAMPROC IsProgram;
	PFNISSHADERPROC IsShader;
	PFNLINKPROGRAMPROC LinkProgram;
	PFNSHADERSOURCEPROC ShaderSource;
	PFNSTENCILFUNCSEPARATEPROC StencilFuncSeparate;
	PFNSTENCILMASKSEPARATEPROC StencilMaskSeparate;
	PFNSTENCILOPSEPARATEPROC StencilOpSeparate;
	PFNUNIFORM1FPROC Uniform1f;
	PFNUNIFORM1FVPROC Uniform1fv;
	PFNUNIFORM1IPROC Uniform1i;
	PFNUNIFORM1IVPROC Uniform1iv;
	PFNUNIFORM2FPROC Uniform2f;
	PFNUNIFORM2FVPROC Uniform2fv;
	PFNUNIFORM2IPROC Uniform2i;
	PFNUNIFORM2IVPROC Uniform2iv;
	PFNUNIFORM3FPROC Uniform3f;
	PFNUNIFORM3FVPROC Uniform3fv;
	PFNUNIFORM3IPROC Uniform3i;
	PFNUNIFORM3IVPROC Uniform3iv;
	PFNUNIFORM4FPROC Uniform4f;
	PFNUNIFORM4FVPROC Uniform4fv;
	PFNUNIFORM4IPROC Uniform4i;
	PFNUNIFORM4IVPROC Uniform4iv;
	PFNUNIFORMMATRIX2FVPROC UniformMatrix2fv;
	PFNUNIFORMMATRIX3FVPROC UniformMatrix3fv;
	PFNUNIFORMMATRIX4FVPROC UniformMatrix4fv;
	PFNUSEPROGRAMPROC UseProgram;
	PFNVALIDATEPROGRAMPROC ValidateProgram;
	PFNVERTEXATTRIB1DPROC VertexAttrib1d;
	PFNVERTEXATTRIB1DVPROC VertexAttrib1dv;
	PFNVERTEXATTRIB1FPROC VertexAttrib1f;
	PFNVERTEXATTRIB1FVPROC VertexAttrib1fv;
	PFNVERTEXATTRIB1SPROC VertexAttrib1s;
	PFNVERTEXATTRIB1SVPROC VertexAttrib1sv;
	PFNVERTEXATTRIB2DPROC VertexAttrib2d;
	PFNVERTEXATTRIB2DVPROC VertexAttrib2dv;
	PFNVERTEXATTRIB2FPROC VertexAttrib2f;
	PFNVERTEXATTRIB2FVPROC VertexAttrib2fv;
	PFNVERTEXATTRIB2SPROC VertexAttrib2s;
	PFNVERTEXATTRIB2SVPROC VertexAttrib2sv;
	PFNVERTEXATTRIB3DPROC VertexAttrib3d;
	PFNVERTEXATTRIB3DVPROC VertexAttrib3dv;
	PFNVERTEXATTRIB3FPROC VertexAttrib3f;
	PFNVERTEXATTRIB3FVPROC VertexAttrib3fv;
	PFNVERTEXATTRIB3SPROC VertexAttrib3s;
	PFNVERTEXATTRIB3SVPROC VertexAttrib3sv;
	PFNVERTEXATTRIB4NBVPROC VertexAttrib4Nbv;
	PFNVERTEXATTRIB4NIVPROC VertexAttrib4Niv;
	PFNVERTEXATTRIB4NSVPROC VertexAttrib4Nsv;
	PFNVERTEXATTRIB4NUBPROC VertexAttrib4Nub;
	PFNVERTEXATTRIB4NUBVPROC VertexAttrib4Nubv;
	PFNVERTEXATTRIB4NUIVPROC VertexAttrib4Nuiv;
	PFNVERTEXATTRIB4NUSVPROC VertexAttrib4Nusv;
	PFNVERTEXATTRIB4BVPROC VertexAttrib4bv;
	PFNVERTEXATTRIB4DPROC VertexAttrib4d;
	PFNVERTEXATTRIB4DVPROC VertexAttrib4dv;
	PFNVERTEXATTRIB4FPROC VertexAttrib4f;
	PFNVERTEXATTRIB4FVPROC VertexAttrib4fv;
	PFNVERTEXATTRIB4IVPROC VertexAttrib4iv;
	PFNVERTEXATTRIB4SPROC VertexAttrib4s;
	PFNVERTEXATTRIB4SVPROC VertexAttrib4sv;
	PFNVERTEXATTRIB4UBVPROC VertexAttrib4ubv;
	PFNVERTEXATTRIB4UIVPROC VertexAttrib4uiv;
	PFNVERTEXATTRIB4USVPROC VertexAttrib4usv;
	PFNVERTEXATTRIBPOINTERPROC VertexAttribPointer;
	
	// Extension: 2.1
	PFNUNIFORMMATRIX2X3FVPROC UniformMatrix2x3fv;
	PFNUNIFORMMATRIX2X4FVPROC UniformMatrix2x4fv;
	PFNUNIFORMMATRIX3X2FVPROC UniformMatrix3x2fv;
	PFNUNIFORMMATRIX3X4FVPROC UniformMatrix3x4fv;
	PFNUNIFORMMATRIX4X2FVPROC UniformMatrix4x2fv;
	PFNUNIFORMMATRIX4X3FVPROC UniformMatrix4x3fv;
	
	// Extension: 3.0
	PFNBEGINCONDITIONALRENDERPROC BeginConditionalRender;
	PFNBEGINTRANSFORMFEEDBACKPROC BeginTransformFeedback;
	PFNBINDBUFFERBASEPROC BindBufferBase;
	PFNBINDBUFFERRANGEPROC BindBufferRange;
	PFNBINDFRAGDATALOCATIONPROC BindFragDataLocation;
	PFNBINDFRAMEBUFFERPROC BindFramebuffer;
	PFNBINDRENDERBUFFERPROC BindRenderbuffer;
	PFNBINDVERTEXARRAYPROC BindVertexArray;
	PFNBLITFRAMEBUFFERPROC BlitFramebuffer;
	PFNCHECKFRAMEBUFFERSTATUSPROC CheckFramebufferStatus;
	PFNCLAMPCOLORPROC ClampColor;
	PFNCLEARBUFFERFIPROC ClearBufferfi;
	PFNCLEARBUFFERFVPROC ClearBufferfv;
	PFNCLEARBUFFERIVPROC ClearBufferiv;
	PFNCLEARBUFFERUIVPROC ClearBufferuiv;
	PFNCOLORMASKIPROC ColorMaski;
	PFNDELETEFRAMEBUFFERSPROC DeleteFramebuffers;
	PFNDELETERENDERBUFFERSPROC DeleteRenderbuffers;
	PFNDELETEVERTEXARRAYSPROC DeleteVertexArrays;
	PFNDISABLEIPROC Disablei;
	PFNENABLEIPROC Enablei;
	PFNENDCONDITIONALRENDERPROC EndConditionalRender;
	PFNENDTRANSFORMFEEDBACKPROC EndTransformFeedback;
	PFNFLUSHMAPPEDBUFFERRANGEPROC FlushMappedBufferRange;
	PFNFRAMEBUFFERRENDERBUFFERPROC FramebufferRenderbuffer;
	PFNFRAMEBUFFERTEXTURE1DPROC FramebufferTexture1D;
	PFNFRAMEBUFFERTEXTURE2DPROC FramebufferTexture2D;
	PFNFRAMEBUFFERTEXTURE3DPROC FramebufferTexture3D;
	PFNFRAMEBUFFERTEXTURELAYERPROC FramebufferTextureLayer;
	PFNGENFRAMEBUFFERSPROC GenFramebuffers;
	PFNGENRENDERBUFFERSPROC GenRenderbuffers;
	PFNGENVERTEXARRAYSPROC GenVertexArrays;
	PFNGENERATEMIPMAPPROC GenerateMipmap;
	PFNGETBOOLEANI_VPROC GetBooleani_v;
	PFNGETFRAGDATALOCATIONPROC GetFragDataLocation;
	PFNGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC GetFramebufferAttachmentParameteriv;
	PFNGETINTEGERI_VPROC GetIntegeri_v;
	PFNGETRENDERBUFFERPARAMETERIVPROC GetRenderbufferParameteriv;
	PFNGETSTRINGIPROC GetStringi;
	PFNGETTEXPARAMETERIIVPROC GetTexParameterIiv;
	PFNGETTEXPARAMETERIUIVPROC GetTexParameterIuiv;
	PFNGETTRANSFORMFEEDBACKVARYINGPROC GetTransformFeedbackVarying;
	PFNGETUNIFORMUIVPROC GetUniformuiv;
	PFNGETVERTEXATTRIBIIVPROC GetVertexAttribIiv;
	PFNGETVERTEXATTRIBIUIVPROC GetVertexAttribIuiv;
	PFNISENABLEDIPROC IsEnabledi;
	PFNISFRAMEBUFFERPROC IsFramebuffer;
	PFNISRENDERBUFFERPROC IsRenderbuffer;
	PFNISVERTEXARRAYPROC IsVertexArray;
	PFNMAPBUFFERRANGEPROC MapBufferRange;
	PFNRENDERBUFFERSTORAGEPROC RenderbufferStorage;
	PFNRENDERBUFFERSTORAGEMULTISAMPLEPROC RenderbufferStorageMultisample;
	PFNTEXPARAMETERIIVPROC TexParameterIiv;
	PFNTEXPARAMETERIUIVPROC TexParameterIuiv;
	PFNTRANSFORMFEEDBACKVARYINGSPROC TransformFeedbackVaryings;
	PFNUNIFORM1UIPROC Uniform1ui;
	PFNUNIFORM1UIVPROC Uniform1uiv;
	PFNUNIFORM2UIPROC Uniform2ui;
	PFNUNIFORM2UIVPROC Uniform2uiv;
	PFNUNIFORM3UIPROC Uniform3ui;
	PFNUNIFORM3UIVPROC Uniform3uiv;
	PFNUNIFORM4UIPROC Uniform4ui;
	PFNUNIFORM4UIVPROC Uniform4uiv;
	PFNVERTEXATTRIBI1IPROC VertexAttribI1i;
	PFNVERTEXATTRIBI1IVPROC VertexAttribI1iv;
	PFNVERTEXATTRIBI1UIPROC VertexAttribI1ui;
	PFNVERTEXATTRIBI1UIVPROC VertexAttribI1uiv;
	PFNVERTEXATTRIBI2IPROC VertexAttribI2i;
	PFNVERTEXATTRIBI2IVPROC VertexAttribI2iv;
	PFNVERTEXATTRIBI2UIPROC VertexAttribI2ui;
	PFNVERTEXATTRIBI2UIVPROC VertexAttribI2uiv;
	PFNVERTEXATTRIBI3IPROC VertexAttribI3i;
	PFNVERTEXATTRIBI3IVPROC VertexAttribI3iv;
	PFNVERTEXATTRIBI3UIPROC VertexAttribI3ui;
	PFNVERTEXATTRIBI3UIVPROC VertexAttribI3uiv;
	PFNVERTEXATTRIBI4BVPROC VertexAttribI4bv;
	PFNVERTEXATTRIBI4IPROC VertexAttribI4i;
	PFNVERTEXATTRIBI4IVPROC VertexAttribI4iv;
	PFNVERTEXATTRIBI4SVPROC VertexAttribI4sv;
	PFNVERTEXATTRIBI4UBVPROC VertexAttribI4ubv;
	PFNVERTEXATTRIBI4UIPROC VertexAttribI4ui;
	PFNVERTEXATTRIBI4UIVPROC VertexAttribI4uiv;
	PFNVERTEXATTRIBI4USVPROC VertexAttribI4usv;
	PFNVERTEXATTRIBIPOINTERPROC VertexAttribIPointer;
	
	// Extension: 3.1
	PFNCOPYBUFFERSUBDATAPROC CopyBufferSubData;
	PFNDRAWARRAYSINSTANCEDPROC DrawArraysInstanced;
	PFNDRAWELEMENTSINSTANCEDPROC DrawElementsInstanced;
	PFNGETACTIVEUNIFORMBLOCKNAMEPROC GetActiveUniformBlockName;
	PFNGETACTIVEUNIFORMBLOCKIVPROC GetActiveUniformBlockiv;
	PFNGETACTIVEUNIFORMNAMEPROC GetActiveUniformName;
	PFNGETACTIVEUNIFORMSIVPROC GetActiveUniformsiv;
	PFNGETUNIFORMBLOCKINDEXPROC GetUniformBlockIndex;
	PFNGETUNIFORMINDICESPROC GetUniformIndices;
	PFNPRIMITIVERESTARTINDEXPROC PrimitiveRestartIndex;
	PFNTEXBUFFERPROC TexBuffer;
	PFNUNIFORMBLOCKBINDINGPROC UniformBlockBinding;
	
	// Extension: 3.2
	PFNCLIENTWAITSYNCPROC ClientWaitSync;
	PFNDELETESYNCPROC DeleteSync;
	PFNDRAWELEMENTSBASEVERTEXPROC DrawElementsBaseVertex;
	PFNDRAWELEMENTSINSTANCEDBASEVERTEXPROC DrawElementsInstancedBaseVertex;
	PFNDRAWRANGEELEMENTSBASEVERTEXPROC DrawRangeElementsBaseVertex;
	PFNFENCESYNCPROC FenceSync;
	PFNFRAMEBUFFERTEXTUREPROC FramebufferTexture;
	PFNGETBUFFERPARAMETERI64VPROC GetBufferParameteri64v;
	PFNGETINTEGER64I_VPROC GetInteger64i_v;
	PFNGETINTEGER64VPROC GetInteger64v;
	PFNGETMULTISAMPLEFVPROC GetMultisamplefv;
	PFNGETSYNCIVPROC GetSynciv;
	PFNISSYNCPROC IsSync;
	PFNMULTIDRAWELEMENTSBASEVERTEXPROC MultiDrawElementsBaseVertex;
	PFNPROVOKINGVERTEXPROC ProvokingVertex;
	PFNSAMPLEMASKIPROC SampleMaski;
	PFNTEXIMAGE2DMULTISAMPLEPROC TexImage2DMultisample;
	PFNTEXIMAGE3DMULTISAMPLEPROC TexImage3DMultisample;
	PFNWAITSYNCPROC WaitSync;
	
	// Extension: 3.3
	PFNBINDFRAGDATALOCATIONINDEXEDPROC BindFragDataLocationIndexed;
	PFNBINDSAMPLERPROC BindSampler;
	PFNDELETESAMPLERSPROC DeleteSamplers;
	PFNGENSAMPLERSPROC GenSamplers;
	PFNGETFRAGDATAINDEXPROC GetFragDataIndex;
	PFNGETQUERYOBJECTI64VPROC GetQueryObjecti64v;
	PFNGETQUERYOBJECTUI64VPROC GetQueryObjectui64v;
	PFNGETSAMPLERPARAMETERIIVPROC GetSamplerParameterIiv;
	PFNGETSAMPLERPARAMETERIUIVPROC GetSamplerParameterIuiv;
	PFNGETSAMPLERPARAMETERFVPROC GetSamplerParameterfv;
	PFNGETSAMPLERPARAMETERIVPROC GetSamplerParameteriv;
	PFNISSAMPLERPROC IsSampler;
	PFNQUERYCOUNTERPROC QueryCounter;
	PFNSAMPLERPARAMETERIIVPROC SamplerParameterIiv;
	PFNSAMPLERPARAMETERIUIVPROC SamplerParameterIuiv;
	PFNSAMPLERPARAMETERFPROC SamplerParameterf;
	PFNSAMPLERPARAMETERFVPROC SamplerParameterfv;
	PFNSAMPLERPARAMETERIPROC SamplerParameteri;
	PFNSAMPLERPARAMETERIVPROC SamplerParameteriv;
	PFNVERTEXATTRIBDIVISORPROC VertexAttribDivisor;
	PFNVERTEXATTRIBP1UIPROC VertexAttribP1ui;
	PFNVERTEXATTRIBP1UIVPROC VertexAttribP1uiv;
	PFNVERTEXATTRIBP2UIPROC VertexAttribP2ui;
	PFNVERTEXATTRIBP2UIVPROC VertexAttribP2uiv;
	PFNVERTEXATTRIBP3UIPROC VertexAttribP3ui;
	PFNVERTEXATTRIBP3UIVPROC VertexAttribP3uiv;
	PFNVERTEXATTRIBP4UIPROC VertexAttribP4ui;
	PFNVERTEXATTRIBP4UIVPROC VertexAttribP4uiv;
	
	// Extension: 4.0
	PFNBEGINQUERYINDEXEDPROC BeginQueryIndexed;
	PFNBINDTRANSFORMFEEDBACKPROC BindTransformFeedback;
	PFNBLENDEQUATIONSEPARATEIPROC BlendEquationSeparatei;
	PFNBLENDEQUATIONIPROC BlendEquationi;
	PFNBLENDFUNCSEPARATEIPROC BlendFuncSeparatei;
	PFNBLENDFUNCIPROC BlendFunci;
	PFNDELETETRANSFORMFEEDBACKSPROC DeleteTransformFeedbacks;
	PFNDRAWARRAYSINDIRECTPROC DrawArraysIndirect;
	PFNDRAWELEMENTSINDIRECTPROC DrawElementsIndirect;
	PFNDRAWTRANSFORMFEEDBACKPROC DrawTransformFeedback;
	PFNDRAWTRANSFORMFEEDBACKSTREAMPROC DrawTransformFeedbackStream;
	PFNENDQUERYINDEXEDPROC EndQueryIndexed;
	PFNGENTRANSFORMFEEDBACKSPROC GenTransformFeedbacks;
	PFNGETACTIVESUBROUTINENAMEPROC GetActiveSubroutineName;
	PFNGETACTIVESUBROUTINEUNIFORMNAMEPROC GetActiveSubroutineUniformName;
	PFNGETACTIVESUBROUTINEUNIFORMIVPROC GetActiveSubroutineUniformiv;
	PFNGETPROGRAMSTAGEIVPROC GetProgramStageiv;
	PFNGETQUERYINDEXEDIVPROC GetQueryIndexediv;
	PFNGETSUBROUTINEINDEXPROC GetSubroutineIndex;
	PFNGETSUBROUTINEUNIFORMLOCATIONPROC GetSubroutineUniformLocation;
	PFNGETUNIFORMSUBROUTINEUIVPROC GetUniformSubroutineuiv;
	PFNGETUNIFORMDVPROC GetUniformdv;
	PFNISTRANSFORMFEEDBACKPROC IsTransformFeedback;
	PFNMINSAMPLESHADINGPROC MinSampleShading;
	PFNPATCHPARAMETERFVPROC PatchParameterfv;
	PFNPATCHPARAMETERIPROC PatchParameteri;
	PFNPAUSETRANSFORMFEEDBACKPROC PauseTransformFeedback;
	PFNRESUMETRANSFORMFEEDBACKPROC ResumeTransformFeedback;
	PFNUNIFORM1DPROC Uniform1d;
	PFNUNIFORM1DVPROC Uniform1dv;
	PFNUNIFORM2DPROC Uniform2d;
	PFNUNIFORM2DVPROC Uniform2dv;
	PFNUNIFORM3DPROC Uniform3d;
	PFNUNIFORM3DVPROC Uniform3dv;
	PFNUNIFORM4DPROC Uniform4d;
	PFNUNIFORM4DVPROC Uniform4dv;
	PFNUNIFORMMATRIX2DVPROC UniformMatrix2dv;
	PFNUNIFORMMATRIX2X3DVPROC UniformMatrix2x3dv;
	PFNUNIFORMMATRIX2X4DVPROC UniformMatrix2x4dv;
	PFNUNIFORMMATRIX3DVPROC UniformMatrix3dv;
	PFNUNIFORMMATRIX3X2DVPROC UniformMatrix3x2dv;
	PFNUNIFORMMATRIX3X4DVPROC UniformMatrix3x4dv;
	PFNUNIFORMMATRIX4DVPROC UniformMatrix4dv;
	PFNUNIFORMMATRIX4X2DVPROC UniformMatrix4x2dv;
	PFNUNIFORMMATRIX4X3DVPROC UniformMatrix4x3dv;
	PFNUNIFORMSUBROUTINESUIVPROC UniformSubroutinesuiv;
	
	// Extension: 4.1
	PFNACTIVESHADERPROGRAMPROC ActiveShaderProgram;
	PFNBINDPROGRAMPIPELINEPROC BindProgramPipeline;
	PFNCLEARDEPTHFPROC ClearDepthf;
	PFNCREATESHADERPROGRAMVPROC CreateShaderProgramv;
	PFNDELETEPROGRAMPIPELINESPROC DeleteProgramPipelines;
	PFNDEPTHRANGEARRAYVPROC DepthRangeArrayv;
	PFNDEPTHRANGEINDEXEDPROC DepthRangeIndexed;
	PFNDEPTHRANGEFPROC DepthRangef;
	PFNGENPROGRAMPIPELINESPROC GenProgramPipelines;
	PFNGETDOUBLEI_VPROC GetDoublei_v;
	PFNGETFLOATI_VPROC GetFloati_v;
	PFNGETPROGRAMBINARYPROC GetProgramBinary;
	PFNGETPROGRAMPIPELINEINFOLOGPROC GetProgramPipelineInfoLog;
	PFNGETPROGRAMPIPELINEIVPROC GetProgramPipelineiv;
	PFNGETSHADERPRECISIONFORMATPROC GetShaderPrecisionFormat;
	PFNGETVERTEXATTRIBLDVPROC GetVertexAttribLdv;
	PFNISPROGRAMPIPELINEPROC IsProgramPipeline;
	PFNPROGRAMBINARYPROC ProgramBinary;
	PFNPROGRAMPARAMETERIPROC ProgramParameteri;
	PFNPROGRAMUNIFORM1DPROC ProgramUniform1d;
	PFNPROGRAMUNIFORM1DVPROC ProgramUniform1dv;
	PFNPROGRAMUNIFORM1FPROC ProgramUniform1f;
	PFNPROGRAMUNIFORM1FVPROC ProgramUniform1fv;
	PFNPROGRAMUNIFORM1IPROC ProgramUniform1i;
	PFNPROGRAMUNIFORM1IVPROC ProgramUniform1iv;
	PFNPROGRAMUNIFORM1UIPROC ProgramUniform1ui;
	PFNPROGRAMUNIFORM1UIVPROC ProgramUniform1uiv;
	PFNPROGRAMUNIFORM2DPROC ProgramUniform2d;
	PFNPROGRAMUNIFORM2DVPROC ProgramUniform2dv;
	PFNPROGRAMUNIFORM2FPROC ProgramUniform2f;
	PFNPROGRAMUNIFORM2FVPROC ProgramUniform2fv;
	PFNPROGRAMUNIFORM2IPROC ProgramUniform2i;
	PFNPROGRAMUNIFORM2IVPROC ProgramUniform2iv;
	PFNPROGRAMUNIFORM2UIPROC ProgramUniform2ui;
	PFNPROGRAMUNIFORM2UIVPROC ProgramUniform2uiv;
	PFNPROGRAMUNIFORM3DPROC ProgramUniform3d;
	PFNPROGRAMUNIFORM3DVPROC ProgramUniform3dv;
	PFNPROGRAMUNIFORM3FPROC ProgramUniform3f;
	PFNPROGRAMUNIFORM3FVPROC ProgramUniform3fv;
	PFNPROGRAMUNIFORM3IPROC ProgramUniform3i;
	PFNPROGRAMUNIFORM3IVPROC ProgramUniform3iv;
	PFNPROGRAMUNIFORM3UIPROC ProgramUniform3ui;
	PFNPROGRAMUNIFORM3UIVPROC ProgramUniform3uiv;
	PFNPROGRAMUNIFORM4DPROC ProgramUniform4d;
	PFNPROGRAMUNIFORM4DVPROC ProgramUniform4dv;
	PFNPROGRAMUNIFORM4FPROC ProgramUniform4f;
	PFNPROGRAMUNIFORM4FVPROC ProgramUniform4fv;
	PFNPROGRAMUNIFORM4IPROC ProgramUniform4i;
	PFNPROGRAMUNIFORM4IVPROC ProgramUniform4iv;
	PFNPROGRAMUNIFORM4UIPROC ProgramUniform4ui;
	PFNPROGRAMUNIFORM4UIVPROC ProgramUniform4uiv;
	PFNPROGRAMUNIFORMMATRIX2DVPROC ProgramUniformMatrix2dv;
	PFNPROGRAMUNIFORMMATRIX2FVPROC ProgramUniformMatrix2fv;
	PFNPROGRAMUNIFORMMATRIX2X3DVPROC ProgramUniformMatrix2x3dv;
	PFNPROGRAMUNIFORMMATRIX2X3FVPROC ProgramUniformMatrix2x3fv;
	PFNPROGRAMUNIFORMMATRIX2X4DVPROC ProgramUniformMatrix2x4dv;
	PFNPROGRAMUNIFORMMATRIX2X4FVPROC ProgramUniformMatrix2x4fv;
	PFNPROGRAMUNIFORMMATRIX3DVPROC ProgramUniformMatrix3dv;
	PFNPROGRAMUNIFORMMATRIX3FVPROC ProgramUniformMatrix3fv;
	PFNPROGRAMUNIFORMMATRIX3X2DVPROC ProgramUniformMatrix3x2dv;
	PFNPROGRAMUNIFORMMATRIX3X2FVPROC ProgramUniformMatrix3x2fv;
	PFNPROGRAMUNIFORMMATRIX3X4DVPROC ProgramUniformMatrix3x4dv;
	PFNPROGRAMUNIFORMMATRIX3X4FVPROC ProgramUniformMatrix3x4fv;
	PFNPROGRAMUNIFORMMATRIX4DVPROC ProgramUniformMatrix4dv;
	PFNPROGRAMUNIFORMMATRIX4FVPROC ProgramUniformMatrix4fv;
	PFNPROGRAMUNIFORMMATRIX4X2DVPROC ProgramUniformMatrix4x2dv;
	PFNPROGRAMUNIFORMMATRIX4X2FVPROC ProgramUniformMatrix4x2fv;
	PFNPROGRAMUNIFORMMATRIX4X3DVPROC ProgramUniformMatrix4x3dv;
	PFNPROGRAMUNIFORMMATRIX4X3FVPROC ProgramUniformMatrix4x3fv;
	PFNRELEASESHADERCOMPILERPROC ReleaseShaderCompiler;
	PFNSCISSORARRAYVPROC ScissorArrayv;
	PFNSCISSORINDEXEDPROC ScissorIndexed;
	PFNSCISSORINDEXEDVPROC ScissorIndexedv;
	PFNSHADERBINARYPROC ShaderBinary;
	PFNUSEPROGRAMSTAGESPROC UseProgramStages;
	PFNVALIDATEPROGRAMPIPELINEPROC ValidateProgramPipeline;
	PFNVERTEXATTRIBL1DPROC VertexAttribL1d;
	PFNVERTEXATTRIBL1DVPROC VertexAttribL1dv;
	PFNVERTEXATTRIBL2DPROC VertexAttribL2d;
	PFNVERTEXATTRIBL2DVPROC VertexAttribL2dv;
	PFNVERTEXATTRIBL3DPROC VertexAttribL3d;
	PFNVERTEXATTRIBL3DVPROC VertexAttribL3dv;
	PFNVERTEXATTRIBL4DPROC VertexAttribL4d;
	PFNVERTEXATTRIBL4DVPROC VertexAttribL4dv;
	PFNVERTEXATTRIBLPOINTERPROC VertexAttribLPointer;
	PFNVIEWPORTARRAYVPROC ViewportArrayv;
	PFNVIEWPORTINDEXEDFPROC ViewportIndexedf;
	PFNVIEWPORTINDEXEDFVPROC ViewportIndexedfv;
	
	// Extension: 4.2
	PFNBINDIMAGETEXTUREPROC BindImageTexture;
	PFNDRAWARRAYSINSTANCEDBASEINSTANCEPROC DrawArraysInstancedBaseInstance;
	PFNDRAWELEMENTSINSTANCEDBASEINSTANCEPROC DrawElementsInstancedBaseInstance;
	PFNDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC DrawElementsInstancedBaseVertexBaseInstance;
	PFNDRAWTRANSFORMFEEDBACKINSTANCEDPROC DrawTransformFeedbackInstanced;
	PFNDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC DrawTransformFeedbackStreamInstanced;
	PFNGETACTIVEATOMICCOUNTERBUFFERIVPROC GetActiveAtomicCounterBufferiv;
	PFNGETINTERNALFORMATIVPROC GetInternalformativ;
	PFNMEMORYBARRIERPROC MemoryBarrier;
	PFNTEXSTORAGE1DPROC TexStorage1D;
	PFNTEXSTORAGE2DPROC TexStorage2D;
	PFNTEXSTORAGE3DPROC TexStorage3D;
	
	// Extension: 4.3
	PFNBINDVERTEXBUFFERPROC BindVertexBuffer;
	PFNCLEARBUFFERDATAPROC ClearBufferData;
	PFNCLEARBUFFERSUBDATAPROC ClearBufferSubData;
	PFNCOPYIMAGESUBDATAPROC CopyImageSubData;
	PFNDEBUGMESSAGECALLBACKPROC DebugMessageCallback;
	PFNDEBUGMESSAGECONTROLPROC DebugMessageControl;
	PFNDEBUGMESSAGEINSERTPROC DebugMessageInsert;
	PFNDISPATCHCOMPUTEPROC DispatchCompute;
	PFNDISPATCHCOMPUTEINDIRECTPROC DispatchComputeIndirect;
	PFNFRAMEBUFFERPARAMETERIPROC FramebufferParameteri;
	PFNGETDEBUGMESSAGELOGPROC GetDebugMessageLog;
	PFNGETFRAMEBUFFERPARAMETERIVPROC GetFramebufferParameteriv;
	PFNGETINTERNALFORMATI64VPROC GetInternalformati64v;
	PFNGETOBJECTLABELPROC GetObjectLabel;
	PFNGETOBJECTPTRLABELPROC GetObjectPtrLabel;
	PFNGETPROGRAMINTERFACEIVPROC GetProgramInterfaceiv;
	PFNGETPROGRAMRESOURCEINDEXPROC GetProgramResourceIndex;
	PFNGETPROGRAMRESOURCELOCATIONPROC GetProgramResourceLocation;
	PFNGETPROGRAMRESOURCELOCATIONINDEXPROC GetProgramResourceLocationIndex;
	PFNGETPROGRAMRESOURCENAMEPROC GetProgramResourceName;
	PFNGETPROGRAMRESOURCEIVPROC GetProgramResourceiv;
	PFNINVALIDATEBUFFERDATAPROC InvalidateBufferData;
	PFNINVALIDATEBUFFERSUBDATAPROC InvalidateBufferSubData;
	PFNINVALIDATEFRAMEBUFFERPROC InvalidateFramebuffer;
	PFNINVALIDATESUBFRAMEBUFFERPROC InvalidateSubFramebuffer;
	PFNINVALIDATETEXIMAGEPROC InvalidateTexImage;
	PFNINVALIDATETEXSUBIMAGEPROC InvalidateTexSubImage;
	PFNMULTIDRAWARRAYSINDIRECTPROC MultiDrawArraysIndirect;
	PFNMULTIDRAWELEMENTSINDIRECTPROC MultiDrawElementsIndirect;
	PFNOBJECTLABELPROC ObjectLabel;
	PFNOBJECTPTRLABELPROC ObjectPtrLabel;
	PFNPOPDEBUGGROUPPROC PopDebugGroup;
	PFNPUSHDEBUGGROUPPROC PushDebugGroup;
	PFNSHADERSTORAGEBLOCKBINDINGPROC ShaderStorageBlockBinding;
	PFNTEXBUFFERRANGEPROC TexBufferRange;
	PFNTEXSTORAGE2DMULTISAMPLEPROC TexStorage2DMultisample;
	PFNTEXSTORAGE3DMULTISAMPLEPROC TexStorage3DMultisample;
	PFNTEXTUREVIEWPROC TextureView;
	PFNVERTEXATTRIBBINDINGPROC VertexAttribBinding;
	PFNVERTEXATTRIBFORMATPROC VertexAttribFormat;
	PFNVERTEXATTRIBIFORMATPROC VertexAttribIFormat;
	PFNVERTEXATTRIBLFORMATPROC VertexAttribLFormat;
	PFNVERTEXBINDINGDIVISORPROC VertexBindingDivisor;
	
	// Extension: 4.4
	PFNBINDBUFFERSBASEPROC BindBuffersBase;
	PFNBINDBUFFERSRANGEPROC BindBuffersRange;
	PFNBINDIMAGETEXTURESPROC BindImageTextures;
	PFNBINDSAMPLERSPROC BindSamplers;
	PFNBINDTEXTURESPROC BindTextures;
	PFNBINDVERTEXBUFFERSPROC BindVertexBuffers;
	PFNBUFFERSTORAGEPROC BufferStorage;
	PFNCLEARTEXIMAGEPROC ClearTexImage;
	PFNCLEARTEXSUBIMAGEPROC ClearTexSubImage;
	
	// Extension: 4.5
	PFNBINDTEXTUREUNITPROC BindTextureUnit;
	PFNBLITNAMEDFRAMEBUFFERPROC BlitNamedFramebuffer;
	PFNCHECKNAMEDFRAMEBUFFERSTATUSPROC CheckNamedFramebufferStatus;
	PFNCLEARNAMEDBUFFERDATAPROC ClearNamedBufferData;
	PFNCLEARNAMEDBUFFERSUBDATAPROC ClearNamedBufferSubData;
	PFNCLEARNAMEDFRAMEBUFFERFIPROC ClearNamedFramebufferfi;
	PFNCLEARNAMEDFRAMEBUFFERFVPROC ClearNamedFramebufferfv;
	PFNCLEARNAMEDFRAMEBUFFERIVPROC ClearNamedFramebufferiv;
	PFNCLEARNAMEDFRAMEBUFFERUIVPROC ClearNamedFramebufferuiv;
	PFNCLIPCONTROLPROC ClipControl;
	PFNCOMPRESSEDTEXTURESUBIMAGE1DPROC CompressedTextureSubImage1D;
	PFNCOMPRESSEDTEXTURESUBIMAGE2DPROC CompressedTextureSubImage2D;
	PFNCOMPRESSEDTEXTURESUBIMAGE3DPROC CompressedTextureSubImage3D;
	PFNCOPYNAMEDBUFFERSUBDATAPROC CopyNamedBufferSubData;
	PFNCOPYTEXTURESUBIMAGE1DPROC CopyTextureSubImage1D;
	PFNCOPYTEXTURESUBIMAGE2DPROC CopyTextureSubImage2D;
	PFNCOPYTEXTURESUBIMAGE3DPROC CopyTextureSubImage3D;
	PFNCREATEBUFFERSPROC CreateBuffers;
	PFNCREATEFRAMEBUFFERSPROC CreateFramebuffers;
	PFNCREATEPROGRAMPIPELINESPROC CreateProgramPipelines;
	PFNCREATEQUERIESPROC CreateQueries;
	PFNCREATERENDERBUFFERSPROC CreateRenderbuffers;
	PFNCREATESAMPLERSPROC CreateSamplers;
	PFNCREATETEXTURESPROC CreateTextures;
	PFNCREATETRANSFORMFEEDBACKSPROC CreateTransformFeedbacks;
	PFNCREATEVERTEXARRAYSPROC CreateVertexArrays;
	PFNDISABLEVERTEXARRAYATTRIBPROC DisableVertexArrayAttrib;
	PFNENABLEVERTEXARRAYATTRIBPROC EnableVertexArrayAttrib;
	PFNFLUSHMAPPEDNAMEDBUFFERRANGEPROC FlushMappedNamedBufferRange;
	PFNGENERATETEXTUREMIPMAPPROC GenerateTextureMipmap;
	PFNGETCOMPRESSEDTEXTUREIMAGEPROC GetCompressedTextureImage;
	PFNGETCOMPRESSEDTEXTURESUBIMAGEPROC GetCompressedTextureSubImage;
	PFNGETGRAPHICSRESETSTATUSPROC GetGraphicsResetStatus;
	PFNGETNAMEDBUFFERPARAMETERI64VPROC GetNamedBufferParameteri64v;
	PFNGETNAMEDBUFFERPARAMETERIVPROC GetNamedBufferParameteriv;
	PFNGETNAMEDBUFFERPOINTERVPROC GetNamedBufferPointerv;
	PFNGETNAMEDBUFFERSUBDATAPROC GetNamedBufferSubData;
	PFNGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC GetNamedFramebufferAttachmentParameteriv;
	PFNGETNAMEDFRAMEBUFFERPARAMETERIVPROC GetNamedFramebufferParameteriv;
	PFNGETNAMEDRENDERBUFFERPARAMETERIVPROC GetNamedRenderbufferParameteriv;
	PFNGETQUERYBUFFEROBJECTI64VPROC GetQueryBufferObjecti64v;
	PFNGETQUERYBUFFEROBJECTIVPROC GetQueryBufferObjectiv;
	PFNGETQUERYBUFFEROBJECTUI64VPROC GetQueryBufferObjectui64v;
	PFNGETQUERYBUFFEROBJECTUIVPROC GetQueryBufferObjectuiv;
	PFNGETTEXTUREIMAGEPROC GetTextureImage;
	PFNGETTEXTURELEVELPARAMETERFVPROC GetTextureLevelParameterfv;
	PFNGETTEXTURELEVELPARAMETERIVPROC GetTextureLevelParameteriv;
	PFNGETTEXTUREPARAMETERIIVPROC GetTextureParameterIiv;
	PFNGETTEXTUREPARAMETERIUIVPROC GetTextureParameterIuiv;
	PFNGETTEXTUREPARAMETERFVPROC GetTextureParameterfv;
	PFNGETTEXTUREPARAMETERIVPROC GetTextureParameteriv;
	PFNGETTEXTURESUBIMAGEPROC GetTextureSubImage;
	PFNGETTRANSFORMFEEDBACKI64_VPROC GetTransformFeedbacki64_v;
	PFNGETTRANSFORMFEEDBACKI_VPROC GetTransformFeedbacki_v;
	PFNGETTRANSFORMFEEDBACKIVPROC GetTransformFeedbackiv;
	PFNGETVERTEXARRAYINDEXED64IVPROC GetVertexArrayIndexed64iv;
	PFNGETVERTEXARRAYINDEXEDIVPROC GetVertexArrayIndexediv;
	PFNGETVERTEXARRAYIVPROC GetVertexArrayiv;
	PFNGETNCOMPRESSEDTEXIMAGEPROC GetnCompressedTexImage;
	PFNGETNTEXIMAGEPROC GetnTexImage;
	PFNGETNUNIFORMDVPROC GetnUniformdv;
	PFNGETNUNIFORMFVPROC GetnUniformfv;
	PFNGETNUNIFORMIVPROC GetnUniformiv;
	PFNGETNUNIFORMUIVPROC GetnUniformuiv;
	PFNINVALIDATENAMEDFRAMEBUFFERDATAPROC InvalidateNamedFramebufferData;
	PFNINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC InvalidateNamedFramebufferSubData;
	PFNMAPNAMEDBUFFERPROC MapNamedBuffer;
	PFNMAPNAMEDBUFFERRANGEPROC MapNamedBufferRange;
	PFNMEMORYBARRIERBYREGIONPROC MemoryBarrierByRegion;
	PFNNAMEDBUFFERDATAPROC NamedBufferData;
	PFNNAMEDBUFFERSTORAGEPROC NamedBufferStorage;
	PFNNAMEDBUFFERSUBDATAPROC NamedBufferSubData;
	PFNNAMEDFRAMEBUFFERDRAWBUFFERPROC NamedFramebufferDrawBuffer;
	PFNNAMEDFRAMEBUFFERDRAWBUFFERSPROC NamedFramebufferDrawBuffers;
	PFNNAMEDFRAMEBUFFERPARAMETERIPROC NamedFramebufferParameteri;
	PFNNAMEDFRAMEBUFFERREADBUFFERPROC NamedFramebufferReadBuffer;
	PFNNAMEDFRAMEBUFFERRENDERBUFFERPROC NamedFramebufferRenderbuffer;
	PFNNAMEDFRAMEBUFFERTEXTUREPROC NamedFramebufferTexture;
	PFNNAMEDFRAMEBUFFERTEXTURELAYERPROC NamedFramebufferTextureLayer;
	PFNNAMEDRENDERBUFFERSTORAGEPROC NamedRenderbufferStorage;
	PFNNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC NamedRenderbufferStorageMultisample;
	PFNREADNPIXELSPROC ReadnPixels;
	PFNTEXTUREBARRIERPROC TextureBarrier;
	PFNTEXTUREBUFFERPROC TextureBuffer;
	PFNTEXTUREBUFFERRANGEPROC TextureBufferRange;
	PFNTEXTUREPARAMETERIIVPROC TextureParameterIiv;
	PFNTEXTUREPARAMETERIUIVPROC TextureParameterIuiv;
	PFNTEXTUREPARAMETERFPROC TextureParameterf;
	PFNTEXTUREPARAMETERFVPROC TextureParameterfv;
	PFNTEXTUREPARAMETERIPROC TextureParameteri;
	PFNTEXTUREPARAMETERIVPROC TextureParameteriv;
	PFNTEXTURESTORAGE1DPROC TextureStorage1D;
	PFNTEXTURESTORAGE2DPROC TextureStorage2D;
	PFNTEXTURESTORAGE2DMULTISAMPLEPROC TextureStorage2DMultisample;
	PFNTEXTURESTORAGE3DPROC TextureStorage3D;
	PFNTEXTURESTORAGE3DMULTISAMPLEPROC TextureStorage3DMultisample;
	PFNTEXTURESUBIMAGE1DPROC TextureSubImage1D;
	PFNTEXTURESUBIMAGE2DPROC TextureSubImage2D;
	PFNTEXTURESUBIMAGE3DPROC TextureSubImage3D;
	PFNTRANSFORMFEEDBACKBUFFERBASEPROC TransformFeedbackBufferBase;
	PFNTRANSFORMFEEDBACKBUFFERRANGEPROC TransformFeedbackBufferRange;
	PFNUNMAPNAMEDBUFFERPROC UnmapNamedBuffer;
	PFNVERTEXARRAYATTRIBBINDINGPROC VertexArrayAttribBinding;
	PFNVERTEXARRAYATTRIBFORMATPROC VertexArrayAttribFormat;
	PFNVERTEXARRAYATTRIBIFORMATPROC VertexArrayAttribIFormat;
	PFNVERTEXARRAYATTRIBLFORMATPROC VertexArrayAttribLFormat;
	PFNVERTEXARRAYBINDINGDIVISORPROC VertexArrayBindingDivisor;
	PFNVERTEXARRAYELEMENTBUFFERPROC VertexArrayElementBuffer;
	PFNVERTEXARRAYVERTEXBUFFERPROC VertexArrayVertexBuffer;
	PFNVERTEXARRAYVERTEXBUFFERSPROC VertexArrayVertexBuffers;
	
	
	// Extension: 1.0
	static void CODEGEN_FUNCPTR Switch_BlendFunc(GLenum sfactor, GLenum dfactor)
	{
		BlendFunc = (PFNBLENDFUNCPROC)IntGetProcAddress("glBlendFunc");
		BlendFunc(sfactor, dfactor);
	}

	static void CODEGEN_FUNCPTR Switch_Clear(GLbitfield mask)
	{
		Clear = (PFNCLEARPROC)IntGetProcAddress("glClear");
		Clear(mask);
	}

	static void CODEGEN_FUNCPTR Switch_ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		ClearColor = (PFNCLEARCOLORPROC)IntGetProcAddress("glClearColor");
		ClearColor(red, green, blue, alpha);
	}

	static void CODEGEN_FUNCPTR Switch_ClearDepth(GLdouble depth)
	{
		ClearDepth = (PFNCLEARDEPTHPROC)IntGetProcAddress("glClearDepth");
		ClearDepth(depth);
	}

	static void CODEGEN_FUNCPTR Switch_ClearStencil(GLint s)
	{
		ClearStencil = (PFNCLEARSTENCILPROC)IntGetProcAddress("glClearStencil");
		ClearStencil(s);
	}

	static void CODEGEN_FUNCPTR Switch_ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
	{
		ColorMask = (PFNCOLORMASKPROC)IntGetProcAddress("glColorMask");
		ColorMask(red, green, blue, alpha);
	}

	static void CODEGEN_FUNCPTR Switch_CullFace(GLenum mode)
	{
		CullFace = (PFNCULLFACEPROC)IntGetProcAddress("glCullFace");
		CullFace(mode);
	}

	static void CODEGEN_FUNCPTR Switch_DepthFunc(GLenum func)
	{
		DepthFunc = (PFNDEPTHFUNCPROC)IntGetProcAddress("glDepthFunc");
		DepthFunc(func);
	}

	static void CODEGEN_FUNCPTR Switch_DepthMask(GLboolean flag)
	{
		DepthMask = (PFNDEPTHMASKPROC)IntGetProcAddress("glDepthMask");
		DepthMask(flag);
	}

	static void CODEGEN_FUNCPTR Switch_DepthRange(GLdouble ren_near, GLdouble ren_far)
	{
		DepthRange = (PFNDEPTHRANGEPROC)IntGetProcAddress("glDepthRange");
		DepthRange(ren_near, ren_far);
	}

	static void CODEGEN_FUNCPTR Switch_Disable(GLenum cap)
	{
		Disable = (PFNDISABLEPROC)IntGetProcAddress("glDisable");
		Disable(cap);
	}

	static void CODEGEN_FUNCPTR Switch_DrawBuffer(GLenum buf)
	{
		DrawBuffer = (PFNDRAWBUFFERPROC)IntGetProcAddress("glDrawBuffer");
		DrawBuffer(buf);
	}

	static void CODEGEN_FUNCPTR Switch_Enable(GLenum cap)
	{
		Enable = (PFNENABLEPROC)IntGetProcAddress("glEnable");
		Enable(cap);
	}

	static void CODEGEN_FUNCPTR Switch_Finish(void)
	{
		Finish = (PFNFINISHPROC)IntGetProcAddress("glFinish");
		Finish();
	}

	static void CODEGEN_FUNCPTR Switch_Flush(void)
	{
		Flush = (PFNFLUSHPROC)IntGetProcAddress("glFlush");
		Flush();
	}

	static void CODEGEN_FUNCPTR Switch_FrontFace(GLenum mode)
	{
		FrontFace = (PFNFRONTFACEPROC)IntGetProcAddress("glFrontFace");
		FrontFace(mode);
	}

	static void CODEGEN_FUNCPTR Switch_GetBooleanv(GLenum pname, GLboolean * data)
	{
		GetBooleanv = (PFNGETBOOLEANVPROC)IntGetProcAddress("glGetBooleanv");
		GetBooleanv(pname, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetDoublev(GLenum pname, GLdouble * data)
	{
		GetDoublev = (PFNGETDOUBLEVPROC)IntGetProcAddress("glGetDoublev");
		GetDoublev(pname, data);
	}

	static GLenum CODEGEN_FUNCPTR Switch_GetError(void)
	{
		GetError = (PFNGETERRORPROC)IntGetProcAddress("glGetError");
		return GetError();
	}

	static void CODEGEN_FUNCPTR Switch_GetFloatv(GLenum pname, GLfloat * data)
	{
		GetFloatv = (PFNGETFLOATVPROC)IntGetProcAddress("glGetFloatv");
		GetFloatv(pname, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetIntegerv(GLenum pname, GLint * data)
	{
		GetIntegerv = (PFNGETINTEGERVPROC)IntGetProcAddress("glGetIntegerv");
		GetIntegerv(pname, data);
	}

	static const GLubyte * CODEGEN_FUNCPTR Switch_GetString(GLenum name)
	{
		GetString = (PFNGETSTRINGPROC)IntGetProcAddress("glGetString");
		return GetString(name);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
	{
		GetTexImage = (PFNGETTEXIMAGEPROC)IntGetProcAddress("glGetTexImage");
		GetTexImage(target, level, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
	{
		GetTexLevelParameterfv = (PFNGETTEXLEVELPARAMETERFVPROC)IntGetProcAddress("glGetTexLevelParameterfv");
		GetTexLevelParameterfv(target, level, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
	{
		GetTexLevelParameteriv = (PFNGETTEXLEVELPARAMETERIVPROC)IntGetProcAddress("glGetTexLevelParameteriv");
		GetTexLevelParameteriv(target, level, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
	{
		GetTexParameterfv = (PFNGETTEXPARAMETERFVPROC)IntGetProcAddress("glGetTexParameterfv");
		GetTexParameterfv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexParameteriv(GLenum target, GLenum pname, GLint * params)
	{
		GetTexParameteriv = (PFNGETTEXPARAMETERIVPROC)IntGetProcAddress("glGetTexParameteriv");
		GetTexParameteriv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_Hint(GLenum target, GLenum mode)
	{
		Hint = (PFNHINTPROC)IntGetProcAddress("glHint");
		Hint(target, mode);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsEnabled(GLenum cap)
	{
		IsEnabled = (PFNISENABLEDPROC)IntGetProcAddress("glIsEnabled");
		return IsEnabled(cap);
	}

	static void CODEGEN_FUNCPTR Switch_LineWidth(GLfloat width)
	{
		LineWidth = (PFNLINEWIDTHPROC)IntGetProcAddress("glLineWidth");
		LineWidth(width);
	}

	static void CODEGEN_FUNCPTR Switch_LogicOp(GLenum opcode)
	{
		LogicOp = (PFNLOGICOPPROC)IntGetProcAddress("glLogicOp");
		LogicOp(opcode);
	}

	static void CODEGEN_FUNCPTR Switch_PixelStoref(GLenum pname, GLfloat param)
	{
		PixelStoref = (PFNPIXELSTOREFPROC)IntGetProcAddress("glPixelStoref");
		PixelStoref(pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_PixelStorei(GLenum pname, GLint param)
	{
		PixelStorei = (PFNPIXELSTOREIPROC)IntGetProcAddress("glPixelStorei");
		PixelStorei(pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_PointSize(GLfloat size)
	{
		PointSize = (PFNPOINTSIZEPROC)IntGetProcAddress("glPointSize");
		PointSize(size);
	}

	static void CODEGEN_FUNCPTR Switch_PolygonMode(GLenum face, GLenum mode)
	{
		PolygonMode = (PFNPOLYGONMODEPROC)IntGetProcAddress("glPolygonMode");
		PolygonMode(face, mode);
	}

	static void CODEGEN_FUNCPTR Switch_ReadBuffer(GLenum src)
	{
		ReadBuffer = (PFNREADBUFFERPROC)IntGetProcAddress("glReadBuffer");
		ReadBuffer(src);
	}

	static void CODEGEN_FUNCPTR Switch_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
	{
		ReadPixels = (PFNREADPIXELSPROC)IntGetProcAddress("glReadPixels");
		ReadPixels(x, y, width, height, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		Scissor = (PFNSCISSORPROC)IntGetProcAddress("glScissor");
		Scissor(x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_StencilFunc(GLenum func, GLint ref, GLuint mask)
	{
		StencilFunc = (PFNSTENCILFUNCPROC)IntGetProcAddress("glStencilFunc");
		StencilFunc(func, ref, mask);
	}

	static void CODEGEN_FUNCPTR Switch_StencilMask(GLuint mask)
	{
		StencilMask = (PFNSTENCILMASKPROC)IntGetProcAddress("glStencilMask");
		StencilMask(mask);
	}

	static void CODEGEN_FUNCPTR Switch_StencilOp(GLenum fail, GLenum zfail, GLenum zpass)
	{
		StencilOp = (PFNSTENCILOPPROC)IntGetProcAddress("glStencilOp");
		StencilOp(fail, zfail, zpass);
	}

	static void CODEGEN_FUNCPTR Switch_TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
	{
		TexImage1D = (PFNTEXIMAGE1DPROC)IntGetProcAddress("glTexImage1D");
		TexImage1D(target, level, internalformat, width, border, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
	{
		TexImage2D = (PFNTEXIMAGE2DPROC)IntGetProcAddress("glTexImage2D");
		TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameterf(GLenum target, GLenum pname, GLfloat param)
	{
		TexParameterf = (PFNTEXPARAMETERFPROC)IntGetProcAddress("glTexParameterf");
		TexParameterf(target, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameterfv(GLenum target, GLenum pname, const GLfloat * params)
	{
		TexParameterfv = (PFNTEXPARAMETERFVPROC)IntGetProcAddress("glTexParameterfv");
		TexParameterfv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameteri(GLenum target, GLenum pname, GLint param)
	{
		TexParameteri = (PFNTEXPARAMETERIPROC)IntGetProcAddress("glTexParameteri");
		TexParameteri(target, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameteriv(GLenum target, GLenum pname, const GLint * params)
	{
		TexParameteriv = (PFNTEXPARAMETERIVPROC)IntGetProcAddress("glTexParameteriv");
		TexParameteriv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		Viewport = (PFNVIEWPORTPROC)IntGetProcAddress("glViewport");
		Viewport(x, y, width, height);
	}

	
	// Extension: 1.1
	static void CODEGEN_FUNCPTR Switch_BindTexture(GLenum target, GLuint texture)
	{
		BindTexture = (PFNBINDTEXTUREPROC)IntGetProcAddress("glBindTexture");
		BindTexture(target, texture);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
	{
		CopyTexImage1D = (PFNCOPYTEXIMAGE1DPROC)IntGetProcAddress("glCopyTexImage1D");
		CopyTexImage1D(target, level, internalformat, x, y, width, border);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
	{
		CopyTexImage2D = (PFNCOPYTEXIMAGE2DPROC)IntGetProcAddress("glCopyTexImage2D");
		CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		CopyTexSubImage1D = (PFNCOPYTEXSUBIMAGE1DPROC)IntGetProcAddress("glCopyTexSubImage1D");
		CopyTexSubImage1D(target, level, xoffset, x, y, width);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		CopyTexSubImage2D = (PFNCOPYTEXSUBIMAGE2DPROC)IntGetProcAddress("glCopyTexSubImage2D");
		CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteTextures(GLsizei n, const GLuint * textures)
	{
		DeleteTextures = (PFNDELETETEXTURESPROC)IntGetProcAddress("glDeleteTextures");
		DeleteTextures(n, textures);
	}

	static void CODEGEN_FUNCPTR Switch_DrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		DrawArrays = (PFNDRAWARRAYSPROC)IntGetProcAddress("glDrawArrays");
		DrawArrays(mode, first, count);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
	{
		DrawElements = (PFNDRAWELEMENTSPROC)IntGetProcAddress("glDrawElements");
		DrawElements(mode, count, type, indices);
	}

	static void CODEGEN_FUNCPTR Switch_GenTextures(GLsizei n, GLuint * textures)
	{
		GenTextures = (PFNGENTEXTURESPROC)IntGetProcAddress("glGenTextures");
		GenTextures(n, textures);
	}

	static void CODEGEN_FUNCPTR Switch_GetPointerv(GLenum pname, void ** params)
	{
		GetPointerv = (PFNGETPOINTERVPROC)IntGetProcAddress("glGetPointerv");
		GetPointerv(pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsTexture(GLuint texture)
	{
		IsTexture = (PFNISTEXTUREPROC)IntGetProcAddress("glIsTexture");
		return IsTexture(texture);
	}

	static void CODEGEN_FUNCPTR Switch_PolygonOffset(GLfloat factor, GLfloat units)
	{
		PolygonOffset = (PFNPOLYGONOFFSETPROC)IntGetProcAddress("glPolygonOffset");
		PolygonOffset(factor, units);
	}

	static void CODEGEN_FUNCPTR Switch_TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
	{
		TexSubImage1D = (PFNTEXSUBIMAGE1DPROC)IntGetProcAddress("glTexSubImage1D");
		TexSubImage1D(target, level, xoffset, width, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
	{
		TexSubImage2D = (PFNTEXSUBIMAGE2DPROC)IntGetProcAddress("glTexSubImage2D");
		TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	}

	
	// Extension: 1.2
	static void CODEGEN_FUNCPTR Switch_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		CopyTexSubImage3D = (PFNCOPYTEXSUBIMAGE3DPROC)IntGetProcAddress("glCopyTexSubImage3D");
		CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
	{
		DrawRangeElements = (PFNDRAWRANGEELEMENTSPROC)IntGetProcAddress("glDrawRangeElements");
		DrawRangeElements(mode, start, end, count, type, indices);
	}

	static void CODEGEN_FUNCPTR Switch_TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
	{
		TexImage3D = (PFNTEXIMAGE3DPROC)IntGetProcAddress("glTexImage3D");
		TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
	{
		TexSubImage3D = (PFNTEXSUBIMAGE3DPROC)IntGetProcAddress("glTexSubImage3D");
		TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	
	// Extension: 1.3
	static void CODEGEN_FUNCPTR Switch_ActiveTexture(GLenum texture)
	{
		ActiveTexture = (PFNACTIVETEXTUREPROC)IntGetProcAddress("glActiveTexture");
		ActiveTexture(texture);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
	{
		CompressedTexImage1D = (PFNCOMPRESSEDTEXIMAGE1DPROC)IntGetProcAddress("glCompressedTexImage1D");
		CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
	{
		CompressedTexImage2D = (PFNCOMPRESSEDTEXIMAGE2DPROC)IntGetProcAddress("glCompressedTexImage2D");
		CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
	{
		CompressedTexImage3D = (PFNCOMPRESSEDTEXIMAGE3DPROC)IntGetProcAddress("glCompressedTexImage3D");
		CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTexSubImage1D = (PFNCOMPRESSEDTEXSUBIMAGE1DPROC)IntGetProcAddress("glCompressedTexSubImage1D");
		CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTexSubImage2D = (PFNCOMPRESSEDTEXSUBIMAGE2DPROC)IntGetProcAddress("glCompressedTexSubImage2D");
		CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTexSubImage3D = (PFNCOMPRESSEDTEXSUBIMAGE3DPROC)IntGetProcAddress("glCompressedTexSubImage3D");
		CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetCompressedTexImage(GLenum target, GLint level, void * img)
	{
		GetCompressedTexImage = (PFNGETCOMPRESSEDTEXIMAGEPROC)IntGetProcAddress("glGetCompressedTexImage");
		GetCompressedTexImage(target, level, img);
	}

	static void CODEGEN_FUNCPTR Switch_SampleCoverage(GLfloat value, GLboolean invert)
	{
		SampleCoverage = (PFNSAMPLECOVERAGEPROC)IntGetProcAddress("glSampleCoverage");
		SampleCoverage(value, invert);
	}

	
	// Extension: 1.4
	static void CODEGEN_FUNCPTR Switch_BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		BlendColor = (PFNBLENDCOLORPROC)IntGetProcAddress("glBlendColor");
		BlendColor(red, green, blue, alpha);
	}

	static void CODEGEN_FUNCPTR Switch_BlendEquation(GLenum mode)
	{
		BlendEquation = (PFNBLENDEQUATIONPROC)IntGetProcAddress("glBlendEquation");
		BlendEquation(mode);
	}

	static void CODEGEN_FUNCPTR Switch_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
	{
		BlendFuncSeparate = (PFNBLENDFUNCSEPARATEPROC)IntGetProcAddress("glBlendFuncSeparate");
		BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}

	static void CODEGEN_FUNCPTR Switch_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
	{
		MultiDrawArrays = (PFNMULTIDRAWARRAYSPROC)IntGetProcAddress("glMultiDrawArrays");
		MultiDrawArrays(mode, first, count, drawcount);
	}

	static void CODEGEN_FUNCPTR Switch_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount)
	{
		MultiDrawElements = (PFNMULTIDRAWELEMENTSPROC)IntGetProcAddress("glMultiDrawElements");
		MultiDrawElements(mode, count, type, indices, drawcount);
	}

	static void CODEGEN_FUNCPTR Switch_PointParameterf(GLenum pname, GLfloat param)
	{
		PointParameterf = (PFNPOINTPARAMETERFPROC)IntGetProcAddress("glPointParameterf");
		PointParameterf(pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_PointParameterfv(GLenum pname, const GLfloat * params)
	{
		PointParameterfv = (PFNPOINTPARAMETERFVPROC)IntGetProcAddress("glPointParameterfv");
		PointParameterfv(pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_PointParameteri(GLenum pname, GLint param)
	{
		PointParameteri = (PFNPOINTPARAMETERIPROC)IntGetProcAddress("glPointParameteri");
		PointParameteri(pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_PointParameteriv(GLenum pname, const GLint * params)
	{
		PointParameteriv = (PFNPOINTPARAMETERIVPROC)IntGetProcAddress("glPointParameteriv");
		PointParameteriv(pname, params);
	}

	
	// Extension: 1.5
	static void CODEGEN_FUNCPTR Switch_BeginQuery(GLenum target, GLuint id)
	{
		BeginQuery = (PFNBEGINQUERYPROC)IntGetProcAddress("glBeginQuery");
		BeginQuery(target, id);
	}

	static void CODEGEN_FUNCPTR Switch_BindBuffer(GLenum target, GLuint buffer)
	{
		BindBuffer = (PFNBINDBUFFERPROC)IntGetProcAddress("glBindBuffer");
		BindBuffer(target, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
	{
		BufferData = (PFNBUFFERDATAPROC)IntGetProcAddress("glBufferData");
		BufferData(target, size, data, usage);
	}

	static void CODEGEN_FUNCPTR Switch_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
	{
		BufferSubData = (PFNBUFFERSUBDATAPROC)IntGetProcAddress("glBufferSubData");
		BufferSubData(target, offset, size, data);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteBuffers(GLsizei n, const GLuint * buffers)
	{
		DeleteBuffers = (PFNDELETEBUFFERSPROC)IntGetProcAddress("glDeleteBuffers");
		DeleteBuffers(n, buffers);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteQueries(GLsizei n, const GLuint * ids)
	{
		DeleteQueries = (PFNDELETEQUERIESPROC)IntGetProcAddress("glDeleteQueries");
		DeleteQueries(n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_EndQuery(GLenum target)
	{
		EndQuery = (PFNENDQUERYPROC)IntGetProcAddress("glEndQuery");
		EndQuery(target);
	}

	static void CODEGEN_FUNCPTR Switch_GenBuffers(GLsizei n, GLuint * buffers)
	{
		GenBuffers = (PFNGENBUFFERSPROC)IntGetProcAddress("glGenBuffers");
		GenBuffers(n, buffers);
	}

	static void CODEGEN_FUNCPTR Switch_GenQueries(GLsizei n, GLuint * ids)
	{
		GenQueries = (PFNGENQUERIESPROC)IntGetProcAddress("glGenQueries");
		GenQueries(n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
	{
		GetBufferParameteriv = (PFNGETBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetBufferParameteriv");
		GetBufferParameteriv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetBufferPointerv(GLenum target, GLenum pname, void ** params)
	{
		GetBufferPointerv = (PFNGETBUFFERPOINTERVPROC)IntGetProcAddress("glGetBufferPointerv");
		GetBufferPointerv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
	{
		GetBufferSubData = (PFNGETBUFFERSUBDATAPROC)IntGetProcAddress("glGetBufferSubData");
		GetBufferSubData(target, offset, size, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
	{
		GetQueryObjectiv = (PFNGETQUERYOBJECTIVPROC)IntGetProcAddress("glGetQueryObjectiv");
		GetQueryObjectiv(id, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
	{
		GetQueryObjectuiv = (PFNGETQUERYOBJECTUIVPROC)IntGetProcAddress("glGetQueryObjectuiv");
		GetQueryObjectuiv(id, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryiv(GLenum target, GLenum pname, GLint * params)
	{
		GetQueryiv = (PFNGETQUERYIVPROC)IntGetProcAddress("glGetQueryiv");
		GetQueryiv(target, pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsBuffer(GLuint buffer)
	{
		IsBuffer = (PFNISBUFFERPROC)IntGetProcAddress("glIsBuffer");
		return IsBuffer(buffer);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsQuery(GLuint id)
	{
		IsQuery = (PFNISQUERYPROC)IntGetProcAddress("glIsQuery");
		return IsQuery(id);
	}

	static void * CODEGEN_FUNCPTR Switch_MapBuffer(GLenum target, GLenum access)
	{
		MapBuffer = (PFNMAPBUFFERPROC)IntGetProcAddress("glMapBuffer");
		return MapBuffer(target, access);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_UnmapBuffer(GLenum target)
	{
		UnmapBuffer = (PFNUNMAPBUFFERPROC)IntGetProcAddress("glUnmapBuffer");
		return UnmapBuffer(target);
	}

	
	// Extension: 2.0
	static void CODEGEN_FUNCPTR Switch_AttachShader(GLuint program, GLuint shader)
	{
		AttachShader = (PFNATTACHSHADERPROC)IntGetProcAddress("glAttachShader");
		AttachShader(program, shader);
	}

	static void CODEGEN_FUNCPTR Switch_BindAttribLocation(GLuint program, GLuint index, const GLchar * name)
	{
		BindAttribLocation = (PFNBINDATTRIBLOCATIONPROC)IntGetProcAddress("glBindAttribLocation");
		BindAttribLocation(program, index, name);
	}

	static void CODEGEN_FUNCPTR Switch_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
	{
		BlendEquationSeparate = (PFNBLENDEQUATIONSEPARATEPROC)IntGetProcAddress("glBlendEquationSeparate");
		BlendEquationSeparate(modeRGB, modeAlpha);
	}

	static void CODEGEN_FUNCPTR Switch_CompileShader(GLuint shader)
	{
		CompileShader = (PFNCOMPILESHADERPROC)IntGetProcAddress("glCompileShader");
		CompileShader(shader);
	}

	static GLuint CODEGEN_FUNCPTR Switch_CreateProgram(void)
	{
		CreateProgram = (PFNCREATEPROGRAMPROC)IntGetProcAddress("glCreateProgram");
		return CreateProgram();
	}

	static GLuint CODEGEN_FUNCPTR Switch_CreateShader(GLenum type)
	{
		CreateShader = (PFNCREATESHADERPROC)IntGetProcAddress("glCreateShader");
		return CreateShader(type);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteProgram(GLuint program)
	{
		DeleteProgram = (PFNDELETEPROGRAMPROC)IntGetProcAddress("glDeleteProgram");
		DeleteProgram(program);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteShader(GLuint shader)
	{
		DeleteShader = (PFNDELETESHADERPROC)IntGetProcAddress("glDeleteShader");
		DeleteShader(shader);
	}

	static void CODEGEN_FUNCPTR Switch_DetachShader(GLuint program, GLuint shader)
	{
		DetachShader = (PFNDETACHSHADERPROC)IntGetProcAddress("glDetachShader");
		DetachShader(program, shader);
	}

	static void CODEGEN_FUNCPTR Switch_DisableVertexAttribArray(GLuint index)
	{
		DisableVertexAttribArray = (PFNDISABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glDisableVertexAttribArray");
		DisableVertexAttribArray(index);
	}

	static void CODEGEN_FUNCPTR Switch_DrawBuffers(GLsizei n, const GLenum * bufs)
	{
		DrawBuffers = (PFNDRAWBUFFERSPROC)IntGetProcAddress("glDrawBuffers");
		DrawBuffers(n, bufs);
	}

	static void CODEGEN_FUNCPTR Switch_EnableVertexAttribArray(GLuint index)
	{
		EnableVertexAttribArray = (PFNENABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glEnableVertexAttribArray");
		EnableVertexAttribArray(index);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
	{
		GetActiveAttrib = (PFNGETACTIVEATTRIBPROC)IntGetProcAddress("glGetActiveAttrib");
		GetActiveAttrib(program, index, bufSize, length, size, type, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
	{
		GetActiveUniform = (PFNGETACTIVEUNIFORMPROC)IntGetProcAddress("glGetActiveUniform");
		GetActiveUniform(program, index, bufSize, length, size, type, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
	{
		GetAttachedShaders = (PFNGETATTACHEDSHADERSPROC)IntGetProcAddress("glGetAttachedShaders");
		GetAttachedShaders(program, maxCount, count, shaders);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetAttribLocation(GLuint program, const GLchar * name)
	{
		GetAttribLocation = (PFNGETATTRIBLOCATIONPROC)IntGetProcAddress("glGetAttribLocation");
		return GetAttribLocation(program, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
	{
		GetProgramInfoLog = (PFNGETPROGRAMINFOLOGPROC)IntGetProcAddress("glGetProgramInfoLog");
		GetProgramInfoLog(program, bufSize, length, infoLog);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramiv(GLuint program, GLenum pname, GLint * params)
	{
		GetProgramiv = (PFNGETPROGRAMIVPROC)IntGetProcAddress("glGetProgramiv");
		GetProgramiv(program, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
	{
		GetShaderInfoLog = (PFNGETSHADERINFOLOGPROC)IntGetProcAddress("glGetShaderInfoLog");
		GetShaderInfoLog(shader, bufSize, length, infoLog);
	}

	static void CODEGEN_FUNCPTR Switch_GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
	{
		GetShaderSource = (PFNGETSHADERSOURCEPROC)IntGetProcAddress("glGetShaderSource");
		GetShaderSource(shader, bufSize, length, source);
	}

	static void CODEGEN_FUNCPTR Switch_GetShaderiv(GLuint shader, GLenum pname, GLint * params)
	{
		GetShaderiv = (PFNGETSHADERIVPROC)IntGetProcAddress("glGetShaderiv");
		GetShaderiv(shader, pname, params);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetUniformLocation(GLuint program, const GLchar * name)
	{
		GetUniformLocation = (PFNGETUNIFORMLOCATIONPROC)IntGetProcAddress("glGetUniformLocation");
		return GetUniformLocation(program, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformfv(GLuint program, GLint location, GLfloat * params)
	{
		GetUniformfv = (PFNGETUNIFORMFVPROC)IntGetProcAddress("glGetUniformfv");
		GetUniformfv(program, location, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformiv(GLuint program, GLint location, GLint * params)
	{
		GetUniformiv = (PFNGETUNIFORMIVPROC)IntGetProcAddress("glGetUniformiv");
		GetUniformiv(program, location, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer)
	{
		GetVertexAttribPointerv = (PFNGETVERTEXATTRIBPOINTERVPROC)IntGetProcAddress("glGetVertexAttribPointerv");
		GetVertexAttribPointerv(index, pname, pointer);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
	{
		GetVertexAttribdv = (PFNGETVERTEXATTRIBDVPROC)IntGetProcAddress("glGetVertexAttribdv");
		GetVertexAttribdv(index, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
	{
		GetVertexAttribfv = (PFNGETVERTEXATTRIBFVPROC)IntGetProcAddress("glGetVertexAttribfv");
		GetVertexAttribfv(index, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
	{
		GetVertexAttribiv = (PFNGETVERTEXATTRIBIVPROC)IntGetProcAddress("glGetVertexAttribiv");
		GetVertexAttribiv(index, pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsProgram(GLuint program)
	{
		IsProgram = (PFNISPROGRAMPROC)IntGetProcAddress("glIsProgram");
		return IsProgram(program);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsShader(GLuint shader)
	{
		IsShader = (PFNISSHADERPROC)IntGetProcAddress("glIsShader");
		return IsShader(shader);
	}

	static void CODEGEN_FUNCPTR Switch_LinkProgram(GLuint program)
	{
		LinkProgram = (PFNLINKPROGRAMPROC)IntGetProcAddress("glLinkProgram");
		LinkProgram(program);
	}

	static void CODEGEN_FUNCPTR Switch_ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length)
	{
		ShaderSource = (PFNSHADERSOURCEPROC)IntGetProcAddress("glShaderSource");
		ShaderSource(shader, count, string, length);
	}

	static void CODEGEN_FUNCPTR Switch_StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
	{
		StencilFuncSeparate = (PFNSTENCILFUNCSEPARATEPROC)IntGetProcAddress("glStencilFuncSeparate");
		StencilFuncSeparate(face, func, ref, mask);
	}

	static void CODEGEN_FUNCPTR Switch_StencilMaskSeparate(GLenum face, GLuint mask)
	{
		StencilMaskSeparate = (PFNSTENCILMASKSEPARATEPROC)IntGetProcAddress("glStencilMaskSeparate");
		StencilMaskSeparate(face, mask);
	}

	static void CODEGEN_FUNCPTR Switch_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
	{
		StencilOpSeparate = (PFNSTENCILOPSEPARATEPROC)IntGetProcAddress("glStencilOpSeparate");
		StencilOpSeparate(face, sfail, dpfail, dppass);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1f(GLint location, GLfloat v0)
	{
		Uniform1f = (PFNUNIFORM1FPROC)IntGetProcAddress("glUniform1f");
		Uniform1f(location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1fv(GLint location, GLsizei count, const GLfloat * value)
	{
		Uniform1fv = (PFNUNIFORM1FVPROC)IntGetProcAddress("glUniform1fv");
		Uniform1fv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1i(GLint location, GLint v0)
	{
		Uniform1i = (PFNUNIFORM1IPROC)IntGetProcAddress("glUniform1i");
		Uniform1i(location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1iv(GLint location, GLsizei count, const GLint * value)
	{
		Uniform1iv = (PFNUNIFORM1IVPROC)IntGetProcAddress("glUniform1iv");
		Uniform1iv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		Uniform2f = (PFNUNIFORM2FPROC)IntGetProcAddress("glUniform2f");
		Uniform2f(location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2fv(GLint location, GLsizei count, const GLfloat * value)
	{
		Uniform2fv = (PFNUNIFORM2FVPROC)IntGetProcAddress("glUniform2fv");
		Uniform2fv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2i(GLint location, GLint v0, GLint v1)
	{
		Uniform2i = (PFNUNIFORM2IPROC)IntGetProcAddress("glUniform2i");
		Uniform2i(location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2iv(GLint location, GLsizei count, const GLint * value)
	{
		Uniform2iv = (PFNUNIFORM2IVPROC)IntGetProcAddress("glUniform2iv");
		Uniform2iv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		Uniform3f = (PFNUNIFORM3FPROC)IntGetProcAddress("glUniform3f");
		Uniform3f(location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3fv(GLint location, GLsizei count, const GLfloat * value)
	{
		Uniform3fv = (PFNUNIFORM3FVPROC)IntGetProcAddress("glUniform3fv");
		Uniform3fv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2)
	{
		Uniform3i = (PFNUNIFORM3IPROC)IntGetProcAddress("glUniform3i");
		Uniform3i(location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3iv(GLint location, GLsizei count, const GLint * value)
	{
		Uniform3iv = (PFNUNIFORM3IVPROC)IntGetProcAddress("glUniform3iv");
		Uniform3iv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		Uniform4f = (PFNUNIFORM4FPROC)IntGetProcAddress("glUniform4f");
		Uniform4f(location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4fv(GLint location, GLsizei count, const GLfloat * value)
	{
		Uniform4fv = (PFNUNIFORM4FVPROC)IntGetProcAddress("glUniform4fv");
		Uniform4fv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		Uniform4i = (PFNUNIFORM4IPROC)IntGetProcAddress("glUniform4i");
		Uniform4i(location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4iv(GLint location, GLsizei count, const GLint * value)
	{
		Uniform4iv = (PFNUNIFORM4IVPROC)IntGetProcAddress("glUniform4iv");
		Uniform4iv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix2fv = (PFNUNIFORMMATRIX2FVPROC)IntGetProcAddress("glUniformMatrix2fv");
		UniformMatrix2fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix3fv = (PFNUNIFORMMATRIX3FVPROC)IntGetProcAddress("glUniformMatrix3fv");
		UniformMatrix3fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix4fv = (PFNUNIFORMMATRIX4FVPROC)IntGetProcAddress("glUniformMatrix4fv");
		UniformMatrix4fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UseProgram(GLuint program)
	{
		UseProgram = (PFNUSEPROGRAMPROC)IntGetProcAddress("glUseProgram");
		UseProgram(program);
	}

	static void CODEGEN_FUNCPTR Switch_ValidateProgram(GLuint program)
	{
		ValidateProgram = (PFNVALIDATEPROGRAMPROC)IntGetProcAddress("glValidateProgram");
		ValidateProgram(program);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1d(GLuint index, GLdouble x)
	{
		VertexAttrib1d = (PFNVERTEXATTRIB1DPROC)IntGetProcAddress("glVertexAttrib1d");
		VertexAttrib1d(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1dv(GLuint index, const GLdouble * v)
	{
		VertexAttrib1dv = (PFNVERTEXATTRIB1DVPROC)IntGetProcAddress("glVertexAttrib1dv");
		VertexAttrib1dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1f(GLuint index, GLfloat x)
	{
		VertexAttrib1f = (PFNVERTEXATTRIB1FPROC)IntGetProcAddress("glVertexAttrib1f");
		VertexAttrib1f(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1fv(GLuint index, const GLfloat * v)
	{
		VertexAttrib1fv = (PFNVERTEXATTRIB1FVPROC)IntGetProcAddress("glVertexAttrib1fv");
		VertexAttrib1fv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1s(GLuint index, GLshort x)
	{
		VertexAttrib1s = (PFNVERTEXATTRIB1SPROC)IntGetProcAddress("glVertexAttrib1s");
		VertexAttrib1s(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib1sv(GLuint index, const GLshort * v)
	{
		VertexAttrib1sv = (PFNVERTEXATTRIB1SVPROC)IntGetProcAddress("glVertexAttrib1sv");
		VertexAttrib1sv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
	{
		VertexAttrib2d = (PFNVERTEXATTRIB2DPROC)IntGetProcAddress("glVertexAttrib2d");
		VertexAttrib2d(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2dv(GLuint index, const GLdouble * v)
	{
		VertexAttrib2dv = (PFNVERTEXATTRIB2DVPROC)IntGetProcAddress("glVertexAttrib2dv");
		VertexAttrib2dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
	{
		VertexAttrib2f = (PFNVERTEXATTRIB2FPROC)IntGetProcAddress("glVertexAttrib2f");
		VertexAttrib2f(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2fv(GLuint index, const GLfloat * v)
	{
		VertexAttrib2fv = (PFNVERTEXATTRIB2FVPROC)IntGetProcAddress("glVertexAttrib2fv");
		VertexAttrib2fv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2s(GLuint index, GLshort x, GLshort y)
	{
		VertexAttrib2s = (PFNVERTEXATTRIB2SPROC)IntGetProcAddress("glVertexAttrib2s");
		VertexAttrib2s(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib2sv(GLuint index, const GLshort * v)
	{
		VertexAttrib2sv = (PFNVERTEXATTRIB2SVPROC)IntGetProcAddress("glVertexAttrib2sv");
		VertexAttrib2sv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		VertexAttrib3d = (PFNVERTEXATTRIB3DPROC)IntGetProcAddress("glVertexAttrib3d");
		VertexAttrib3d(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3dv(GLuint index, const GLdouble * v)
	{
		VertexAttrib3dv = (PFNVERTEXATTRIB3DVPROC)IntGetProcAddress("glVertexAttrib3dv");
		VertexAttrib3dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
	{
		VertexAttrib3f = (PFNVERTEXATTRIB3FPROC)IntGetProcAddress("glVertexAttrib3f");
		VertexAttrib3f(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3fv(GLuint index, const GLfloat * v)
	{
		VertexAttrib3fv = (PFNVERTEXATTRIB3FVPROC)IntGetProcAddress("glVertexAttrib3fv");
		VertexAttrib3fv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
	{
		VertexAttrib3s = (PFNVERTEXATTRIB3SPROC)IntGetProcAddress("glVertexAttrib3s");
		VertexAttrib3s(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib3sv(GLuint index, const GLshort * v)
	{
		VertexAttrib3sv = (PFNVERTEXATTRIB3SVPROC)IntGetProcAddress("glVertexAttrib3sv");
		VertexAttrib3sv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nbv(GLuint index, const GLbyte * v)
	{
		VertexAttrib4Nbv = (PFNVERTEXATTRIB4NBVPROC)IntGetProcAddress("glVertexAttrib4Nbv");
		VertexAttrib4Nbv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Niv(GLuint index, const GLint * v)
	{
		VertexAttrib4Niv = (PFNVERTEXATTRIB4NIVPROC)IntGetProcAddress("glVertexAttrib4Niv");
		VertexAttrib4Niv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nsv(GLuint index, const GLshort * v)
	{
		VertexAttrib4Nsv = (PFNVERTEXATTRIB4NSVPROC)IntGetProcAddress("glVertexAttrib4Nsv");
		VertexAttrib4Nsv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
	{
		VertexAttrib4Nub = (PFNVERTEXATTRIB4NUBPROC)IntGetProcAddress("glVertexAttrib4Nub");
		VertexAttrib4Nub(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nubv(GLuint index, const GLubyte * v)
	{
		VertexAttrib4Nubv = (PFNVERTEXATTRIB4NUBVPROC)IntGetProcAddress("glVertexAttrib4Nubv");
		VertexAttrib4Nubv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nuiv(GLuint index, const GLuint * v)
	{
		VertexAttrib4Nuiv = (PFNVERTEXATTRIB4NUIVPROC)IntGetProcAddress("glVertexAttrib4Nuiv");
		VertexAttrib4Nuiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nusv(GLuint index, const GLushort * v)
	{
		VertexAttrib4Nusv = (PFNVERTEXATTRIB4NUSVPROC)IntGetProcAddress("glVertexAttrib4Nusv");
		VertexAttrib4Nusv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4bv(GLuint index, const GLbyte * v)
	{
		VertexAttrib4bv = (PFNVERTEXATTRIB4BVPROC)IntGetProcAddress("glVertexAttrib4bv");
		VertexAttrib4bv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		VertexAttrib4d = (PFNVERTEXATTRIB4DPROC)IntGetProcAddress("glVertexAttrib4d");
		VertexAttrib4d(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4dv(GLuint index, const GLdouble * v)
	{
		VertexAttrib4dv = (PFNVERTEXATTRIB4DVPROC)IntGetProcAddress("glVertexAttrib4dv");
		VertexAttrib4dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		VertexAttrib4f = (PFNVERTEXATTRIB4FPROC)IntGetProcAddress("glVertexAttrib4f");
		VertexAttrib4f(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4fv(GLuint index, const GLfloat * v)
	{
		VertexAttrib4fv = (PFNVERTEXATTRIB4FVPROC)IntGetProcAddress("glVertexAttrib4fv");
		VertexAttrib4fv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4iv(GLuint index, const GLint * v)
	{
		VertexAttrib4iv = (PFNVERTEXATTRIB4IVPROC)IntGetProcAddress("glVertexAttrib4iv");
		VertexAttrib4iv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
	{
		VertexAttrib4s = (PFNVERTEXATTRIB4SPROC)IntGetProcAddress("glVertexAttrib4s");
		VertexAttrib4s(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4sv(GLuint index, const GLshort * v)
	{
		VertexAttrib4sv = (PFNVERTEXATTRIB4SVPROC)IntGetProcAddress("glVertexAttrib4sv");
		VertexAttrib4sv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4ubv(GLuint index, const GLubyte * v)
	{
		VertexAttrib4ubv = (PFNVERTEXATTRIB4UBVPROC)IntGetProcAddress("glVertexAttrib4ubv");
		VertexAttrib4ubv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4uiv(GLuint index, const GLuint * v)
	{
		VertexAttrib4uiv = (PFNVERTEXATTRIB4UIVPROC)IntGetProcAddress("glVertexAttrib4uiv");
		VertexAttrib4uiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttrib4usv(GLuint index, const GLushort * v)
	{
		VertexAttrib4usv = (PFNVERTEXATTRIB4USVPROC)IntGetProcAddress("glVertexAttrib4usv");
		VertexAttrib4usv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
	{
		VertexAttribPointer = (PFNVERTEXATTRIBPOINTERPROC)IntGetProcAddress("glVertexAttribPointer");
		VertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	
	// Extension: 2.1
	static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix2x3fv = (PFNUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glUniformMatrix2x3fv");
		UniformMatrix2x3fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix2x4fv = (PFNUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glUniformMatrix2x4fv");
		UniformMatrix2x4fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix3x2fv = (PFNUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glUniformMatrix3x2fv");
		UniformMatrix3x2fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix3x4fv = (PFNUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glUniformMatrix3x4fv");
		UniformMatrix3x4fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix4x2fv = (PFNUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glUniformMatrix4x2fv");
		UniformMatrix4x2fv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		UniformMatrix4x3fv = (PFNUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glUniformMatrix4x3fv");
		UniformMatrix4x3fv(location, count, transpose, value);
	}

	
	// Extension: 3.0
	static void CODEGEN_FUNCPTR Switch_BeginConditionalRender(GLuint id, GLenum mode)
	{
		BeginConditionalRender = (PFNBEGINCONDITIONALRENDERPROC)IntGetProcAddress("glBeginConditionalRender");
		BeginConditionalRender(id, mode);
	}

	static void CODEGEN_FUNCPTR Switch_BeginTransformFeedback(GLenum primitiveMode)
	{
		BeginTransformFeedback = (PFNBEGINTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBeginTransformFeedback");
		BeginTransformFeedback(primitiveMode);
	}

	static void CODEGEN_FUNCPTR Switch_BindBufferBase(GLenum target, GLuint index, GLuint buffer)
	{
		BindBufferBase = (PFNBINDBUFFERBASEPROC)IntGetProcAddress("glBindBufferBase");
		BindBufferBase(target, index, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		BindBufferRange = (PFNBINDBUFFERRANGEPROC)IntGetProcAddress("glBindBufferRange");
		BindBufferRange(target, index, buffer, offset, size);
	}

	static void CODEGEN_FUNCPTR Switch_BindFragDataLocation(GLuint program, GLuint color, const GLchar * name)
	{
		BindFragDataLocation = (PFNBINDFRAGDATALOCATIONPROC)IntGetProcAddress("glBindFragDataLocation");
		BindFragDataLocation(program, color, name);
	}

	static void CODEGEN_FUNCPTR Switch_BindFramebuffer(GLenum target, GLuint framebuffer)
	{
		BindFramebuffer = (PFNBINDFRAMEBUFFERPROC)IntGetProcAddress("glBindFramebuffer");
		BindFramebuffer(target, framebuffer);
	}

	static void CODEGEN_FUNCPTR Switch_BindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		BindRenderbuffer = (PFNBINDRENDERBUFFERPROC)IntGetProcAddress("glBindRenderbuffer");
		BindRenderbuffer(target, renderbuffer);
	}

	static void CODEGEN_FUNCPTR Switch_BindVertexArray(GLuint ren_array)
	{
		BindVertexArray = (PFNBINDVERTEXARRAYPROC)IntGetProcAddress("glBindVertexArray");
		BindVertexArray(ren_array);
	}

	static void CODEGEN_FUNCPTR Switch_BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		BlitFramebuffer = (PFNBLITFRAMEBUFFERPROC)IntGetProcAddress("glBlitFramebuffer");
		BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	static GLenum CODEGEN_FUNCPTR Switch_CheckFramebufferStatus(GLenum target)
	{
		CheckFramebufferStatus = (PFNCHECKFRAMEBUFFERSTATUSPROC)IntGetProcAddress("glCheckFramebufferStatus");
		return CheckFramebufferStatus(target);
	}

	static void CODEGEN_FUNCPTR Switch_ClampColor(GLenum target, GLenum clamp)
	{
		ClampColor = (PFNCLAMPCOLORPROC)IntGetProcAddress("glClampColor");
		ClampColor(target, clamp);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		ClearBufferfi = (PFNCLEARBUFFERFIPROC)IntGetProcAddress("glClearBufferfi");
		ClearBufferfi(buffer, drawbuffer, depth, stencil);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value)
	{
		ClearBufferfv = (PFNCLEARBUFFERFVPROC)IntGetProcAddress("glClearBufferfv");
		ClearBufferfv(buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value)
	{
		ClearBufferiv = (PFNCLEARBUFFERIVPROC)IntGetProcAddress("glClearBufferiv");
		ClearBufferiv(buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value)
	{
		ClearBufferuiv = (PFNCLEARBUFFERUIVPROC)IntGetProcAddress("glClearBufferuiv");
		ClearBufferuiv(buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
	{
		ColorMaski = (PFNCOLORMASKIPROC)IntGetProcAddress("glColorMaski");
		ColorMaski(index, r, g, b, a);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteFramebuffers(GLsizei n, const GLuint * framebuffers)
	{
		DeleteFramebuffers = (PFNDELETEFRAMEBUFFERSPROC)IntGetProcAddress("glDeleteFramebuffers");
		DeleteFramebuffers(n, framebuffers);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers)
	{
		DeleteRenderbuffers = (PFNDELETERENDERBUFFERSPROC)IntGetProcAddress("glDeleteRenderbuffers");
		DeleteRenderbuffers(n, renderbuffers);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteVertexArrays(GLsizei n, const GLuint * arrays)
	{
		DeleteVertexArrays = (PFNDELETEVERTEXARRAYSPROC)IntGetProcAddress("glDeleteVertexArrays");
		DeleteVertexArrays(n, arrays);
	}

	static void CODEGEN_FUNCPTR Switch_Disablei(GLenum target, GLuint index)
	{
		Disablei = (PFNDISABLEIPROC)IntGetProcAddress("glDisablei");
		Disablei(target, index);
	}

	static void CODEGEN_FUNCPTR Switch_Enablei(GLenum target, GLuint index)
	{
		Enablei = (PFNENABLEIPROC)IntGetProcAddress("glEnablei");
		Enablei(target, index);
	}

	static void CODEGEN_FUNCPTR Switch_EndConditionalRender(void)
	{
		EndConditionalRender = (PFNENDCONDITIONALRENDERPROC)IntGetProcAddress("glEndConditionalRender");
		EndConditionalRender();
	}

	static void CODEGEN_FUNCPTR Switch_EndTransformFeedback(void)
	{
		EndTransformFeedback = (PFNENDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glEndTransformFeedback");
		EndTransformFeedback();
	}

	static void CODEGEN_FUNCPTR Switch_FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
	{
		FlushMappedBufferRange = (PFNFLUSHMAPPEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedBufferRange");
		FlushMappedBufferRange(target, offset, length);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		FramebufferRenderbuffer = (PFNFRAMEBUFFERRENDERBUFFERPROC)IntGetProcAddress("glFramebufferRenderbuffer");
		FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		FramebufferTexture1D = (PFNFRAMEBUFFERTEXTURE1DPROC)IntGetProcAddress("glFramebufferTexture1D");
		FramebufferTexture1D(target, attachment, textarget, texture, level);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		FramebufferTexture2D = (PFNFRAMEBUFFERTEXTURE2DPROC)IntGetProcAddress("glFramebufferTexture2D");
		FramebufferTexture2D(target, attachment, textarget, texture, level);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
	{
		FramebufferTexture3D = (PFNFRAMEBUFFERTEXTURE3DPROC)IntGetProcAddress("glFramebufferTexture3D");
		FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		FramebufferTextureLayer = (PFNFRAMEBUFFERTEXTURELAYERPROC)IntGetProcAddress("glFramebufferTextureLayer");
		FramebufferTextureLayer(target, attachment, texture, level, layer);
	}

	static void CODEGEN_FUNCPTR Switch_GenFramebuffers(GLsizei n, GLuint * framebuffers)
	{
		GenFramebuffers = (PFNGENFRAMEBUFFERSPROC)IntGetProcAddress("glGenFramebuffers");
		GenFramebuffers(n, framebuffers);
	}

	static void CODEGEN_FUNCPTR Switch_GenRenderbuffers(GLsizei n, GLuint * renderbuffers)
	{
		GenRenderbuffers = (PFNGENRENDERBUFFERSPROC)IntGetProcAddress("glGenRenderbuffers");
		GenRenderbuffers(n, renderbuffers);
	}

	static void CODEGEN_FUNCPTR Switch_GenVertexArrays(GLsizei n, GLuint * arrays)
	{
		GenVertexArrays = (PFNGENVERTEXARRAYSPROC)IntGetProcAddress("glGenVertexArrays");
		GenVertexArrays(n, arrays);
	}

	static void CODEGEN_FUNCPTR Switch_GenerateMipmap(GLenum target)
	{
		GenerateMipmap = (PFNGENERATEMIPMAPPROC)IntGetProcAddress("glGenerateMipmap");
		GenerateMipmap(target);
	}

	static void CODEGEN_FUNCPTR Switch_GetBooleani_v(GLenum target, GLuint index, GLboolean * data)
	{
		GetBooleani_v = (PFNGETBOOLEANI_VPROC)IntGetProcAddress("glGetBooleani_v");
		GetBooleani_v(target, index, data);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetFragDataLocation(GLuint program, const GLchar * name)
	{
		GetFragDataLocation = (PFNGETFRAGDATALOCATIONPROC)IntGetProcAddress("glGetFragDataLocation");
		return GetFragDataLocation(program, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
	{
		GetFramebufferAttachmentParameteriv = (PFNGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)IntGetProcAddress("glGetFramebufferAttachmentParameteriv");
		GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetIntegeri_v(GLenum target, GLuint index, GLint * data)
	{
		GetIntegeri_v = (PFNGETINTEGERI_VPROC)IntGetProcAddress("glGetIntegeri_v");
		GetIntegeri_v(target, index, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
	{
		GetRenderbufferParameteriv = (PFNGETRENDERBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetRenderbufferParameteriv");
		GetRenderbufferParameteriv(target, pname, params);
	}

	static const GLubyte * CODEGEN_FUNCPTR Switch_GetStringi(GLenum name, GLuint index)
	{
		GetStringi = (PFNGETSTRINGIPROC)IntGetProcAddress("glGetStringi");
		return GetStringi(name, index);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
	{
		GetTexParameterIiv = (PFNGETTEXPARAMETERIIVPROC)IntGetProcAddress("glGetTexParameterIiv");
		GetTexParameterIiv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
	{
		GetTexParameterIuiv = (PFNGETTEXPARAMETERIUIVPROC)IntGetProcAddress("glGetTexParameterIuiv");
		GetTexParameterIuiv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
	{
		GetTransformFeedbackVarying = (PFNGETTRANSFORMFEEDBACKVARYINGPROC)IntGetProcAddress("glGetTransformFeedbackVarying");
		GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformuiv(GLuint program, GLint location, GLuint * params)
	{
		GetUniformuiv = (PFNGETUNIFORMUIVPROC)IntGetProcAddress("glGetUniformuiv");
		GetUniformuiv(program, location, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
	{
		GetVertexAttribIiv = (PFNGETVERTEXATTRIBIIVPROC)IntGetProcAddress("glGetVertexAttribIiv");
		GetVertexAttribIiv(index, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
	{
		GetVertexAttribIuiv = (PFNGETVERTEXATTRIBIUIVPROC)IntGetProcAddress("glGetVertexAttribIuiv");
		GetVertexAttribIuiv(index, pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsEnabledi(GLenum target, GLuint index)
	{
		IsEnabledi = (PFNISENABLEDIPROC)IntGetProcAddress("glIsEnabledi");
		return IsEnabledi(target, index);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsFramebuffer(GLuint framebuffer)
	{
		IsFramebuffer = (PFNISFRAMEBUFFERPROC)IntGetProcAddress("glIsFramebuffer");
		return IsFramebuffer(framebuffer);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsRenderbuffer(GLuint renderbuffer)
	{
		IsRenderbuffer = (PFNISRENDERBUFFERPROC)IntGetProcAddress("glIsRenderbuffer");
		return IsRenderbuffer(renderbuffer);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsVertexArray(GLuint ren_array)
	{
		IsVertexArray = (PFNISVERTEXARRAYPROC)IntGetProcAddress("glIsVertexArray");
		return IsVertexArray(ren_array);
	}

	static void * CODEGEN_FUNCPTR Switch_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		MapBufferRange = (PFNMAPBUFFERRANGEPROC)IntGetProcAddress("glMapBufferRange");
		return MapBufferRange(target, offset, length, access);
	}

	static void CODEGEN_FUNCPTR Switch_RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		RenderbufferStorage = (PFNRENDERBUFFERSTORAGEPROC)IntGetProcAddress("glRenderbufferStorage");
		RenderbufferStorage(target, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		RenderbufferStorageMultisample = (PFNRENDERBUFFERSTORAGEMULTISAMPLEPROC)IntGetProcAddress("glRenderbufferStorageMultisample");
		RenderbufferStorageMultisample(target, samples, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameterIiv(GLenum target, GLenum pname, const GLint * params)
	{
		TexParameterIiv = (PFNTEXPARAMETERIIVPROC)IntGetProcAddress("glTexParameterIiv");
		TexParameterIiv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params)
	{
		TexParameterIuiv = (PFNTEXPARAMETERIUIVPROC)IntGetProcAddress("glTexParameterIuiv");
		TexParameterIuiv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode)
	{
		TransformFeedbackVaryings = (PFNTRANSFORMFEEDBACKVARYINGSPROC)IntGetProcAddress("glTransformFeedbackVaryings");
		TransformFeedbackVaryings(program, count, varyings, bufferMode);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1ui(GLint location, GLuint v0)
	{
		Uniform1ui = (PFNUNIFORM1UIPROC)IntGetProcAddress("glUniform1ui");
		Uniform1ui(location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1uiv(GLint location, GLsizei count, const GLuint * value)
	{
		Uniform1uiv = (PFNUNIFORM1UIVPROC)IntGetProcAddress("glUniform1uiv");
		Uniform1uiv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2ui(GLint location, GLuint v0, GLuint v1)
	{
		Uniform2ui = (PFNUNIFORM2UIPROC)IntGetProcAddress("glUniform2ui");
		Uniform2ui(location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2uiv(GLint location, GLsizei count, const GLuint * value)
	{
		Uniform2uiv = (PFNUNIFORM2UIVPROC)IntGetProcAddress("glUniform2uiv");
		Uniform2uiv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		Uniform3ui = (PFNUNIFORM3UIPROC)IntGetProcAddress("glUniform3ui");
		Uniform3ui(location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3uiv(GLint location, GLsizei count, const GLuint * value)
	{
		Uniform3uiv = (PFNUNIFORM3UIVPROC)IntGetProcAddress("glUniform3uiv");
		Uniform3uiv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		Uniform4ui = (PFNUNIFORM4UIPROC)IntGetProcAddress("glUniform4ui");
		Uniform4ui(location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4uiv(GLint location, GLsizei count, const GLuint * value)
	{
		Uniform4uiv = (PFNUNIFORM4UIVPROC)IntGetProcAddress("glUniform4uiv");
		Uniform4uiv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI1i(GLuint index, GLint x)
	{
		VertexAttribI1i = (PFNVERTEXATTRIBI1IPROC)IntGetProcAddress("glVertexAttribI1i");
		VertexAttribI1i(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI1iv(GLuint index, const GLint * v)
	{
		VertexAttribI1iv = (PFNVERTEXATTRIBI1IVPROC)IntGetProcAddress("glVertexAttribI1iv");
		VertexAttribI1iv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI1ui(GLuint index, GLuint x)
	{
		VertexAttribI1ui = (PFNVERTEXATTRIBI1UIPROC)IntGetProcAddress("glVertexAttribI1ui");
		VertexAttribI1ui(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI1uiv(GLuint index, const GLuint * v)
	{
		VertexAttribI1uiv = (PFNVERTEXATTRIBI1UIVPROC)IntGetProcAddress("glVertexAttribI1uiv");
		VertexAttribI1uiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI2i(GLuint index, GLint x, GLint y)
	{
		VertexAttribI2i = (PFNVERTEXATTRIBI2IPROC)IntGetProcAddress("glVertexAttribI2i");
		VertexAttribI2i(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI2iv(GLuint index, const GLint * v)
	{
		VertexAttribI2iv = (PFNVERTEXATTRIBI2IVPROC)IntGetProcAddress("glVertexAttribI2iv");
		VertexAttribI2iv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI2ui(GLuint index, GLuint x, GLuint y)
	{
		VertexAttribI2ui = (PFNVERTEXATTRIBI2UIPROC)IntGetProcAddress("glVertexAttribI2ui");
		VertexAttribI2ui(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI2uiv(GLuint index, const GLuint * v)
	{
		VertexAttribI2uiv = (PFNVERTEXATTRIBI2UIVPROC)IntGetProcAddress("glVertexAttribI2uiv");
		VertexAttribI2uiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
	{
		VertexAttribI3i = (PFNVERTEXATTRIBI3IPROC)IntGetProcAddress("glVertexAttribI3i");
		VertexAttribI3i(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI3iv(GLuint index, const GLint * v)
	{
		VertexAttribI3iv = (PFNVERTEXATTRIBI3IVPROC)IntGetProcAddress("glVertexAttribI3iv");
		VertexAttribI3iv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
	{
		VertexAttribI3ui = (PFNVERTEXATTRIBI3UIPROC)IntGetProcAddress("glVertexAttribI3ui");
		VertexAttribI3ui(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI3uiv(GLuint index, const GLuint * v)
	{
		VertexAttribI3uiv = (PFNVERTEXATTRIBI3UIVPROC)IntGetProcAddress("glVertexAttribI3uiv");
		VertexAttribI3uiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4bv(GLuint index, const GLbyte * v)
	{
		VertexAttribI4bv = (PFNVERTEXATTRIBI4BVPROC)IntGetProcAddress("glVertexAttribI4bv");
		VertexAttribI4bv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
	{
		VertexAttribI4i = (PFNVERTEXATTRIBI4IPROC)IntGetProcAddress("glVertexAttribI4i");
		VertexAttribI4i(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4iv(GLuint index, const GLint * v)
	{
		VertexAttribI4iv = (PFNVERTEXATTRIBI4IVPROC)IntGetProcAddress("glVertexAttribI4iv");
		VertexAttribI4iv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4sv(GLuint index, const GLshort * v)
	{
		VertexAttribI4sv = (PFNVERTEXATTRIBI4SVPROC)IntGetProcAddress("glVertexAttribI4sv");
		VertexAttribI4sv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4ubv(GLuint index, const GLubyte * v)
	{
		VertexAttribI4ubv = (PFNVERTEXATTRIBI4UBVPROC)IntGetProcAddress("glVertexAttribI4ubv");
		VertexAttribI4ubv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
	{
		VertexAttribI4ui = (PFNVERTEXATTRIBI4UIPROC)IntGetProcAddress("glVertexAttribI4ui");
		VertexAttribI4ui(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4uiv(GLuint index, const GLuint * v)
	{
		VertexAttribI4uiv = (PFNVERTEXATTRIBI4UIVPROC)IntGetProcAddress("glVertexAttribI4uiv");
		VertexAttribI4uiv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribI4usv(GLuint index, const GLushort * v)
	{
		VertexAttribI4usv = (PFNVERTEXATTRIBI4USVPROC)IntGetProcAddress("glVertexAttribI4usv");
		VertexAttribI4usv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
	{
		VertexAttribIPointer = (PFNVERTEXATTRIBIPOINTERPROC)IntGetProcAddress("glVertexAttribIPointer");
		VertexAttribIPointer(index, size, type, stride, pointer);
	}

	
	// Extension: 3.1
	static void CODEGEN_FUNCPTR Switch_CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		CopyBufferSubData = (PFNCOPYBUFFERSUBDATAPROC)IntGetProcAddress("glCopyBufferSubData");
		CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	}

	static void CODEGEN_FUNCPTR Switch_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
	{
		DrawArraysInstanced = (PFNDRAWARRAYSINSTANCEDPROC)IntGetProcAddress("glDrawArraysInstanced");
		DrawArraysInstanced(mode, first, count, instancecount);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
	{
		DrawElementsInstanced = (PFNDRAWELEMENTSINSTANCEDPROC)IntGetProcAddress("glDrawElementsInstanced");
		DrawElementsInstanced(mode, count, type, indices, instancecount);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
	{
		GetActiveUniformBlockName = (PFNGETACTIVEUNIFORMBLOCKNAMEPROC)IntGetProcAddress("glGetActiveUniformBlockName");
		GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
	{
		GetActiveUniformBlockiv = (PFNGETACTIVEUNIFORMBLOCKIVPROC)IntGetProcAddress("glGetActiveUniformBlockiv");
		GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
	{
		GetActiveUniformName = (PFNGETACTIVEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveUniformName");
		GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params)
	{
		GetActiveUniformsiv = (PFNGETACTIVEUNIFORMSIVPROC)IntGetProcAddress("glGetActiveUniformsiv");
		GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	}

	static GLuint CODEGEN_FUNCPTR Switch_GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName)
	{
		GetUniformBlockIndex = (PFNGETUNIFORMBLOCKINDEXPROC)IntGetProcAddress("glGetUniformBlockIndex");
		return GetUniformBlockIndex(program, uniformBlockName);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
	{
		GetUniformIndices = (PFNGETUNIFORMINDICESPROC)IntGetProcAddress("glGetUniformIndices");
		GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	}

	static void CODEGEN_FUNCPTR Switch_PrimitiveRestartIndex(GLuint index)
	{
		PrimitiveRestartIndex = (PFNPRIMITIVERESTARTINDEXPROC)IntGetProcAddress("glPrimitiveRestartIndex");
		PrimitiveRestartIndex(index);
	}

	static void CODEGEN_FUNCPTR Switch_TexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
	{
		TexBuffer = (PFNTEXBUFFERPROC)IntGetProcAddress("glTexBuffer");
		TexBuffer(target, internalformat, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
	{
		UniformBlockBinding = (PFNUNIFORMBLOCKBINDINGPROC)IntGetProcAddress("glUniformBlockBinding");
		UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	}

	
	// Extension: 3.2
	static GLenum CODEGEN_FUNCPTR Switch_ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		ClientWaitSync = (PFNCLIENTWAITSYNCPROC)IntGetProcAddress("glClientWaitSync");
		return ClientWaitSync(sync, flags, timeout);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteSync(GLsync sync)
	{
		DeleteSync = (PFNDELETESYNCPROC)IntGetProcAddress("glDeleteSync");
		DeleteSync(sync);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
	{
		DrawElementsBaseVertex = (PFNDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawElementsBaseVertex");
		DrawElementsBaseVertex(mode, count, type, indices, basevertex);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
	{
		DrawElementsInstancedBaseVertex = (PFNDRAWELEMENTSINSTANCEDBASEVERTEXPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertex");
		DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
	}

	static void CODEGEN_FUNCPTR Switch_DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
	{
		DrawRangeElementsBaseVertex = (PFNDRAWRANGEELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawRangeElementsBaseVertex");
		DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	}

	static GLsync CODEGEN_FUNCPTR Switch_FenceSync(GLenum condition, GLbitfield flags)
	{
		FenceSync = (PFNFENCESYNCPROC)IntGetProcAddress("glFenceSync");
		return FenceSync(condition, flags);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
	{
		FramebufferTexture = (PFNFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glFramebufferTexture");
		FramebufferTexture(target, attachment, texture, level);
	}

	static void CODEGEN_FUNCPTR Switch_GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params)
	{
		GetBufferParameteri64v = (PFNGETBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetBufferParameteri64v");
		GetBufferParameteri64v(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetInteger64i_v(GLenum target, GLuint index, GLint64 * data)
	{
		GetInteger64i_v = (PFNGETINTEGER64I_VPROC)IntGetProcAddress("glGetInteger64i_v");
		GetInteger64i_v(target, index, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetInteger64v(GLenum pname, GLint64 * data)
	{
		GetInteger64v = (PFNGETINTEGER64VPROC)IntGetProcAddress("glGetInteger64v");
		GetInteger64v(pname, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
	{
		GetMultisamplefv = (PFNGETMULTISAMPLEFVPROC)IntGetProcAddress("glGetMultisamplefv");
		GetMultisamplefv(pname, index, val);
	}

	static void CODEGEN_FUNCPTR Switch_GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
	{
		GetSynciv = (PFNGETSYNCIVPROC)IntGetProcAddress("glGetSynciv");
		GetSynciv(sync, pname, bufSize, length, values);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsSync(GLsync sync)
	{
		IsSync = (PFNISSYNCPROC)IntGetProcAddress("glIsSync");
		return IsSync(sync);
	}

	static void CODEGEN_FUNCPTR Switch_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex)
	{
		MultiDrawElementsBaseVertex = (PFNMULTIDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glMultiDrawElementsBaseVertex");
		MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
	}

	static void CODEGEN_FUNCPTR Switch_ProvokingVertex(GLenum mode)
	{
		ProvokingVertex = (PFNPROVOKINGVERTEXPROC)IntGetProcAddress("glProvokingVertex");
		ProvokingVertex(mode);
	}

	static void CODEGEN_FUNCPTR Switch_SampleMaski(GLuint maskNumber, GLbitfield mask)
	{
		SampleMaski = (PFNSAMPLEMASKIPROC)IntGetProcAddress("glSampleMaski");
		SampleMaski(maskNumber, mask);
	}

	static void CODEGEN_FUNCPTR Switch_TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		TexImage2DMultisample = (PFNTEXIMAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexImage2DMultisample");
		TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		TexImage3DMultisample = (PFNTEXIMAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexImage3DMultisample");
		TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		WaitSync = (PFNWAITSYNCPROC)IntGetProcAddress("glWaitSync");
		WaitSync(sync, flags, timeout);
	}

	
	// Extension: 3.3
	static void CODEGEN_FUNCPTR Switch_BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name)
	{
		BindFragDataLocationIndexed = (PFNBINDFRAGDATALOCATIONINDEXEDPROC)IntGetProcAddress("glBindFragDataLocationIndexed");
		BindFragDataLocationIndexed(program, colorNumber, index, name);
	}

	static void CODEGEN_FUNCPTR Switch_BindSampler(GLuint unit, GLuint sampler)
	{
		BindSampler = (PFNBINDSAMPLERPROC)IntGetProcAddress("glBindSampler");
		BindSampler(unit, sampler);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteSamplers(GLsizei count, const GLuint * samplers)
	{
		DeleteSamplers = (PFNDELETESAMPLERSPROC)IntGetProcAddress("glDeleteSamplers");
		DeleteSamplers(count, samplers);
	}

	static void CODEGEN_FUNCPTR Switch_GenSamplers(GLsizei count, GLuint * samplers)
	{
		GenSamplers = (PFNGENSAMPLERSPROC)IntGetProcAddress("glGenSamplers");
		GenSamplers(count, samplers);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetFragDataIndex(GLuint program, const GLchar * name)
	{
		GetFragDataIndex = (PFNGETFRAGDATAINDEXPROC)IntGetProcAddress("glGetFragDataIndex");
		return GetFragDataIndex(program, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params)
	{
		GetQueryObjecti64v = (PFNGETQUERYOBJECTI64VPROC)IntGetProcAddress("glGetQueryObjecti64v");
		GetQueryObjecti64v(id, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params)
	{
		GetQueryObjectui64v = (PFNGETQUERYOBJECTUI64VPROC)IntGetProcAddress("glGetQueryObjectui64v");
		GetQueryObjectui64v(id, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
	{
		GetSamplerParameterIiv = (PFNGETSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glGetSamplerParameterIiv");
		GetSamplerParameterIiv(sampler, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
	{
		GetSamplerParameterIuiv = (PFNGETSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glGetSamplerParameterIuiv");
		GetSamplerParameterIuiv(sampler, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
	{
		GetSamplerParameterfv = (PFNGETSAMPLERPARAMETERFVPROC)IntGetProcAddress("glGetSamplerParameterfv");
		GetSamplerParameterfv(sampler, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
	{
		GetSamplerParameteriv = (PFNGETSAMPLERPARAMETERIVPROC)IntGetProcAddress("glGetSamplerParameteriv");
		GetSamplerParameteriv(sampler, pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsSampler(GLuint sampler)
	{
		IsSampler = (PFNISSAMPLERPROC)IntGetProcAddress("glIsSampler");
		return IsSampler(sampler);
	}

	static void CODEGEN_FUNCPTR Switch_QueryCounter(GLuint id, GLenum target)
	{
		QueryCounter = (PFNQUERYCOUNTERPROC)IntGetProcAddress("glQueryCounter");
		QueryCounter(id, target);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param)
	{
		SamplerParameterIiv = (PFNSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glSamplerParameterIiv");
		SamplerParameterIiv(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param)
	{
		SamplerParameterIuiv = (PFNSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glSamplerParameterIuiv");
		SamplerParameterIuiv(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
	{
		SamplerParameterf = (PFNSAMPLERPARAMETERFPROC)IntGetProcAddress("glSamplerParameterf");
		SamplerParameterf(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param)
	{
		SamplerParameterfv = (PFNSAMPLERPARAMETERFVPROC)IntGetProcAddress("glSamplerParameterfv");
		SamplerParameterfv(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameteri(GLuint sampler, GLenum pname, GLint param)
	{
		SamplerParameteri = (PFNSAMPLERPARAMETERIPROC)IntGetProcAddress("glSamplerParameteri");
		SamplerParameteri(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param)
	{
		SamplerParameteriv = (PFNSAMPLERPARAMETERIVPROC)IntGetProcAddress("glSamplerParameteriv");
		SamplerParameteriv(sampler, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribDivisor(GLuint index, GLuint divisor)
	{
		VertexAttribDivisor = (PFNVERTEXATTRIBDIVISORPROC)IntGetProcAddress("glVertexAttribDivisor");
		VertexAttribDivisor(index, divisor);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		VertexAttribP1ui = (PFNVERTEXATTRIBP1UIPROC)IntGetProcAddress("glVertexAttribP1ui");
		VertexAttribP1ui(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
	{
		VertexAttribP1uiv = (PFNVERTEXATTRIBP1UIVPROC)IntGetProcAddress("glVertexAttribP1uiv");
		VertexAttribP1uiv(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		VertexAttribP2ui = (PFNVERTEXATTRIBP2UIPROC)IntGetProcAddress("glVertexAttribP2ui");
		VertexAttribP2ui(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
	{
		VertexAttribP2uiv = (PFNVERTEXATTRIBP2UIVPROC)IntGetProcAddress("glVertexAttribP2uiv");
		VertexAttribP2uiv(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		VertexAttribP3ui = (PFNVERTEXATTRIBP3UIPROC)IntGetProcAddress("glVertexAttribP3ui");
		VertexAttribP3ui(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
	{
		VertexAttribP3uiv = (PFNVERTEXATTRIBP3UIVPROC)IntGetProcAddress("glVertexAttribP3uiv");
		VertexAttribP3uiv(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		VertexAttribP4ui = (PFNVERTEXATTRIBP4UIPROC)IntGetProcAddress("glVertexAttribP4ui");
		VertexAttribP4ui(index, type, normalized, value);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
	{
		VertexAttribP4uiv = (PFNVERTEXATTRIBP4UIVPROC)IntGetProcAddress("glVertexAttribP4uiv");
		VertexAttribP4uiv(index, type, normalized, value);
	}

	
	// Extension: 4.0
	static void CODEGEN_FUNCPTR Switch_BeginQueryIndexed(GLenum target, GLuint index, GLuint id)
	{
		BeginQueryIndexed = (PFNBEGINQUERYINDEXEDPROC)IntGetProcAddress("glBeginQueryIndexed");
		BeginQueryIndexed(target, index, id);
	}

	static void CODEGEN_FUNCPTR Switch_BindTransformFeedback(GLenum target, GLuint id)
	{
		BindTransformFeedback = (PFNBINDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBindTransformFeedback");
		BindTransformFeedback(target, id);
	}

	static void CODEGEN_FUNCPTR Switch_BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
	{
		BlendEquationSeparatei = (PFNBLENDEQUATIONSEPARATEIPROC)IntGetProcAddress("glBlendEquationSeparatei");
		BlendEquationSeparatei(buf, modeRGB, modeAlpha);
	}

	static void CODEGEN_FUNCPTR Switch_BlendEquationi(GLuint buf, GLenum mode)
	{
		BlendEquationi = (PFNBLENDEQUATIONIPROC)IntGetProcAddress("glBlendEquationi");
		BlendEquationi(buf, mode);
	}

	static void CODEGEN_FUNCPTR Switch_BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
	{
		BlendFuncSeparatei = (PFNBLENDFUNCSEPARATEIPROC)IntGetProcAddress("glBlendFuncSeparatei");
		BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	}

	static void CODEGEN_FUNCPTR Switch_BlendFunci(GLuint buf, GLenum src, GLenum dst)
	{
		BlendFunci = (PFNBLENDFUNCIPROC)IntGetProcAddress("glBlendFunci");
		BlendFunci(buf, src, dst);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteTransformFeedbacks(GLsizei n, const GLuint * ids)
	{
		DeleteTransformFeedbacks = (PFNDELETETRANSFORMFEEDBACKSPROC)IntGetProcAddress("glDeleteTransformFeedbacks");
		DeleteTransformFeedbacks(n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_DrawArraysIndirect(GLenum mode, const void * indirect)
	{
		DrawArraysIndirect = (PFNDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glDrawArraysIndirect");
		DrawArraysIndirect(mode, indirect);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsIndirect(GLenum mode, GLenum type, const void * indirect)
	{
		DrawElementsIndirect = (PFNDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glDrawElementsIndirect");
		DrawElementsIndirect(mode, type, indirect);
	}

	static void CODEGEN_FUNCPTR Switch_DrawTransformFeedback(GLenum mode, GLuint id)
	{
		DrawTransformFeedback = (PFNDRAWTRANSFORMFEEDBACKPROC)IntGetProcAddress("glDrawTransformFeedback");
		DrawTransformFeedback(mode, id);
	}

	static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
	{
		DrawTransformFeedbackStream = (PFNDRAWTRANSFORMFEEDBACKSTREAMPROC)IntGetProcAddress("glDrawTransformFeedbackStream");
		DrawTransformFeedbackStream(mode, id, stream);
	}

	static void CODEGEN_FUNCPTR Switch_EndQueryIndexed(GLenum target, GLuint index)
	{
		EndQueryIndexed = (PFNENDQUERYINDEXEDPROC)IntGetProcAddress("glEndQueryIndexed");
		EndQueryIndexed(target, index);
	}

	static void CODEGEN_FUNCPTR Switch_GenTransformFeedbacks(GLsizei n, GLuint * ids)
	{
		GenTransformFeedbacks = (PFNGENTRANSFORMFEEDBACKSPROC)IntGetProcAddress("glGenTransformFeedbacks");
		GenTransformFeedbacks(n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
	{
		GetActiveSubroutineName = (PFNGETACTIVESUBROUTINENAMEPROC)IntGetProcAddress("glGetActiveSubroutineName");
		GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
	{
		GetActiveSubroutineUniformName = (PFNGETACTIVESUBROUTINEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveSubroutineUniformName");
		GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
	{
		GetActiveSubroutineUniformiv = (PFNGETACTIVESUBROUTINEUNIFORMIVPROC)IntGetProcAddress("glGetActiveSubroutineUniformiv");
		GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
	{
		GetProgramStageiv = (PFNGETPROGRAMSTAGEIVPROC)IntGetProcAddress("glGetProgramStageiv");
		GetProgramStageiv(program, shadertype, pname, values);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
	{
		GetQueryIndexediv = (PFNGETQUERYINDEXEDIVPROC)IntGetProcAddress("glGetQueryIndexediv");
		GetQueryIndexediv(target, index, pname, params);
	}

	static GLuint CODEGEN_FUNCPTR Switch_GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name)
	{
		GetSubroutineIndex = (PFNGETSUBROUTINEINDEXPROC)IntGetProcAddress("glGetSubroutineIndex");
		return GetSubroutineIndex(program, shadertype, name);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name)
	{
		GetSubroutineUniformLocation = (PFNGETSUBROUTINEUNIFORMLOCATIONPROC)IntGetProcAddress("glGetSubroutineUniformLocation");
		return GetSubroutineUniformLocation(program, shadertype, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
	{
		GetUniformSubroutineuiv = (PFNGETUNIFORMSUBROUTINEUIVPROC)IntGetProcAddress("glGetUniformSubroutineuiv");
		GetUniformSubroutineuiv(shadertype, location, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetUniformdv(GLuint program, GLint location, GLdouble * params)
	{
		GetUniformdv = (PFNGETUNIFORMDVPROC)IntGetProcAddress("glGetUniformdv");
		GetUniformdv(program, location, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsTransformFeedback(GLuint id)
	{
		IsTransformFeedback = (PFNISTRANSFORMFEEDBACKPROC)IntGetProcAddress("glIsTransformFeedback");
		return IsTransformFeedback(id);
	}

	static void CODEGEN_FUNCPTR Switch_MinSampleShading(GLfloat value)
	{
		MinSampleShading = (PFNMINSAMPLESHADINGPROC)IntGetProcAddress("glMinSampleShading");
		MinSampleShading(value);
	}

	static void CODEGEN_FUNCPTR Switch_PatchParameterfv(GLenum pname, const GLfloat * values)
	{
		PatchParameterfv = (PFNPATCHPARAMETERFVPROC)IntGetProcAddress("glPatchParameterfv");
		PatchParameterfv(pname, values);
	}

	static void CODEGEN_FUNCPTR Switch_PatchParameteri(GLenum pname, GLint value)
	{
		PatchParameteri = (PFNPATCHPARAMETERIPROC)IntGetProcAddress("glPatchParameteri");
		PatchParameteri(pname, value);
	}

	static void CODEGEN_FUNCPTR Switch_PauseTransformFeedback(void)
	{
		PauseTransformFeedback = (PFNPAUSETRANSFORMFEEDBACKPROC)IntGetProcAddress("glPauseTransformFeedback");
		PauseTransformFeedback();
	}

	static void CODEGEN_FUNCPTR Switch_ResumeTransformFeedback(void)
	{
		ResumeTransformFeedback = (PFNRESUMETRANSFORMFEEDBACKPROC)IntGetProcAddress("glResumeTransformFeedback");
		ResumeTransformFeedback();
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1d(GLint location, GLdouble x)
	{
		Uniform1d = (PFNUNIFORM1DPROC)IntGetProcAddress("glUniform1d");
		Uniform1d(location, x);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform1dv(GLint location, GLsizei count, const GLdouble * value)
	{
		Uniform1dv = (PFNUNIFORM1DVPROC)IntGetProcAddress("glUniform1dv");
		Uniform1dv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2d(GLint location, GLdouble x, GLdouble y)
	{
		Uniform2d = (PFNUNIFORM2DPROC)IntGetProcAddress("glUniform2d");
		Uniform2d(location, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform2dv(GLint location, GLsizei count, const GLdouble * value)
	{
		Uniform2dv = (PFNUNIFORM2DVPROC)IntGetProcAddress("glUniform2dv");
		Uniform2dv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
	{
		Uniform3d = (PFNUNIFORM3DPROC)IntGetProcAddress("glUniform3d");
		Uniform3d(location, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform3dv(GLint location, GLsizei count, const GLdouble * value)
	{
		Uniform3dv = (PFNUNIFORM3DVPROC)IntGetProcAddress("glUniform3dv");
		Uniform3dv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		Uniform4d = (PFNUNIFORM4DPROC)IntGetProcAddress("glUniform4d");
		Uniform4d(location, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_Uniform4dv(GLint location, GLsizei count, const GLdouble * value)
	{
		Uniform4dv = (PFNUNIFORM4DVPROC)IntGetProcAddress("glUniform4dv");
		Uniform4dv(location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix2dv = (PFNUNIFORMMATRIX2DVPROC)IntGetProcAddress("glUniformMatrix2dv");
		UniformMatrix2dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix2x3dv = (PFNUNIFORMMATRIX2X3DVPROC)IntGetProcAddress("glUniformMatrix2x3dv");
		UniformMatrix2x3dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix2x4dv = (PFNUNIFORMMATRIX2X4DVPROC)IntGetProcAddress("glUniformMatrix2x4dv");
		UniformMatrix2x4dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix3dv = (PFNUNIFORMMATRIX3DVPROC)IntGetProcAddress("glUniformMatrix3dv");
		UniformMatrix3dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix3x2dv = (PFNUNIFORMMATRIX3X2DVPROC)IntGetProcAddress("glUniformMatrix3x2dv");
		UniformMatrix3x2dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix3x4dv = (PFNUNIFORMMATRIX3X4DVPROC)IntGetProcAddress("glUniformMatrix3x4dv");
		UniformMatrix3x4dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix4dv = (PFNUNIFORMMATRIX4DVPROC)IntGetProcAddress("glUniformMatrix4dv");
		UniformMatrix4dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix4x2dv = (PFNUNIFORMMATRIX4X2DVPROC)IntGetProcAddress("glUniformMatrix4x2dv");
		UniformMatrix4x2dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		UniformMatrix4x3dv = (PFNUNIFORMMATRIX4X3DVPROC)IntGetProcAddress("glUniformMatrix4x3dv");
		UniformMatrix4x3dv(location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices)
	{
		UniformSubroutinesuiv = (PFNUNIFORMSUBROUTINESUIVPROC)IntGetProcAddress("glUniformSubroutinesuiv");
		UniformSubroutinesuiv(shadertype, count, indices);
	}

	
	// Extension: 4.1
	static void CODEGEN_FUNCPTR Switch_ActiveShaderProgram(GLuint pipeline, GLuint program)
	{
		ActiveShaderProgram = (PFNACTIVESHADERPROGRAMPROC)IntGetProcAddress("glActiveShaderProgram");
		ActiveShaderProgram(pipeline, program);
	}

	static void CODEGEN_FUNCPTR Switch_BindProgramPipeline(GLuint pipeline)
	{
		BindProgramPipeline = (PFNBINDPROGRAMPIPELINEPROC)IntGetProcAddress("glBindProgramPipeline");
		BindProgramPipeline(pipeline);
	}

	static void CODEGEN_FUNCPTR Switch_ClearDepthf(GLfloat d)
	{
		ClearDepthf = (PFNCLEARDEPTHFPROC)IntGetProcAddress("glClearDepthf");
		ClearDepthf(d);
	}

	static GLuint CODEGEN_FUNCPTR Switch_CreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings)
	{
		CreateShaderProgramv = (PFNCREATESHADERPROGRAMVPROC)IntGetProcAddress("glCreateShaderProgramv");
		return CreateShaderProgramv(type, count, strings);
	}

	static void CODEGEN_FUNCPTR Switch_DeleteProgramPipelines(GLsizei n, const GLuint * pipelines)
	{
		DeleteProgramPipelines = (PFNDELETEPROGRAMPIPELINESPROC)IntGetProcAddress("glDeleteProgramPipelines");
		DeleteProgramPipelines(n, pipelines);
	}

	static void CODEGEN_FUNCPTR Switch_DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v)
	{
		DepthRangeArrayv = (PFNDEPTHRANGEARRAYVPROC)IntGetProcAddress("glDepthRangeArrayv");
		DepthRangeArrayv(first, count, v);
	}

	static void CODEGEN_FUNCPTR Switch_DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
	{
		DepthRangeIndexed = (PFNDEPTHRANGEINDEXEDPROC)IntGetProcAddress("glDepthRangeIndexed");
		DepthRangeIndexed(index, n, f);
	}

	static void CODEGEN_FUNCPTR Switch_DepthRangef(GLfloat n, GLfloat f)
	{
		DepthRangef = (PFNDEPTHRANGEFPROC)IntGetProcAddress("glDepthRangef");
		DepthRangef(n, f);
	}

	static void CODEGEN_FUNCPTR Switch_GenProgramPipelines(GLsizei n, GLuint * pipelines)
	{
		GenProgramPipelines = (PFNGENPROGRAMPIPELINESPROC)IntGetProcAddress("glGenProgramPipelines");
		GenProgramPipelines(n, pipelines);
	}

	static void CODEGEN_FUNCPTR Switch_GetDoublei_v(GLenum target, GLuint index, GLdouble * data)
	{
		GetDoublei_v = (PFNGETDOUBLEI_VPROC)IntGetProcAddress("glGetDoublei_v");
		GetDoublei_v(target, index, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetFloati_v(GLenum target, GLuint index, GLfloat * data)
	{
		GetFloati_v = (PFNGETFLOATI_VPROC)IntGetProcAddress("glGetFloati_v");
		GetFloati_v(target, index, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary)
	{
		GetProgramBinary = (PFNGETPROGRAMBINARYPROC)IntGetProcAddress("glGetProgramBinary");
		GetProgramBinary(program, bufSize, length, binaryFormat, binary);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
	{
		GetProgramPipelineInfoLog = (PFNGETPROGRAMPIPELINEINFOLOGPROC)IntGetProcAddress("glGetProgramPipelineInfoLog");
		GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
	{
		GetProgramPipelineiv = (PFNGETPROGRAMPIPELINEIVPROC)IntGetProcAddress("glGetProgramPipelineiv");
		GetProgramPipelineiv(pipeline, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
	{
		GetShaderPrecisionFormat = (PFNGETSHADERPRECISIONFORMATPROC)IntGetProcAddress("glGetShaderPrecisionFormat");
		GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
	{
		GetVertexAttribLdv = (PFNGETVERTEXATTRIBLDVPROC)IntGetProcAddress("glGetVertexAttribLdv");
		GetVertexAttribLdv(index, pname, params);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_IsProgramPipeline(GLuint pipeline)
	{
		IsProgramPipeline = (PFNISPROGRAMPIPELINEPROC)IntGetProcAddress("glIsProgramPipeline");
		return IsProgramPipeline(pipeline);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length)
	{
		ProgramBinary = (PFNPROGRAMBINARYPROC)IntGetProcAddress("glProgramBinary");
		ProgramBinary(program, binaryFormat, binary, length);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramParameteri(GLuint program, GLenum pname, GLint value)
	{
		ProgramParameteri = (PFNPROGRAMPARAMETERIPROC)IntGetProcAddress("glProgramParameteri");
		ProgramParameteri(program, pname, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1d(GLuint program, GLint location, GLdouble v0)
	{
		ProgramUniform1d = (PFNPROGRAMUNIFORM1DPROC)IntGetProcAddress("glProgramUniform1d");
		ProgramUniform1d(program, location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
	{
		ProgramUniform1dv = (PFNPROGRAMUNIFORM1DVPROC)IntGetProcAddress("glProgramUniform1dv");
		ProgramUniform1dv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1f(GLuint program, GLint location, GLfloat v0)
	{
		ProgramUniform1f = (PFNPROGRAMUNIFORM1FPROC)IntGetProcAddress("glProgramUniform1f");
		ProgramUniform1f(program, location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
	{
		ProgramUniform1fv = (PFNPROGRAMUNIFORM1FVPROC)IntGetProcAddress("glProgramUniform1fv");
		ProgramUniform1fv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1i(GLuint program, GLint location, GLint v0)
	{
		ProgramUniform1i = (PFNPROGRAMUNIFORM1IPROC)IntGetProcAddress("glProgramUniform1i");
		ProgramUniform1i(program, location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value)
	{
		ProgramUniform1iv = (PFNPROGRAMUNIFORM1IVPROC)IntGetProcAddress("glProgramUniform1iv");
		ProgramUniform1iv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1ui(GLuint program, GLint location, GLuint v0)
	{
		ProgramUniform1ui = (PFNPROGRAMUNIFORM1UIPROC)IntGetProcAddress("glProgramUniform1ui");
		ProgramUniform1ui(program, location, v0);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
	{
		ProgramUniform1uiv = (PFNPROGRAMUNIFORM1UIVPROC)IntGetProcAddress("glProgramUniform1uiv");
		ProgramUniform1uiv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
	{
		ProgramUniform2d = (PFNPROGRAMUNIFORM2DPROC)IntGetProcAddress("glProgramUniform2d");
		ProgramUniform2d(program, location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
	{
		ProgramUniform2dv = (PFNPROGRAMUNIFORM2DVPROC)IntGetProcAddress("glProgramUniform2dv");
		ProgramUniform2dv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
	{
		ProgramUniform2f = (PFNPROGRAMUNIFORM2FPROC)IntGetProcAddress("glProgramUniform2f");
		ProgramUniform2f(program, location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
	{
		ProgramUniform2fv = (PFNPROGRAMUNIFORM2FVPROC)IntGetProcAddress("glProgramUniform2fv");
		ProgramUniform2fv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
	{
		ProgramUniform2i = (PFNPROGRAMUNIFORM2IPROC)IntGetProcAddress("glProgramUniform2i");
		ProgramUniform2i(program, location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value)
	{
		ProgramUniform2iv = (PFNPROGRAMUNIFORM2IVPROC)IntGetProcAddress("glProgramUniform2iv");
		ProgramUniform2iv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
	{
		ProgramUniform2ui = (PFNPROGRAMUNIFORM2UIPROC)IntGetProcAddress("glProgramUniform2ui");
		ProgramUniform2ui(program, location, v0, v1);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
	{
		ProgramUniform2uiv = (PFNPROGRAMUNIFORM2UIVPROC)IntGetProcAddress("glProgramUniform2uiv");
		ProgramUniform2uiv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
	{
		ProgramUniform3d = (PFNPROGRAMUNIFORM3DPROC)IntGetProcAddress("glProgramUniform3d");
		ProgramUniform3d(program, location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
	{
		ProgramUniform3dv = (PFNPROGRAMUNIFORM3DVPROC)IntGetProcAddress("glProgramUniform3dv");
		ProgramUniform3dv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		ProgramUniform3f = (PFNPROGRAMUNIFORM3FPROC)IntGetProcAddress("glProgramUniform3f");
		ProgramUniform3f(program, location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
	{
		ProgramUniform3fv = (PFNPROGRAMUNIFORM3FVPROC)IntGetProcAddress("glProgramUniform3fv");
		ProgramUniform3fv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
	{
		ProgramUniform3i = (PFNPROGRAMUNIFORM3IPROC)IntGetProcAddress("glProgramUniform3i");
		ProgramUniform3i(program, location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value)
	{
		ProgramUniform3iv = (PFNPROGRAMUNIFORM3IVPROC)IntGetProcAddress("glProgramUniform3iv");
		ProgramUniform3iv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		ProgramUniform3ui = (PFNPROGRAMUNIFORM3UIPROC)IntGetProcAddress("glProgramUniform3ui");
		ProgramUniform3ui(program, location, v0, v1, v2);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
	{
		ProgramUniform3uiv = (PFNPROGRAMUNIFORM3UIVPROC)IntGetProcAddress("glProgramUniform3uiv");
		ProgramUniform3uiv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
	{
		ProgramUniform4d = (PFNPROGRAMUNIFORM4DPROC)IntGetProcAddress("glProgramUniform4d");
		ProgramUniform4d(program, location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
	{
		ProgramUniform4dv = (PFNPROGRAMUNIFORM4DVPROC)IntGetProcAddress("glProgramUniform4dv");
		ProgramUniform4dv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		ProgramUniform4f = (PFNPROGRAMUNIFORM4FPROC)IntGetProcAddress("glProgramUniform4f");
		ProgramUniform4f(program, location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
	{
		ProgramUniform4fv = (PFNPROGRAMUNIFORM4FVPROC)IntGetProcAddress("glProgramUniform4fv");
		ProgramUniform4fv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		ProgramUniform4i = (PFNPROGRAMUNIFORM4IPROC)IntGetProcAddress("glProgramUniform4i");
		ProgramUniform4i(program, location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value)
	{
		ProgramUniform4iv = (PFNPROGRAMUNIFORM4IVPROC)IntGetProcAddress("glProgramUniform4iv");
		ProgramUniform4iv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		ProgramUniform4ui = (PFNPROGRAMUNIFORM4UIPROC)IntGetProcAddress("glProgramUniform4ui");
		ProgramUniform4ui(program, location, v0, v1, v2, v3);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
	{
		ProgramUniform4uiv = (PFNPROGRAMUNIFORM4UIVPROC)IntGetProcAddress("glProgramUniform4uiv");
		ProgramUniform4uiv(program, location, count, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix2dv = (PFNPROGRAMUNIFORMMATRIX2DVPROC)IntGetProcAddress("glProgramUniformMatrix2dv");
		ProgramUniformMatrix2dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix2fv = (PFNPROGRAMUNIFORMMATRIX2FVPROC)IntGetProcAddress("glProgramUniformMatrix2fv");
		ProgramUniformMatrix2fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix2x3dv = (PFNPROGRAMUNIFORMMATRIX2X3DVPROC)IntGetProcAddress("glProgramUniformMatrix2x3dv");
		ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix2x3fv = (PFNPROGRAMUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glProgramUniformMatrix2x3fv");
		ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix2x4dv = (PFNPROGRAMUNIFORMMATRIX2X4DVPROC)IntGetProcAddress("glProgramUniformMatrix2x4dv");
		ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix2x4fv = (PFNPROGRAMUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glProgramUniformMatrix2x4fv");
		ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix3dv = (PFNPROGRAMUNIFORMMATRIX3DVPROC)IntGetProcAddress("glProgramUniformMatrix3dv");
		ProgramUniformMatrix3dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix3fv = (PFNPROGRAMUNIFORMMATRIX3FVPROC)IntGetProcAddress("glProgramUniformMatrix3fv");
		ProgramUniformMatrix3fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix3x2dv = (PFNPROGRAMUNIFORMMATRIX3X2DVPROC)IntGetProcAddress("glProgramUniformMatrix3x2dv");
		ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix3x2fv = (PFNPROGRAMUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glProgramUniformMatrix3x2fv");
		ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix3x4dv = (PFNPROGRAMUNIFORMMATRIX3X4DVPROC)IntGetProcAddress("glProgramUniformMatrix3x4dv");
		ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix3x4fv = (PFNPROGRAMUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glProgramUniformMatrix3x4fv");
		ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix4dv = (PFNPROGRAMUNIFORMMATRIX4DVPROC)IntGetProcAddress("glProgramUniformMatrix4dv");
		ProgramUniformMatrix4dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix4fv = (PFNPROGRAMUNIFORMMATRIX4FVPROC)IntGetProcAddress("glProgramUniformMatrix4fv");
		ProgramUniformMatrix4fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix4x2dv = (PFNPROGRAMUNIFORMMATRIX4X2DVPROC)IntGetProcAddress("glProgramUniformMatrix4x2dv");
		ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix4x2fv = (PFNPROGRAMUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glProgramUniformMatrix4x2fv");
		ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
	{
		ProgramUniformMatrix4x3dv = (PFNPROGRAMUNIFORMMATRIX4X3DVPROC)IntGetProcAddress("glProgramUniformMatrix4x3dv");
		ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		ProgramUniformMatrix4x3fv = (PFNPROGRAMUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glProgramUniformMatrix4x3fv");
		ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	}

	static void CODEGEN_FUNCPTR Switch_ReleaseShaderCompiler(void)
	{
		ReleaseShaderCompiler = (PFNRELEASESHADERCOMPILERPROC)IntGetProcAddress("glReleaseShaderCompiler");
		ReleaseShaderCompiler();
	}

	static void CODEGEN_FUNCPTR Switch_ScissorArrayv(GLuint first, GLsizei count, const GLint * v)
	{
		ScissorArrayv = (PFNSCISSORARRAYVPROC)IntGetProcAddress("glScissorArrayv");
		ScissorArrayv(first, count, v);
	}

	static void CODEGEN_FUNCPTR Switch_ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
	{
		ScissorIndexed = (PFNSCISSORINDEXEDPROC)IntGetProcAddress("glScissorIndexed");
		ScissorIndexed(index, left, bottom, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_ScissorIndexedv(GLuint index, const GLint * v)
	{
		ScissorIndexedv = (PFNSCISSORINDEXEDVPROC)IntGetProcAddress("glScissorIndexedv");
		ScissorIndexedv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length)
	{
		ShaderBinary = (PFNSHADERBINARYPROC)IntGetProcAddress("glShaderBinary");
		ShaderBinary(count, shaders, binaryformat, binary, length);
	}

	static void CODEGEN_FUNCPTR Switch_UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
	{
		UseProgramStages = (PFNUSEPROGRAMSTAGESPROC)IntGetProcAddress("glUseProgramStages");
		UseProgramStages(pipeline, stages, program);
	}

	static void CODEGEN_FUNCPTR Switch_ValidateProgramPipeline(GLuint pipeline)
	{
		ValidateProgramPipeline = (PFNVALIDATEPROGRAMPIPELINEPROC)IntGetProcAddress("glValidateProgramPipeline");
		ValidateProgramPipeline(pipeline);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL1d(GLuint index, GLdouble x)
	{
		VertexAttribL1d = (PFNVERTEXATTRIBL1DPROC)IntGetProcAddress("glVertexAttribL1d");
		VertexAttribL1d(index, x);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL1dv(GLuint index, const GLdouble * v)
	{
		VertexAttribL1dv = (PFNVERTEXATTRIBL1DVPROC)IntGetProcAddress("glVertexAttribL1dv");
		VertexAttribL1dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
	{
		VertexAttribL2d = (PFNVERTEXATTRIBL2DPROC)IntGetProcAddress("glVertexAttribL2d");
		VertexAttribL2d(index, x, y);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL2dv(GLuint index, const GLdouble * v)
	{
		VertexAttribL2dv = (PFNVERTEXATTRIBL2DVPROC)IntGetProcAddress("glVertexAttribL2dv");
		VertexAttribL2dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		VertexAttribL3d = (PFNVERTEXATTRIBL3DPROC)IntGetProcAddress("glVertexAttribL3d");
		VertexAttribL3d(index, x, y, z);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL3dv(GLuint index, const GLdouble * v)
	{
		VertexAttribL3dv = (PFNVERTEXATTRIBL3DVPROC)IntGetProcAddress("glVertexAttribL3dv");
		VertexAttribL3dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		VertexAttribL4d = (PFNVERTEXATTRIBL4DPROC)IntGetProcAddress("glVertexAttribL4d");
		VertexAttribL4d(index, x, y, z, w);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribL4dv(GLuint index, const GLdouble * v)
	{
		VertexAttribL4dv = (PFNVERTEXATTRIBL4DVPROC)IntGetProcAddress("glVertexAttribL4dv");
		VertexAttribL4dv(index, v);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
	{
		VertexAttribLPointer = (PFNVERTEXATTRIBLPOINTERPROC)IntGetProcAddress("glVertexAttribLPointer");
		VertexAttribLPointer(index, size, type, stride, pointer);
	}

	static void CODEGEN_FUNCPTR Switch_ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v)
	{
		ViewportArrayv = (PFNVIEWPORTARRAYVPROC)IntGetProcAddress("glViewportArrayv");
		ViewportArrayv(first, count, v);
	}

	static void CODEGEN_FUNCPTR Switch_ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
	{
		ViewportIndexedf = (PFNVIEWPORTINDEXEDFPROC)IntGetProcAddress("glViewportIndexedf");
		ViewportIndexedf(index, x, y, w, h);
	}

	static void CODEGEN_FUNCPTR Switch_ViewportIndexedfv(GLuint index, const GLfloat * v)
	{
		ViewportIndexedfv = (PFNVIEWPORTINDEXEDFVPROC)IntGetProcAddress("glViewportIndexedfv");
		ViewportIndexedfv(index, v);
	}

	
	// Extension: 4.2
	static void CODEGEN_FUNCPTR Switch_BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
	{
		BindImageTexture = (PFNBINDIMAGETEXTUREPROC)IntGetProcAddress("glBindImageTexture");
		BindImageTexture(unit, texture, level, layered, layer, access, format);
	}

	static void CODEGEN_FUNCPTR Switch_DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
	{
		DrawArraysInstancedBaseInstance = (PFNDRAWARRAYSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawArraysInstancedBaseInstance");
		DrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance)
	{
		DrawElementsInstancedBaseInstance = (PFNDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseInstance");
		DrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
	}

	static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
	{
		DrawElementsInstancedBaseVertexBaseInstance = (PFNDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
		DrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
	}

	static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
	{
		DrawTransformFeedbackInstanced = (PFNDRAWTRANSFORMFEEDBACKINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackInstanced");
		DrawTransformFeedbackInstanced(mode, id, instancecount);
	}

	static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
	{
		DrawTransformFeedbackStreamInstanced = (PFNDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackStreamInstanced");
		DrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
	}

	static void CODEGEN_FUNCPTR Switch_GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
	{
		GetActiveAtomicCounterBufferiv = (PFNGETACTIVEATOMICCOUNTERBUFFERIVPROC)IntGetProcAddress("glGetActiveAtomicCounterBufferiv");
		GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
	{
		GetInternalformativ = (PFNGETINTERNALFORMATIVPROC)IntGetProcAddress("glGetInternalformativ");
		GetInternalformativ(target, internalformat, pname, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_MemoryBarrier(GLbitfield barriers)
	{
		MemoryBarrier = (PFNMEMORYBARRIERPROC)IntGetProcAddress("glMemoryBarrier");
		MemoryBarrier(barriers);
	}

	static void CODEGEN_FUNCPTR Switch_TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		TexStorage1D = (PFNTEXSTORAGE1DPROC)IntGetProcAddress("glTexStorage1D");
		TexStorage1D(target, levels, internalformat, width);
	}

	static void CODEGEN_FUNCPTR Switch_TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		TexStorage2D = (PFNTEXSTORAGE2DPROC)IntGetProcAddress("glTexStorage2D");
		TexStorage2D(target, levels, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		TexStorage3D = (PFNTEXSTORAGE3DPROC)IntGetProcAddress("glTexStorage3D");
		TexStorage3D(target, levels, internalformat, width, height, depth);
	}

	
	// Extension: 4.3
	static void CODEGEN_FUNCPTR Switch_BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		BindVertexBuffer = (PFNBINDVERTEXBUFFERPROC)IntGetProcAddress("glBindVertexBuffer");
		BindVertexBuffer(bindingindex, buffer, offset, stride);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data)
	{
		ClearBufferData = (PFNCLEARBUFFERDATAPROC)IntGetProcAddress("glClearBufferData");
		ClearBufferData(target, internalformat, format, type, data);
	}

	static void CODEGEN_FUNCPTR Switch_ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
	{
		ClearBufferSubData = (PFNCLEARBUFFERSUBDATAPROC)IntGetProcAddress("glClearBufferSubData");
		ClearBufferSubData(target, internalformat, offset, size, format, type, data);
	}

	static void CODEGEN_FUNCPTR Switch_CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
	{
		CopyImageSubData = (PFNCOPYIMAGESUBDATAPROC)IntGetProcAddress("glCopyImageSubData");
		CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
	}

	static void CODEGEN_FUNCPTR Switch_DebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
	{
		DebugMessageCallback = (PFNDEBUGMESSAGECALLBACKPROC)IntGetProcAddress("glDebugMessageCallback");
		DebugMessageCallback(callback, userParam);
	}

	static void CODEGEN_FUNCPTR Switch_DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
	{
		DebugMessageControl = (PFNDEBUGMESSAGECONTROLPROC)IntGetProcAddress("glDebugMessageControl");
		DebugMessageControl(source, type, severity, count, ids, enabled);
	}

	static void CODEGEN_FUNCPTR Switch_DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
	{
		DebugMessageInsert = (PFNDEBUGMESSAGEINSERTPROC)IntGetProcAddress("glDebugMessageInsert");
		DebugMessageInsert(source, type, id, severity, length, buf);
	}

	static void CODEGEN_FUNCPTR Switch_DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
	{
		DispatchCompute = (PFNDISPATCHCOMPUTEPROC)IntGetProcAddress("glDispatchCompute");
		DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
	}

	static void CODEGEN_FUNCPTR Switch_DispatchComputeIndirect(GLintptr indirect)
	{
		DispatchComputeIndirect = (PFNDISPATCHCOMPUTEINDIRECTPROC)IntGetProcAddress("glDispatchComputeIndirect");
		DispatchComputeIndirect(indirect);
	}

	static void CODEGEN_FUNCPTR Switch_FramebufferParameteri(GLenum target, GLenum pname, GLint param)
	{
		FramebufferParameteri = (PFNFRAMEBUFFERPARAMETERIPROC)IntGetProcAddress("glFramebufferParameteri");
		FramebufferParameteri(target, pname, param);
	}

	static GLuint CODEGEN_FUNCPTR Switch_GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
	{
		GetDebugMessageLog = (PFNGETDEBUGMESSAGELOGPROC)IntGetProcAddress("glGetDebugMessageLog");
		return GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	}

	static void CODEGEN_FUNCPTR Switch_GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params)
	{
		GetFramebufferParameteriv = (PFNGETFRAMEBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetFramebufferParameteriv");
		GetFramebufferParameteriv(target, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params)
	{
		GetInternalformati64v = (PFNGETINTERNALFORMATI64VPROC)IntGetProcAddress("glGetInternalformati64v");
		GetInternalformati64v(target, internalformat, pname, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
	{
		GetObjectLabel = (PFNGETOBJECTLABELPROC)IntGetProcAddress("glGetObjectLabel");
		GetObjectLabel(identifier, name, bufSize, length, label);
	}

	static void CODEGEN_FUNCPTR Switch_GetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
	{
		GetObjectPtrLabel = (PFNGETOBJECTPTRLABELPROC)IntGetProcAddress("glGetObjectPtrLabel");
		GetObjectPtrLabel(ptr, bufSize, length, label);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params)
	{
		GetProgramInterfaceiv = (PFNGETPROGRAMINTERFACEIVPROC)IntGetProcAddress("glGetProgramInterfaceiv");
		GetProgramInterfaceiv(program, programInterface, pname, params);
	}

	static GLuint CODEGEN_FUNCPTR Switch_GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name)
	{
		GetProgramResourceIndex = (PFNGETPROGRAMRESOURCEINDEXPROC)IntGetProcAddress("glGetProgramResourceIndex");
		return GetProgramResourceIndex(program, programInterface, name);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name)
	{
		GetProgramResourceLocation = (PFNGETPROGRAMRESOURCELOCATIONPROC)IntGetProcAddress("glGetProgramResourceLocation");
		return GetProgramResourceLocation(program, programInterface, name);
	}

	static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name)
	{
		GetProgramResourceLocationIndex = (PFNGETPROGRAMRESOURCELOCATIONINDEXPROC)IntGetProcAddress("glGetProgramResourceLocationIndex");
		return GetProgramResourceLocationIndex(program, programInterface, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
	{
		GetProgramResourceName = (PFNGETPROGRAMRESOURCENAMEPROC)IntGetProcAddress("glGetProgramResourceName");
		GetProgramResourceName(program, programInterface, index, bufSize, length, name);
	}

	static void CODEGEN_FUNCPTR Switch_GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params)
	{
		GetProgramResourceiv = (PFNGETPROGRAMRESOURCEIVPROC)IntGetProcAddress("glGetProgramResourceiv");
		GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateBufferData(GLuint buffer)
	{
		InvalidateBufferData = (PFNINVALIDATEBUFFERDATAPROC)IntGetProcAddress("glInvalidateBufferData");
		InvalidateBufferData(buffer);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		InvalidateBufferSubData = (PFNINVALIDATEBUFFERSUBDATAPROC)IntGetProcAddress("glInvalidateBufferSubData");
		InvalidateBufferSubData(buffer, offset, length);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments)
	{
		InvalidateFramebuffer = (PFNINVALIDATEFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateFramebuffer");
		InvalidateFramebuffer(target, numAttachments, attachments);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		InvalidateSubFramebuffer = (PFNINVALIDATESUBFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateSubFramebuffer");
		InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateTexImage(GLuint texture, GLint level)
	{
		InvalidateTexImage = (PFNINVALIDATETEXIMAGEPROC)IntGetProcAddress("glInvalidateTexImage");
		InvalidateTexImage(texture, level);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
	{
		InvalidateTexSubImage = (PFNINVALIDATETEXSUBIMAGEPROC)IntGetProcAddress("glInvalidateTexSubImage");
		InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
	}

	static void CODEGEN_FUNCPTR Switch_MultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride)
	{
		MultiDrawArraysIndirect = (PFNMULTIDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glMultiDrawArraysIndirect");
		MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
	}

	static void CODEGEN_FUNCPTR Switch_MultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride)
	{
		MultiDrawElementsIndirect = (PFNMULTIDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glMultiDrawElementsIndirect");
		MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
	}

	static void CODEGEN_FUNCPTR Switch_ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label)
	{
		ObjectLabel = (PFNOBJECTLABELPROC)IntGetProcAddress("glObjectLabel");
		ObjectLabel(identifier, name, length, label);
	}

	static void CODEGEN_FUNCPTR Switch_ObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
	{
		ObjectPtrLabel = (PFNOBJECTPTRLABELPROC)IntGetProcAddress("glObjectPtrLabel");
		ObjectPtrLabel(ptr, length, label);
	}

	static void CODEGEN_FUNCPTR Switch_PopDebugGroup(void)
	{
		PopDebugGroup = (PFNPOPDEBUGGROUPPROC)IntGetProcAddress("glPopDebugGroup");
		PopDebugGroup();
	}

	static void CODEGEN_FUNCPTR Switch_PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message)
	{
		PushDebugGroup = (PFNPUSHDEBUGGROUPPROC)IntGetProcAddress("glPushDebugGroup");
		PushDebugGroup(source, id, length, message);
	}

	static void CODEGEN_FUNCPTR Switch_ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
	{
		ShaderStorageBlockBinding = (PFNSHADERSTORAGEBLOCKBINDINGPROC)IntGetProcAddress("glShaderStorageBlockBinding");
		ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
	}

	static void CODEGEN_FUNCPTR Switch_TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		TexBufferRange = (PFNTEXBUFFERRANGEPROC)IntGetProcAddress("glTexBufferRange");
		TexBufferRange(target, internalformat, buffer, offset, size);
	}

	static void CODEGEN_FUNCPTR Switch_TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		TexStorage2DMultisample = (PFNTEXSTORAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage2DMultisample");
		TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		TexStorage3DMultisample = (PFNTEXSTORAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage3DMultisample");
		TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
	{
		TextureView = (PFNTEXTUREVIEWPROC)IntGetProcAddress("glTextureView");
		TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribBinding(GLuint attribindex, GLuint bindingindex)
	{
		VertexAttribBinding = (PFNVERTEXATTRIBBINDINGPROC)IntGetProcAddress("glVertexAttribBinding");
		VertexAttribBinding(attribindex, bindingindex);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		VertexAttribFormat = (PFNVERTEXATTRIBFORMATPROC)IntGetProcAddress("glVertexAttribFormat");
		VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		VertexAttribIFormat = (PFNVERTEXATTRIBIFORMATPROC)IntGetProcAddress("glVertexAttribIFormat");
		VertexAttribIFormat(attribindex, size, type, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		VertexAttribLFormat = (PFNVERTEXATTRIBLFORMATPROC)IntGetProcAddress("glVertexAttribLFormat");
		VertexAttribLFormat(attribindex, size, type, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexBindingDivisor(GLuint bindingindex, GLuint divisor)
	{
		VertexBindingDivisor = (PFNVERTEXBINDINGDIVISORPROC)IntGetProcAddress("glVertexBindingDivisor");
		VertexBindingDivisor(bindingindex, divisor);
	}

	
	// Extension: 4.4
	static void CODEGEN_FUNCPTR Switch_BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers)
	{
		BindBuffersBase = (PFNBINDBUFFERSBASEPROC)IntGetProcAddress("glBindBuffersBase");
		BindBuffersBase(target, first, count, buffers);
	}

	static void CODEGEN_FUNCPTR Switch_BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes)
	{
		BindBuffersRange = (PFNBINDBUFFERSRANGEPROC)IntGetProcAddress("glBindBuffersRange");
		BindBuffersRange(target, first, count, buffers, offsets, sizes);
	}

	static void CODEGEN_FUNCPTR Switch_BindImageTextures(GLuint first, GLsizei count, const GLuint * textures)
	{
		BindImageTextures = (PFNBINDIMAGETEXTURESPROC)IntGetProcAddress("glBindImageTextures");
		BindImageTextures(first, count, textures);
	}

	static void CODEGEN_FUNCPTR Switch_BindSamplers(GLuint first, GLsizei count, const GLuint * samplers)
	{
		BindSamplers = (PFNBINDSAMPLERSPROC)IntGetProcAddress("glBindSamplers");
		BindSamplers(first, count, samplers);
	}

	static void CODEGEN_FUNCPTR Switch_BindTextures(GLuint first, GLsizei count, const GLuint * textures)
	{
		BindTextures = (PFNBINDTEXTURESPROC)IntGetProcAddress("glBindTextures");
		BindTextures(first, count, textures);
	}

	static void CODEGEN_FUNCPTR Switch_BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
	{
		BindVertexBuffers = (PFNBINDVERTEXBUFFERSPROC)IntGetProcAddress("glBindVertexBuffers");
		BindVertexBuffers(first, count, buffers, offsets, strides);
	}

	static void CODEGEN_FUNCPTR Switch_BufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags)
	{
		BufferStorage = (PFNBUFFERSTORAGEPROC)IntGetProcAddress("glBufferStorage");
		BufferStorage(target, size, data, flags);
	}

	static void CODEGEN_FUNCPTR Switch_ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data)
	{
		ClearTexImage = (PFNCLEARTEXIMAGEPROC)IntGetProcAddress("glClearTexImage");
		ClearTexImage(texture, level, format, type, data);
	}

	static void CODEGEN_FUNCPTR Switch_ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data)
	{
		ClearTexSubImage = (PFNCLEARTEXSUBIMAGEPROC)IntGetProcAddress("glClearTexSubImage");
		ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	}

	
	// Extension: 4.5
	static void CODEGEN_FUNCPTR Switch_BindTextureUnit(GLuint unit, GLuint texture)
	{
		BindTextureUnit = (PFNBINDTEXTUREUNITPROC)IntGetProcAddress("glBindTextureUnit");
		BindTextureUnit(unit, texture);
	}

	static void CODEGEN_FUNCPTR Switch_BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		BlitNamedFramebuffer = (PFNBLITNAMEDFRAMEBUFFERPROC)IntGetProcAddress("glBlitNamedFramebuffer");
		BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	static GLenum CODEGEN_FUNCPTR Switch_CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
	{
		CheckNamedFramebufferStatus = (PFNCHECKNAMEDFRAMEBUFFERSTATUSPROC)IntGetProcAddress("glCheckNamedFramebufferStatus");
		return CheckNamedFramebufferStatus(framebuffer, target);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
	{
		ClearNamedBufferData = (PFNCLEARNAMEDBUFFERDATAPROC)IntGetProcAddress("glClearNamedBufferData");
		ClearNamedBufferData(buffer, internalformat, format, type, data);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
	{
		ClearNamedBufferSubData = (PFNCLEARNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glClearNamedBufferSubData");
		ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil)
	{
		ClearNamedFramebufferfi = (PFNCLEARNAMEDFRAMEBUFFERFIPROC)IntGetProcAddress("glClearNamedFramebufferfi");
		ClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value)
	{
		ClearNamedFramebufferfv = (PFNCLEARNAMEDFRAMEBUFFERFVPROC)IntGetProcAddress("glClearNamedFramebufferfv");
		ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value)
	{
		ClearNamedFramebufferiv = (PFNCLEARNAMEDFRAMEBUFFERIVPROC)IntGetProcAddress("glClearNamedFramebufferiv");
		ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value)
	{
		ClearNamedFramebufferuiv = (PFNCLEARNAMEDFRAMEBUFFERUIVPROC)IntGetProcAddress("glClearNamedFramebufferuiv");
		ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
	}

	static void CODEGEN_FUNCPTR Switch_ClipControl(GLenum origin, GLenum depth)
	{
		ClipControl = (PFNCLIPCONTROLPROC)IntGetProcAddress("glClipControl");
		ClipControl(origin, depth);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTextureSubImage1D = (PFNCOMPRESSEDTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glCompressedTextureSubImage1D");
		CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTextureSubImage2D = (PFNCOMPRESSEDTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glCompressedTextureSubImage2D");
		CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
	{
		CompressedTextureSubImage3D = (PFNCOMPRESSEDTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glCompressedTextureSubImage3D");
		CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		CopyNamedBufferSubData = (PFNCOPYNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glCopyNamedBufferSubData");
		CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		CopyTextureSubImage1D = (PFNCOPYTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glCopyTextureSubImage1D");
		CopyTextureSubImage1D(texture, level, xoffset, x, y, width);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		CopyTextureSubImage2D = (PFNCOPYTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glCopyTextureSubImage2D");
		CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		CopyTextureSubImage3D = (PFNCOPYTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glCopyTextureSubImage3D");
		CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_CreateBuffers(GLsizei n, GLuint * buffers)
	{
		CreateBuffers = (PFNCREATEBUFFERSPROC)IntGetProcAddress("glCreateBuffers");
		CreateBuffers(n, buffers);
	}

	static void CODEGEN_FUNCPTR Switch_CreateFramebuffers(GLsizei n, GLuint * framebuffers)
	{
		CreateFramebuffers = (PFNCREATEFRAMEBUFFERSPROC)IntGetProcAddress("glCreateFramebuffers");
		CreateFramebuffers(n, framebuffers);
	}

	static void CODEGEN_FUNCPTR Switch_CreateProgramPipelines(GLsizei n, GLuint * pipelines)
	{
		CreateProgramPipelines = (PFNCREATEPROGRAMPIPELINESPROC)IntGetProcAddress("glCreateProgramPipelines");
		CreateProgramPipelines(n, pipelines);
	}

	static void CODEGEN_FUNCPTR Switch_CreateQueries(GLenum target, GLsizei n, GLuint * ids)
	{
		CreateQueries = (PFNCREATEQUERIESPROC)IntGetProcAddress("glCreateQueries");
		CreateQueries(target, n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_CreateRenderbuffers(GLsizei n, GLuint * renderbuffers)
	{
		CreateRenderbuffers = (PFNCREATERENDERBUFFERSPROC)IntGetProcAddress("glCreateRenderbuffers");
		CreateRenderbuffers(n, renderbuffers);
	}

	static void CODEGEN_FUNCPTR Switch_CreateSamplers(GLsizei n, GLuint * samplers)
	{
		CreateSamplers = (PFNCREATESAMPLERSPROC)IntGetProcAddress("glCreateSamplers");
		CreateSamplers(n, samplers);
	}

	static void CODEGEN_FUNCPTR Switch_CreateTextures(GLenum target, GLsizei n, GLuint * textures)
	{
		CreateTextures = (PFNCREATETEXTURESPROC)IntGetProcAddress("glCreateTextures");
		CreateTextures(target, n, textures);
	}

	static void CODEGEN_FUNCPTR Switch_CreateTransformFeedbacks(GLsizei n, GLuint * ids)
	{
		CreateTransformFeedbacks = (PFNCREATETRANSFORMFEEDBACKSPROC)IntGetProcAddress("glCreateTransformFeedbacks");
		CreateTransformFeedbacks(n, ids);
	}

	static void CODEGEN_FUNCPTR Switch_CreateVertexArrays(GLsizei n, GLuint * arrays)
	{
		CreateVertexArrays = (PFNCREATEVERTEXARRAYSPROC)IntGetProcAddress("glCreateVertexArrays");
		CreateVertexArrays(n, arrays);
	}

	static void CODEGEN_FUNCPTR Switch_DisableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		DisableVertexArrayAttrib = (PFNDISABLEVERTEXARRAYATTRIBPROC)IntGetProcAddress("glDisableVertexArrayAttrib");
		DisableVertexArrayAttrib(vaobj, index);
	}

	static void CODEGEN_FUNCPTR Switch_EnableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		EnableVertexArrayAttrib = (PFNENABLEVERTEXARRAYATTRIBPROC)IntGetProcAddress("glEnableVertexArrayAttrib");
		EnableVertexArrayAttrib(vaobj, index);
	}

	static void CODEGEN_FUNCPTR Switch_FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		FlushMappedNamedBufferRange = (PFNFLUSHMAPPEDNAMEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedNamedBufferRange");
		FlushMappedNamedBufferRange(buffer, offset, length);
	}

	static void CODEGEN_FUNCPTR Switch_GenerateTextureMipmap(GLuint texture)
	{
		GenerateTextureMipmap = (PFNGENERATETEXTUREMIPMAPPROC)IntGetProcAddress("glGenerateTextureMipmap");
		GenerateTextureMipmap(texture);
	}

	static void CODEGEN_FUNCPTR Switch_GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels)
	{
		GetCompressedTextureImage = (PFNGETCOMPRESSEDTEXTUREIMAGEPROC)IntGetProcAddress("glGetCompressedTextureImage");
		GetCompressedTextureImage(texture, level, bufSize, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels)
	{
		GetCompressedTextureSubImage = (PFNGETCOMPRESSEDTEXTURESUBIMAGEPROC)IntGetProcAddress("glGetCompressedTextureSubImage");
		GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
	}

	static GLenum CODEGEN_FUNCPTR Switch_GetGraphicsResetStatus(void)
	{
		GetGraphicsResetStatus = (PFNGETGRAPHICSRESETSTATUSPROC)IntGetProcAddress("glGetGraphicsResetStatus");
		return GetGraphicsResetStatus();
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params)
	{
		GetNamedBufferParameteri64v = (PFNGETNAMEDBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetNamedBufferParameteri64v");
		GetNamedBufferParameteri64v(buffer, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params)
	{
		GetNamedBufferParameteriv = (PFNGETNAMEDBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedBufferParameteriv");
		GetNamedBufferParameteriv(buffer, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params)
	{
		GetNamedBufferPointerv = (PFNGETNAMEDBUFFERPOINTERVPROC)IntGetProcAddress("glGetNamedBufferPointerv");
		GetNamedBufferPointerv(buffer, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data)
	{
		GetNamedBufferSubData = (PFNGETNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glGetNamedBufferSubData");
		GetNamedBufferSubData(buffer, offset, size, data);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params)
	{
		GetNamedFramebufferAttachmentParameteriv = (PFNGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)IntGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
		GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param)
	{
		GetNamedFramebufferParameteriv = (PFNGETNAMEDFRAMEBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedFramebufferParameteriv");
		GetNamedFramebufferParameteriv(framebuffer, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params)
	{
		GetNamedRenderbufferParameteriv = (PFNGETNAMEDRENDERBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedRenderbufferParameteriv");
		GetNamedRenderbufferParameteriv(renderbuffer, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		GetQueryBufferObjecti64v = (PFNGETQUERYBUFFEROBJECTI64VPROC)IntGetProcAddress("glGetQueryBufferObjecti64v");
		GetQueryBufferObjecti64v(id, buffer, pname, offset);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		GetQueryBufferObjectiv = (PFNGETQUERYBUFFEROBJECTIVPROC)IntGetProcAddress("glGetQueryBufferObjectiv");
		GetQueryBufferObjectiv(id, buffer, pname, offset);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		GetQueryBufferObjectui64v = (PFNGETQUERYBUFFEROBJECTUI64VPROC)IntGetProcAddress("glGetQueryBufferObjectui64v");
		GetQueryBufferObjectui64v(id, buffer, pname, offset);
	}

	static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		GetQueryBufferObjectuiv = (PFNGETQUERYBUFFEROBJECTUIVPROC)IntGetProcAddress("glGetQueryBufferObjectuiv");
		GetQueryBufferObjectuiv(id, buffer, pname, offset);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
	{
		GetTextureImage = (PFNGETTEXTUREIMAGEPROC)IntGetProcAddress("glGetTextureImage");
		GetTextureImage(texture, level, format, type, bufSize, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params)
	{
		GetTextureLevelParameterfv = (PFNGETTEXTURELEVELPARAMETERFVPROC)IntGetProcAddress("glGetTextureLevelParameterfv");
		GetTextureLevelParameterfv(texture, level, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params)
	{
		GetTextureLevelParameteriv = (PFNGETTEXTURELEVELPARAMETERIVPROC)IntGetProcAddress("glGetTextureLevelParameteriv");
		GetTextureLevelParameteriv(texture, level, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params)
	{
		GetTextureParameterIiv = (PFNGETTEXTUREPARAMETERIIVPROC)IntGetProcAddress("glGetTextureParameterIiv");
		GetTextureParameterIiv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params)
	{
		GetTextureParameterIuiv = (PFNGETTEXTUREPARAMETERIUIVPROC)IntGetProcAddress("glGetTextureParameterIuiv");
		GetTextureParameterIuiv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params)
	{
		GetTextureParameterfv = (PFNGETTEXTUREPARAMETERFVPROC)IntGetProcAddress("glGetTextureParameterfv");
		GetTextureParameterfv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params)
	{
		GetTextureParameteriv = (PFNGETTEXTUREPARAMETERIVPROC)IntGetProcAddress("glGetTextureParameteriv");
		GetTextureParameteriv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
	{
		GetTextureSubImage = (PFNGETTEXTURESUBIMAGEPROC)IntGetProcAddress("glGetTextureSubImage");
		GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param)
	{
		GetTransformFeedbacki64_v = (PFNGETTRANSFORMFEEDBACKI64_VPROC)IntGetProcAddress("glGetTransformFeedbacki64_v");
		GetTransformFeedbacki64_v(xfb, pname, index, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param)
	{
		GetTransformFeedbacki_v = (PFNGETTRANSFORMFEEDBACKI_VPROC)IntGetProcAddress("glGetTransformFeedbacki_v");
		GetTransformFeedbacki_v(xfb, pname, index, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param)
	{
		GetTransformFeedbackiv = (PFNGETTRANSFORMFEEDBACKIVPROC)IntGetProcAddress("glGetTransformFeedbackiv");
		GetTransformFeedbackiv(xfb, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param)
	{
		GetVertexArrayIndexed64iv = (PFNGETVERTEXARRAYINDEXED64IVPROC)IntGetProcAddress("glGetVertexArrayIndexed64iv");
		GetVertexArrayIndexed64iv(vaobj, index, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param)
	{
		GetVertexArrayIndexediv = (PFNGETVERTEXARRAYINDEXEDIVPROC)IntGetProcAddress("glGetVertexArrayIndexediv");
		GetVertexArrayIndexediv(vaobj, index, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param)
	{
		GetVertexArrayiv = (PFNGETVERTEXARRAYIVPROC)IntGetProcAddress("glGetVertexArrayiv");
		GetVertexArrayiv(vaobj, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels)
	{
		GetnCompressedTexImage = (PFNGETNCOMPRESSEDTEXIMAGEPROC)IntGetProcAddress("glGetnCompressedTexImage");
		GetnCompressedTexImage(target, lod, bufSize, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
	{
		GetnTexImage = (PFNGETNTEXIMAGEPROC)IntGetProcAddress("glGetnTexImage");
		GetnTexImage(target, level, format, type, bufSize, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
	{
		GetnUniformdv = (PFNGETNUNIFORMDVPROC)IntGetProcAddress("glGetnUniformdv");
		GetnUniformdv(program, location, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
	{
		GetnUniformfv = (PFNGETNUNIFORMFVPROC)IntGetProcAddress("glGetnUniformfv");
		GetnUniformfv(program, location, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params)
	{
		GetnUniformiv = (PFNGETNUNIFORMIVPROC)IntGetProcAddress("glGetnUniformiv");
		GetnUniformiv(program, location, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
	{
		GetnUniformuiv = (PFNGETNUNIFORMUIVPROC)IntGetProcAddress("glGetnUniformuiv");
		GetnUniformuiv(program, location, bufSize, params);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments)
	{
		InvalidateNamedFramebufferData = (PFNINVALIDATENAMEDFRAMEBUFFERDATAPROC)IntGetProcAddress("glInvalidateNamedFramebufferData");
		InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
	}

	static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		InvalidateNamedFramebufferSubData = (PFNINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)IntGetProcAddress("glInvalidateNamedFramebufferSubData");
		InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
	}

	static void * CODEGEN_FUNCPTR Switch_MapNamedBuffer(GLuint buffer, GLenum access)
	{
		MapNamedBuffer = (PFNMAPNAMEDBUFFERPROC)IntGetProcAddress("glMapNamedBuffer");
		return MapNamedBuffer(buffer, access);
	}

	static void * CODEGEN_FUNCPTR Switch_MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		MapNamedBufferRange = (PFNMAPNAMEDBUFFERRANGEPROC)IntGetProcAddress("glMapNamedBufferRange");
		return MapNamedBufferRange(buffer, offset, length, access);
	}

	static void CODEGEN_FUNCPTR Switch_MemoryBarrierByRegion(GLbitfield barriers)
	{
		MemoryBarrierByRegion = (PFNMEMORYBARRIERBYREGIONPROC)IntGetProcAddress("glMemoryBarrierByRegion");
		MemoryBarrierByRegion(barriers);
	}

	static void CODEGEN_FUNCPTR Switch_NamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage)
	{
		NamedBufferData = (PFNNAMEDBUFFERDATAPROC)IntGetProcAddress("glNamedBufferData");
		NamedBufferData(buffer, size, data, usage);
	}

	static void CODEGEN_FUNCPTR Switch_NamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags)
	{
		NamedBufferStorage = (PFNNAMEDBUFFERSTORAGEPROC)IntGetProcAddress("glNamedBufferStorage");
		NamedBufferStorage(buffer, size, data, flags);
	}

	static void CODEGEN_FUNCPTR Switch_NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data)
	{
		NamedBufferSubData = (PFNNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glNamedBufferSubData");
		NamedBufferSubData(buffer, offset, size, data);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
	{
		NamedFramebufferDrawBuffer = (PFNNAMEDFRAMEBUFFERDRAWBUFFERPROC)IntGetProcAddress("glNamedFramebufferDrawBuffer");
		NamedFramebufferDrawBuffer(framebuffer, buf);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs)
	{
		NamedFramebufferDrawBuffers = (PFNNAMEDFRAMEBUFFERDRAWBUFFERSPROC)IntGetProcAddress("glNamedFramebufferDrawBuffers");
		NamedFramebufferDrawBuffers(framebuffer, n, bufs);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
	{
		NamedFramebufferParameteri = (PFNNAMEDFRAMEBUFFERPARAMETERIPROC)IntGetProcAddress("glNamedFramebufferParameteri");
		NamedFramebufferParameteri(framebuffer, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
	{
		NamedFramebufferReadBuffer = (PFNNAMEDFRAMEBUFFERREADBUFFERPROC)IntGetProcAddress("glNamedFramebufferReadBuffer");
		NamedFramebufferReadBuffer(framebuffer, src);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		NamedFramebufferRenderbuffer = (PFNNAMEDFRAMEBUFFERRENDERBUFFERPROC)IntGetProcAddress("glNamedFramebufferRenderbuffer");
		NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
	{
		NamedFramebufferTexture = (PFNNAMEDFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glNamedFramebufferTexture");
		NamedFramebufferTexture(framebuffer, attachment, texture, level);
	}

	static void CODEGEN_FUNCPTR Switch_NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		NamedFramebufferTextureLayer = (PFNNAMEDFRAMEBUFFERTEXTURELAYERPROC)IntGetProcAddress("glNamedFramebufferTextureLayer");
		NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
	}

	static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
	{
		NamedRenderbufferStorage = (PFNNAMEDRENDERBUFFERSTORAGEPROC)IntGetProcAddress("glNamedRenderbufferStorage");
		NamedRenderbufferStorage(renderbuffer, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		NamedRenderbufferStorageMultisample = (PFNNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)IntGetProcAddress("glNamedRenderbufferStorageMultisample");
		NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
	{
		ReadnPixels = (PFNREADNPIXELSPROC)IntGetProcAddress("glReadnPixels");
		ReadnPixels(x, y, width, height, format, type, bufSize, data);
	}

	static void CODEGEN_FUNCPTR Switch_TextureBarrier(void)
	{
		TextureBarrier = (PFNTEXTUREBARRIERPROC)IntGetProcAddress("glTextureBarrier");
		TextureBarrier();
	}

	static void CODEGEN_FUNCPTR Switch_TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
	{
		TextureBuffer = (PFNTEXTUREBUFFERPROC)IntGetProcAddress("glTextureBuffer");
		TextureBuffer(texture, internalformat, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		TextureBufferRange = (PFNTEXTUREBUFFERRANGEPROC)IntGetProcAddress("glTextureBufferRange");
		TextureBufferRange(texture, internalformat, buffer, offset, size);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params)
	{
		TextureParameterIiv = (PFNTEXTUREPARAMETERIIVPROC)IntGetProcAddress("glTextureParameterIiv");
		TextureParameterIiv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params)
	{
		TextureParameterIuiv = (PFNTEXTUREPARAMETERIUIVPROC)IntGetProcAddress("glTextureParameterIuiv");
		TextureParameterIuiv(texture, pname, params);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameterf(GLuint texture, GLenum pname, GLfloat param)
	{
		TextureParameterf = (PFNTEXTUREPARAMETERFPROC)IntGetProcAddress("glTextureParameterf");
		TextureParameterf(texture, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param)
	{
		TextureParameterfv = (PFNTEXTUREPARAMETERFVPROC)IntGetProcAddress("glTextureParameterfv");
		TextureParameterfv(texture, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameteri(GLuint texture, GLenum pname, GLint param)
	{
		TextureParameteri = (PFNTEXTUREPARAMETERIPROC)IntGetProcAddress("glTextureParameteri");
		TextureParameteri(texture, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TextureParameteriv(GLuint texture, GLenum pname, const GLint * param)
	{
		TextureParameteriv = (PFNTEXTUREPARAMETERIVPROC)IntGetProcAddress("glTextureParameteriv");
		TextureParameteriv(texture, pname, param);
	}

	static void CODEGEN_FUNCPTR Switch_TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		TextureStorage1D = (PFNTEXTURESTORAGE1DPROC)IntGetProcAddress("glTextureStorage1D");
		TextureStorage1D(texture, levels, internalformat, width);
	}

	static void CODEGEN_FUNCPTR Switch_TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		TextureStorage2D = (PFNTEXTURESTORAGE2DPROC)IntGetProcAddress("glTextureStorage2D");
		TextureStorage2D(texture, levels, internalformat, width, height);
	}

	static void CODEGEN_FUNCPTR Switch_TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		TextureStorage2DMultisample = (PFNTEXTURESTORAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTextureStorage2DMultisample");
		TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		TextureStorage3D = (PFNTEXTURESTORAGE3DPROC)IntGetProcAddress("glTextureStorage3D");
		TextureStorage3D(texture, levels, internalformat, width, height, depth);
	}

	static void CODEGEN_FUNCPTR Switch_TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		TextureStorage3DMultisample = (PFNTEXTURESTORAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTextureStorage3DMultisample");
		TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	static void CODEGEN_FUNCPTR Switch_TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
	{
		TextureSubImage1D = (PFNTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glTextureSubImage1D");
		TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
	{
		TextureSubImage2D = (PFNTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glTextureSubImage2D");
		TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
	{
		TextureSubImage3D = (PFNTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glTextureSubImage3D");
		TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
	{
		TransformFeedbackBufferBase = (PFNTRANSFORMFEEDBACKBUFFERBASEPROC)IntGetProcAddress("glTransformFeedbackBufferBase");
		TransformFeedbackBufferBase(xfb, index, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		TransformFeedbackBufferRange = (PFNTRANSFORMFEEDBACKBUFFERRANGEPROC)IntGetProcAddress("glTransformFeedbackBufferRange");
		TransformFeedbackBufferRange(xfb, index, buffer, offset, size);
	}

	static GLboolean CODEGEN_FUNCPTR Switch_UnmapNamedBuffer(GLuint buffer)
	{
		UnmapNamedBuffer = (PFNUNMAPNAMEDBUFFERPROC)IntGetProcAddress("glUnmapNamedBuffer");
		return UnmapNamedBuffer(buffer);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
	{
		VertexArrayAttribBinding = (PFNVERTEXARRAYATTRIBBINDINGPROC)IntGetProcAddress("glVertexArrayAttribBinding");
		VertexArrayAttribBinding(vaobj, attribindex, bindingindex);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		VertexArrayAttribFormat = (PFNVERTEXARRAYATTRIBFORMATPROC)IntGetProcAddress("glVertexArrayAttribFormat");
		VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		VertexArrayAttribIFormat = (PFNVERTEXARRAYATTRIBIFORMATPROC)IntGetProcAddress("glVertexArrayAttribIFormat");
		VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		VertexArrayAttribLFormat = (PFNVERTEXARRAYATTRIBLFORMATPROC)IntGetProcAddress("glVertexArrayAttribLFormat");
		VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
	{
		VertexArrayBindingDivisor = (PFNVERTEXARRAYBINDINGDIVISORPROC)IntGetProcAddress("glVertexArrayBindingDivisor");
		VertexArrayBindingDivisor(vaobj, bindingindex, divisor);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
	{
		VertexArrayElementBuffer = (PFNVERTEXARRAYELEMENTBUFFERPROC)IntGetProcAddress("glVertexArrayElementBuffer");
		VertexArrayElementBuffer(vaobj, buffer);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		VertexArrayVertexBuffer = (PFNVERTEXARRAYVERTEXBUFFERPROC)IntGetProcAddress("glVertexArrayVertexBuffer");
		VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
	}

	static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
	{
		VertexArrayVertexBuffers = (PFNVERTEXARRAYVERTEXBUFFERSPROC)IntGetProcAddress("glVertexArrayVertexBuffers");
		VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
	}

	
	
	namespace 
	{
		struct InitializeVariables
		{
			InitializeVariables()
			{
				// Extension: 1.0
				BlendFunc = Switch_BlendFunc;
				Clear = Switch_Clear;
				ClearColor = Switch_ClearColor;
				ClearDepth = Switch_ClearDepth;
				ClearStencil = Switch_ClearStencil;
				ColorMask = Switch_ColorMask;
				CullFace = Switch_CullFace;
				DepthFunc = Switch_DepthFunc;
				DepthMask = Switch_DepthMask;
				DepthRange = Switch_DepthRange;
				Disable = Switch_Disable;
				DrawBuffer = Switch_DrawBuffer;
				Enable = Switch_Enable;
				Finish = Switch_Finish;
				Flush = Switch_Flush;
				FrontFace = Switch_FrontFace;
				GetBooleanv = Switch_GetBooleanv;
				GetDoublev = Switch_GetDoublev;
				GetError = Switch_GetError;
				GetFloatv = Switch_GetFloatv;
				GetIntegerv = Switch_GetIntegerv;
				GetString = Switch_GetString;
				GetTexImage = Switch_GetTexImage;
				GetTexLevelParameterfv = Switch_GetTexLevelParameterfv;
				GetTexLevelParameteriv = Switch_GetTexLevelParameteriv;
				GetTexParameterfv = Switch_GetTexParameterfv;
				GetTexParameteriv = Switch_GetTexParameteriv;
				Hint = Switch_Hint;
				IsEnabled = Switch_IsEnabled;
				LineWidth = Switch_LineWidth;
				LogicOp = Switch_LogicOp;
				PixelStoref = Switch_PixelStoref;
				PixelStorei = Switch_PixelStorei;
				PointSize = Switch_PointSize;
				PolygonMode = Switch_PolygonMode;
				ReadBuffer = Switch_ReadBuffer;
				ReadPixels = Switch_ReadPixels;
				Scissor = Switch_Scissor;
				StencilFunc = Switch_StencilFunc;
				StencilMask = Switch_StencilMask;
				StencilOp = Switch_StencilOp;
				TexImage1D = Switch_TexImage1D;
				TexImage2D = Switch_TexImage2D;
				TexParameterf = Switch_TexParameterf;
				TexParameterfv = Switch_TexParameterfv;
				TexParameteri = Switch_TexParameteri;
				TexParameteriv = Switch_TexParameteriv;
				Viewport = Switch_Viewport;
				
				// Extension: 1.1
				BindTexture = Switch_BindTexture;
				CopyTexImage1D = Switch_CopyTexImage1D;
				CopyTexImage2D = Switch_CopyTexImage2D;
				CopyTexSubImage1D = Switch_CopyTexSubImage1D;
				CopyTexSubImage2D = Switch_CopyTexSubImage2D;
				DeleteTextures = Switch_DeleteTextures;
				DrawArrays = Switch_DrawArrays;
				DrawElements = Switch_DrawElements;
				GenTextures = Switch_GenTextures;
				GetPointerv = Switch_GetPointerv;
				IsTexture = Switch_IsTexture;
				PolygonOffset = Switch_PolygonOffset;
				TexSubImage1D = Switch_TexSubImage1D;
				TexSubImage2D = Switch_TexSubImage2D;
				
				// Extension: 1.2
				CopyTexSubImage3D = Switch_CopyTexSubImage3D;
				DrawRangeElements = Switch_DrawRangeElements;
				TexImage3D = Switch_TexImage3D;
				TexSubImage3D = Switch_TexSubImage3D;
				
				// Extension: 1.3
				ActiveTexture = Switch_ActiveTexture;
				CompressedTexImage1D = Switch_CompressedTexImage1D;
				CompressedTexImage2D = Switch_CompressedTexImage2D;
				CompressedTexImage3D = Switch_CompressedTexImage3D;
				CompressedTexSubImage1D = Switch_CompressedTexSubImage1D;
				CompressedTexSubImage2D = Switch_CompressedTexSubImage2D;
				CompressedTexSubImage3D = Switch_CompressedTexSubImage3D;
				GetCompressedTexImage = Switch_GetCompressedTexImage;
				SampleCoverage = Switch_SampleCoverage;
				
				// Extension: 1.4
				BlendColor = Switch_BlendColor;
				BlendEquation = Switch_BlendEquation;
				BlendFuncSeparate = Switch_BlendFuncSeparate;
				MultiDrawArrays = Switch_MultiDrawArrays;
				MultiDrawElements = Switch_MultiDrawElements;
				PointParameterf = Switch_PointParameterf;
				PointParameterfv = Switch_PointParameterfv;
				PointParameteri = Switch_PointParameteri;
				PointParameteriv = Switch_PointParameteriv;
				
				// Extension: 1.5
				BeginQuery = Switch_BeginQuery;
				BindBuffer = Switch_BindBuffer;
				BufferData = Switch_BufferData;
				BufferSubData = Switch_BufferSubData;
				DeleteBuffers = Switch_DeleteBuffers;
				DeleteQueries = Switch_DeleteQueries;
				EndQuery = Switch_EndQuery;
				GenBuffers = Switch_GenBuffers;
				GenQueries = Switch_GenQueries;
				GetBufferParameteriv = Switch_GetBufferParameteriv;
				GetBufferPointerv = Switch_GetBufferPointerv;
				GetBufferSubData = Switch_GetBufferSubData;
				GetQueryObjectiv = Switch_GetQueryObjectiv;
				GetQueryObjectuiv = Switch_GetQueryObjectuiv;
				GetQueryiv = Switch_GetQueryiv;
				IsBuffer = Switch_IsBuffer;
				IsQuery = Switch_IsQuery;
				MapBuffer = Switch_MapBuffer;
				UnmapBuffer = Switch_UnmapBuffer;
				
				// Extension: 2.0
				AttachShader = Switch_AttachShader;
				BindAttribLocation = Switch_BindAttribLocation;
				BlendEquationSeparate = Switch_BlendEquationSeparate;
				CompileShader = Switch_CompileShader;
				CreateProgram = Switch_CreateProgram;
				CreateShader = Switch_CreateShader;
				DeleteProgram = Switch_DeleteProgram;
				DeleteShader = Switch_DeleteShader;
				DetachShader = Switch_DetachShader;
				DisableVertexAttribArray = Switch_DisableVertexAttribArray;
				DrawBuffers = Switch_DrawBuffers;
				EnableVertexAttribArray = Switch_EnableVertexAttribArray;
				GetActiveAttrib = Switch_GetActiveAttrib;
				GetActiveUniform = Switch_GetActiveUniform;
				GetAttachedShaders = Switch_GetAttachedShaders;
				GetAttribLocation = Switch_GetAttribLocation;
				GetProgramInfoLog = Switch_GetProgramInfoLog;
				GetProgramiv = Switch_GetProgramiv;
				GetShaderInfoLog = Switch_GetShaderInfoLog;
				GetShaderSource = Switch_GetShaderSource;
				GetShaderiv = Switch_GetShaderiv;
				GetUniformLocation = Switch_GetUniformLocation;
				GetUniformfv = Switch_GetUniformfv;
				GetUniformiv = Switch_GetUniformiv;
				GetVertexAttribPointerv = Switch_GetVertexAttribPointerv;
				GetVertexAttribdv = Switch_GetVertexAttribdv;
				GetVertexAttribfv = Switch_GetVertexAttribfv;
				GetVertexAttribiv = Switch_GetVertexAttribiv;
				IsProgram = Switch_IsProgram;
				IsShader = Switch_IsShader;
				LinkProgram = Switch_LinkProgram;
				ShaderSource = Switch_ShaderSource;
				StencilFuncSeparate = Switch_StencilFuncSeparate;
				StencilMaskSeparate = Switch_StencilMaskSeparate;
				StencilOpSeparate = Switch_StencilOpSeparate;
				Uniform1f = Switch_Uniform1f;
				Uniform1fv = Switch_Uniform1fv;
				Uniform1i = Switch_Uniform1i;
				Uniform1iv = Switch_Uniform1iv;
				Uniform2f = Switch_Uniform2f;
				Uniform2fv = Switch_Uniform2fv;
				Uniform2i = Switch_Uniform2i;
				Uniform2iv = Switch_Uniform2iv;
				Uniform3f = Switch_Uniform3f;
				Uniform3fv = Switch_Uniform3fv;
				Uniform3i = Switch_Uniform3i;
				Uniform3iv = Switch_Uniform3iv;
				Uniform4f = Switch_Uniform4f;
				Uniform4fv = Switch_Uniform4fv;
				Uniform4i = Switch_Uniform4i;
				Uniform4iv = Switch_Uniform4iv;
				UniformMatrix2fv = Switch_UniformMatrix2fv;
				UniformMatrix3fv = Switch_UniformMatrix3fv;
				UniformMatrix4fv = Switch_UniformMatrix4fv;
				UseProgram = Switch_UseProgram;
				ValidateProgram = Switch_ValidateProgram;
				VertexAttrib1d = Switch_VertexAttrib1d;
				VertexAttrib1dv = Switch_VertexAttrib1dv;
				VertexAttrib1f = Switch_VertexAttrib1f;
				VertexAttrib1fv = Switch_VertexAttrib1fv;
				VertexAttrib1s = Switch_VertexAttrib1s;
				VertexAttrib1sv = Switch_VertexAttrib1sv;
				VertexAttrib2d = Switch_VertexAttrib2d;
				VertexAttrib2dv = Switch_VertexAttrib2dv;
				VertexAttrib2f = Switch_VertexAttrib2f;
				VertexAttrib2fv = Switch_VertexAttrib2fv;
				VertexAttrib2s = Switch_VertexAttrib2s;
				VertexAttrib2sv = Switch_VertexAttrib2sv;
				VertexAttrib3d = Switch_VertexAttrib3d;
				VertexAttrib3dv = Switch_VertexAttrib3dv;
				VertexAttrib3f = Switch_VertexAttrib3f;
				VertexAttrib3fv = Switch_VertexAttrib3fv;
				VertexAttrib3s = Switch_VertexAttrib3s;
				VertexAttrib3sv = Switch_VertexAttrib3sv;
				VertexAttrib4Nbv = Switch_VertexAttrib4Nbv;
				VertexAttrib4Niv = Switch_VertexAttrib4Niv;
				VertexAttrib4Nsv = Switch_VertexAttrib4Nsv;
				VertexAttrib4Nub = Switch_VertexAttrib4Nub;
				VertexAttrib4Nubv = Switch_VertexAttrib4Nubv;
				VertexAttrib4Nuiv = Switch_VertexAttrib4Nuiv;
				VertexAttrib4Nusv = Switch_VertexAttrib4Nusv;
				VertexAttrib4bv = Switch_VertexAttrib4bv;
				VertexAttrib4d = Switch_VertexAttrib4d;
				VertexAttrib4dv = Switch_VertexAttrib4dv;
				VertexAttrib4f = Switch_VertexAttrib4f;
				VertexAttrib4fv = Switch_VertexAttrib4fv;
				VertexAttrib4iv = Switch_VertexAttrib4iv;
				VertexAttrib4s = Switch_VertexAttrib4s;
				VertexAttrib4sv = Switch_VertexAttrib4sv;
				VertexAttrib4ubv = Switch_VertexAttrib4ubv;
				VertexAttrib4uiv = Switch_VertexAttrib4uiv;
				VertexAttrib4usv = Switch_VertexAttrib4usv;
				VertexAttribPointer = Switch_VertexAttribPointer;
				
				// Extension: 2.1
				UniformMatrix2x3fv = Switch_UniformMatrix2x3fv;
				UniformMatrix2x4fv = Switch_UniformMatrix2x4fv;
				UniformMatrix3x2fv = Switch_UniformMatrix3x2fv;
				UniformMatrix3x4fv = Switch_UniformMatrix3x4fv;
				UniformMatrix4x2fv = Switch_UniformMatrix4x2fv;
				UniformMatrix4x3fv = Switch_UniformMatrix4x3fv;
				
				// Extension: 3.0
				BeginConditionalRender = Switch_BeginConditionalRender;
				BeginTransformFeedback = Switch_BeginTransformFeedback;
				BindBufferBase = Switch_BindBufferBase;
				BindBufferRange = Switch_BindBufferRange;
				BindFragDataLocation = Switch_BindFragDataLocation;
				BindFramebuffer = Switch_BindFramebuffer;
				BindRenderbuffer = Switch_BindRenderbuffer;
				BindVertexArray = Switch_BindVertexArray;
				BlitFramebuffer = Switch_BlitFramebuffer;
				CheckFramebufferStatus = Switch_CheckFramebufferStatus;
				ClampColor = Switch_ClampColor;
				ClearBufferfi = Switch_ClearBufferfi;
				ClearBufferfv = Switch_ClearBufferfv;
				ClearBufferiv = Switch_ClearBufferiv;
				ClearBufferuiv = Switch_ClearBufferuiv;
				ColorMaski = Switch_ColorMaski;
				DeleteFramebuffers = Switch_DeleteFramebuffers;
				DeleteRenderbuffers = Switch_DeleteRenderbuffers;
				DeleteVertexArrays = Switch_DeleteVertexArrays;
				Disablei = Switch_Disablei;
				Enablei = Switch_Enablei;
				EndConditionalRender = Switch_EndConditionalRender;
				EndTransformFeedback = Switch_EndTransformFeedback;
				FlushMappedBufferRange = Switch_FlushMappedBufferRange;
				FramebufferRenderbuffer = Switch_FramebufferRenderbuffer;
				FramebufferTexture1D = Switch_FramebufferTexture1D;
				FramebufferTexture2D = Switch_FramebufferTexture2D;
				FramebufferTexture3D = Switch_FramebufferTexture3D;
				FramebufferTextureLayer = Switch_FramebufferTextureLayer;
				GenFramebuffers = Switch_GenFramebuffers;
				GenRenderbuffers = Switch_GenRenderbuffers;
				GenVertexArrays = Switch_GenVertexArrays;
				GenerateMipmap = Switch_GenerateMipmap;
				GetBooleani_v = Switch_GetBooleani_v;
				GetFragDataLocation = Switch_GetFragDataLocation;
				GetFramebufferAttachmentParameteriv = Switch_GetFramebufferAttachmentParameteriv;
				GetIntegeri_v = Switch_GetIntegeri_v;
				GetRenderbufferParameteriv = Switch_GetRenderbufferParameteriv;
				GetStringi = Switch_GetStringi;
				GetTexParameterIiv = Switch_GetTexParameterIiv;
				GetTexParameterIuiv = Switch_GetTexParameterIuiv;
				GetTransformFeedbackVarying = Switch_GetTransformFeedbackVarying;
				GetUniformuiv = Switch_GetUniformuiv;
				GetVertexAttribIiv = Switch_GetVertexAttribIiv;
				GetVertexAttribIuiv = Switch_GetVertexAttribIuiv;
				IsEnabledi = Switch_IsEnabledi;
				IsFramebuffer = Switch_IsFramebuffer;
				IsRenderbuffer = Switch_IsRenderbuffer;
				IsVertexArray = Switch_IsVertexArray;
				MapBufferRange = Switch_MapBufferRange;
				RenderbufferStorage = Switch_RenderbufferStorage;
				RenderbufferStorageMultisample = Switch_RenderbufferStorageMultisample;
				TexParameterIiv = Switch_TexParameterIiv;
				TexParameterIuiv = Switch_TexParameterIuiv;
				TransformFeedbackVaryings = Switch_TransformFeedbackVaryings;
				Uniform1ui = Switch_Uniform1ui;
				Uniform1uiv = Switch_Uniform1uiv;
				Uniform2ui = Switch_Uniform2ui;
				Uniform2uiv = Switch_Uniform2uiv;
				Uniform3ui = Switch_Uniform3ui;
				Uniform3uiv = Switch_Uniform3uiv;
				Uniform4ui = Switch_Uniform4ui;
				Uniform4uiv = Switch_Uniform4uiv;
				VertexAttribI1i = Switch_VertexAttribI1i;
				VertexAttribI1iv = Switch_VertexAttribI1iv;
				VertexAttribI1ui = Switch_VertexAttribI1ui;
				VertexAttribI1uiv = Switch_VertexAttribI1uiv;
				VertexAttribI2i = Switch_VertexAttribI2i;
				VertexAttribI2iv = Switch_VertexAttribI2iv;
				VertexAttribI2ui = Switch_VertexAttribI2ui;
				VertexAttribI2uiv = Switch_VertexAttribI2uiv;
				VertexAttribI3i = Switch_VertexAttribI3i;
				VertexAttribI3iv = Switch_VertexAttribI3iv;
				VertexAttribI3ui = Switch_VertexAttribI3ui;
				VertexAttribI3uiv = Switch_VertexAttribI3uiv;
				VertexAttribI4bv = Switch_VertexAttribI4bv;
				VertexAttribI4i = Switch_VertexAttribI4i;
				VertexAttribI4iv = Switch_VertexAttribI4iv;
				VertexAttribI4sv = Switch_VertexAttribI4sv;
				VertexAttribI4ubv = Switch_VertexAttribI4ubv;
				VertexAttribI4ui = Switch_VertexAttribI4ui;
				VertexAttribI4uiv = Switch_VertexAttribI4uiv;
				VertexAttribI4usv = Switch_VertexAttribI4usv;
				VertexAttribIPointer = Switch_VertexAttribIPointer;
				
				// Extension: 3.1
				CopyBufferSubData = Switch_CopyBufferSubData;
				DrawArraysInstanced = Switch_DrawArraysInstanced;
				DrawElementsInstanced = Switch_DrawElementsInstanced;
				GetActiveUniformBlockName = Switch_GetActiveUniformBlockName;
				GetActiveUniformBlockiv = Switch_GetActiveUniformBlockiv;
				GetActiveUniformName = Switch_GetActiveUniformName;
				GetActiveUniformsiv = Switch_GetActiveUniformsiv;
				GetUniformBlockIndex = Switch_GetUniformBlockIndex;
				GetUniformIndices = Switch_GetUniformIndices;
				PrimitiveRestartIndex = Switch_PrimitiveRestartIndex;
				TexBuffer = Switch_TexBuffer;
				UniformBlockBinding = Switch_UniformBlockBinding;
				
				// Extension: 3.2
				ClientWaitSync = Switch_ClientWaitSync;
				DeleteSync = Switch_DeleteSync;
				DrawElementsBaseVertex = Switch_DrawElementsBaseVertex;
				DrawElementsInstancedBaseVertex = Switch_DrawElementsInstancedBaseVertex;
				DrawRangeElementsBaseVertex = Switch_DrawRangeElementsBaseVertex;
				FenceSync = Switch_FenceSync;
				FramebufferTexture = Switch_FramebufferTexture;
				GetBufferParameteri64v = Switch_GetBufferParameteri64v;
				GetInteger64i_v = Switch_GetInteger64i_v;
				GetInteger64v = Switch_GetInteger64v;
				GetMultisamplefv = Switch_GetMultisamplefv;
				GetSynciv = Switch_GetSynciv;
				IsSync = Switch_IsSync;
				MultiDrawElementsBaseVertex = Switch_MultiDrawElementsBaseVertex;
				ProvokingVertex = Switch_ProvokingVertex;
				SampleMaski = Switch_SampleMaski;
				TexImage2DMultisample = Switch_TexImage2DMultisample;
				TexImage3DMultisample = Switch_TexImage3DMultisample;
				WaitSync = Switch_WaitSync;
				
				// Extension: 3.3
				BindFragDataLocationIndexed = Switch_BindFragDataLocationIndexed;
				BindSampler = Switch_BindSampler;
				DeleteSamplers = Switch_DeleteSamplers;
				GenSamplers = Switch_GenSamplers;
				GetFragDataIndex = Switch_GetFragDataIndex;
				GetQueryObjecti64v = Switch_GetQueryObjecti64v;
				GetQueryObjectui64v = Switch_GetQueryObjectui64v;
				GetSamplerParameterIiv = Switch_GetSamplerParameterIiv;
				GetSamplerParameterIuiv = Switch_GetSamplerParameterIuiv;
				GetSamplerParameterfv = Switch_GetSamplerParameterfv;
				GetSamplerParameteriv = Switch_GetSamplerParameteriv;
				IsSampler = Switch_IsSampler;
				QueryCounter = Switch_QueryCounter;
				SamplerParameterIiv = Switch_SamplerParameterIiv;
				SamplerParameterIuiv = Switch_SamplerParameterIuiv;
				SamplerParameterf = Switch_SamplerParameterf;
				SamplerParameterfv = Switch_SamplerParameterfv;
				SamplerParameteri = Switch_SamplerParameteri;
				SamplerParameteriv = Switch_SamplerParameteriv;
				VertexAttribDivisor = Switch_VertexAttribDivisor;
				VertexAttribP1ui = Switch_VertexAttribP1ui;
				VertexAttribP1uiv = Switch_VertexAttribP1uiv;
				VertexAttribP2ui = Switch_VertexAttribP2ui;
				VertexAttribP2uiv = Switch_VertexAttribP2uiv;
				VertexAttribP3ui = Switch_VertexAttribP3ui;
				VertexAttribP3uiv = Switch_VertexAttribP3uiv;
				VertexAttribP4ui = Switch_VertexAttribP4ui;
				VertexAttribP4uiv = Switch_VertexAttribP4uiv;
				
				// Extension: 4.0
				BeginQueryIndexed = Switch_BeginQueryIndexed;
				BindTransformFeedback = Switch_BindTransformFeedback;
				BlendEquationSeparatei = Switch_BlendEquationSeparatei;
				BlendEquationi = Switch_BlendEquationi;
				BlendFuncSeparatei = Switch_BlendFuncSeparatei;
				BlendFunci = Switch_BlendFunci;
				DeleteTransformFeedbacks = Switch_DeleteTransformFeedbacks;
				DrawArraysIndirect = Switch_DrawArraysIndirect;
				DrawElementsIndirect = Switch_DrawElementsIndirect;
				DrawTransformFeedback = Switch_DrawTransformFeedback;
				DrawTransformFeedbackStream = Switch_DrawTransformFeedbackStream;
				EndQueryIndexed = Switch_EndQueryIndexed;
				GenTransformFeedbacks = Switch_GenTransformFeedbacks;
				GetActiveSubroutineName = Switch_GetActiveSubroutineName;
				GetActiveSubroutineUniformName = Switch_GetActiveSubroutineUniformName;
				GetActiveSubroutineUniformiv = Switch_GetActiveSubroutineUniformiv;
				GetProgramStageiv = Switch_GetProgramStageiv;
				GetQueryIndexediv = Switch_GetQueryIndexediv;
				GetSubroutineIndex = Switch_GetSubroutineIndex;
				GetSubroutineUniformLocation = Switch_GetSubroutineUniformLocation;
				GetUniformSubroutineuiv = Switch_GetUniformSubroutineuiv;
				GetUniformdv = Switch_GetUniformdv;
				IsTransformFeedback = Switch_IsTransformFeedback;
				MinSampleShading = Switch_MinSampleShading;
				PatchParameterfv = Switch_PatchParameterfv;
				PatchParameteri = Switch_PatchParameteri;
				PauseTransformFeedback = Switch_PauseTransformFeedback;
				ResumeTransformFeedback = Switch_ResumeTransformFeedback;
				Uniform1d = Switch_Uniform1d;
				Uniform1dv = Switch_Uniform1dv;
				Uniform2d = Switch_Uniform2d;
				Uniform2dv = Switch_Uniform2dv;
				Uniform3d = Switch_Uniform3d;
				Uniform3dv = Switch_Uniform3dv;
				Uniform4d = Switch_Uniform4d;
				Uniform4dv = Switch_Uniform4dv;
				UniformMatrix2dv = Switch_UniformMatrix2dv;
				UniformMatrix2x3dv = Switch_UniformMatrix2x3dv;
				UniformMatrix2x4dv = Switch_UniformMatrix2x4dv;
				UniformMatrix3dv = Switch_UniformMatrix3dv;
				UniformMatrix3x2dv = Switch_UniformMatrix3x2dv;
				UniformMatrix3x4dv = Switch_UniformMatrix3x4dv;
				UniformMatrix4dv = Switch_UniformMatrix4dv;
				UniformMatrix4x2dv = Switch_UniformMatrix4x2dv;
				UniformMatrix4x3dv = Switch_UniformMatrix4x3dv;
				UniformSubroutinesuiv = Switch_UniformSubroutinesuiv;
				
				// Extension: 4.1
				ActiveShaderProgram = Switch_ActiveShaderProgram;
				BindProgramPipeline = Switch_BindProgramPipeline;
				ClearDepthf = Switch_ClearDepthf;
				CreateShaderProgramv = Switch_CreateShaderProgramv;
				DeleteProgramPipelines = Switch_DeleteProgramPipelines;
				DepthRangeArrayv = Switch_DepthRangeArrayv;
				DepthRangeIndexed = Switch_DepthRangeIndexed;
				DepthRangef = Switch_DepthRangef;
				GenProgramPipelines = Switch_GenProgramPipelines;
				GetDoublei_v = Switch_GetDoublei_v;
				GetFloati_v = Switch_GetFloati_v;
				GetProgramBinary = Switch_GetProgramBinary;
				GetProgramPipelineInfoLog = Switch_GetProgramPipelineInfoLog;
				GetProgramPipelineiv = Switch_GetProgramPipelineiv;
				GetShaderPrecisionFormat = Switch_GetShaderPrecisionFormat;
				GetVertexAttribLdv = Switch_GetVertexAttribLdv;
				IsProgramPipeline = Switch_IsProgramPipeline;
				ProgramBinary = Switch_ProgramBinary;
				ProgramParameteri = Switch_ProgramParameteri;
				ProgramUniform1d = Switch_ProgramUniform1d;
				ProgramUniform1dv = Switch_ProgramUniform1dv;
				ProgramUniform1f = Switch_ProgramUniform1f;
				ProgramUniform1fv = Switch_ProgramUniform1fv;
				ProgramUniform1i = Switch_ProgramUniform1i;
				ProgramUniform1iv = Switch_ProgramUniform1iv;
				ProgramUniform1ui = Switch_ProgramUniform1ui;
				ProgramUniform1uiv = Switch_ProgramUniform1uiv;
				ProgramUniform2d = Switch_ProgramUniform2d;
				ProgramUniform2dv = Switch_ProgramUniform2dv;
				ProgramUniform2f = Switch_ProgramUniform2f;
				ProgramUniform2fv = Switch_ProgramUniform2fv;
				ProgramUniform2i = Switch_ProgramUniform2i;
				ProgramUniform2iv = Switch_ProgramUniform2iv;
				ProgramUniform2ui = Switch_ProgramUniform2ui;
				ProgramUniform2uiv = Switch_ProgramUniform2uiv;
				ProgramUniform3d = Switch_ProgramUniform3d;
				ProgramUniform3dv = Switch_ProgramUniform3dv;
				ProgramUniform3f = Switch_ProgramUniform3f;
				ProgramUniform3fv = Switch_ProgramUniform3fv;
				ProgramUniform3i = Switch_ProgramUniform3i;
				ProgramUniform3iv = Switch_ProgramUniform3iv;
				ProgramUniform3ui = Switch_ProgramUniform3ui;
				ProgramUniform3uiv = Switch_ProgramUniform3uiv;
				ProgramUniform4d = Switch_ProgramUniform4d;
				ProgramUniform4dv = Switch_ProgramUniform4dv;
				ProgramUniform4f = Switch_ProgramUniform4f;
				ProgramUniform4fv = Switch_ProgramUniform4fv;
				ProgramUniform4i = Switch_ProgramUniform4i;
				ProgramUniform4iv = Switch_ProgramUniform4iv;
				ProgramUniform4ui = Switch_ProgramUniform4ui;
				ProgramUniform4uiv = Switch_ProgramUniform4uiv;
				ProgramUniformMatrix2dv = Switch_ProgramUniformMatrix2dv;
				ProgramUniformMatrix2fv = Switch_ProgramUniformMatrix2fv;
				ProgramUniformMatrix2x3dv = Switch_ProgramUniformMatrix2x3dv;
				ProgramUniformMatrix2x3fv = Switch_ProgramUniformMatrix2x3fv;
				ProgramUniformMatrix2x4dv = Switch_ProgramUniformMatrix2x4dv;
				ProgramUniformMatrix2x4fv = Switch_ProgramUniformMatrix2x4fv;
				ProgramUniformMatrix3dv = Switch_ProgramUniformMatrix3dv;
				ProgramUniformMatrix3fv = Switch_ProgramUniformMatrix3fv;
				ProgramUniformMatrix3x2dv = Switch_ProgramUniformMatrix3x2dv;
				ProgramUniformMatrix3x2fv = Switch_ProgramUniformMatrix3x2fv;
				ProgramUniformMatrix3x4dv = Switch_ProgramUniformMatrix3x4dv;
				ProgramUniformMatrix3x4fv = Switch_ProgramUniformMatrix3x4fv;
				ProgramUniformMatrix4dv = Switch_ProgramUniformMatrix4dv;
				ProgramUniformMatrix4fv = Switch_ProgramUniformMatrix4fv;
				ProgramUniformMatrix4x2dv = Switch_ProgramUniformMatrix4x2dv;
				ProgramUniformMatrix4x2fv = Switch_ProgramUniformMatrix4x2fv;
				ProgramUniformMatrix4x3dv = Switch_ProgramUniformMatrix4x3dv;
				ProgramUniformMatrix4x3fv = Switch_ProgramUniformMatrix4x3fv;
				ReleaseShaderCompiler = Switch_ReleaseShaderCompiler;
				ScissorArrayv = Switch_ScissorArrayv;
				ScissorIndexed = Switch_ScissorIndexed;
				ScissorIndexedv = Switch_ScissorIndexedv;
				ShaderBinary = Switch_ShaderBinary;
				UseProgramStages = Switch_UseProgramStages;
				ValidateProgramPipeline = Switch_ValidateProgramPipeline;
				VertexAttribL1d = Switch_VertexAttribL1d;
				VertexAttribL1dv = Switch_VertexAttribL1dv;
				VertexAttribL2d = Switch_VertexAttribL2d;
				VertexAttribL2dv = Switch_VertexAttribL2dv;
				VertexAttribL3d = Switch_VertexAttribL3d;
				VertexAttribL3dv = Switch_VertexAttribL3dv;
				VertexAttribL4d = Switch_VertexAttribL4d;
				VertexAttribL4dv = Switch_VertexAttribL4dv;
				VertexAttribLPointer = Switch_VertexAttribLPointer;
				ViewportArrayv = Switch_ViewportArrayv;
				ViewportIndexedf = Switch_ViewportIndexedf;
				ViewportIndexedfv = Switch_ViewportIndexedfv;
				
				// Extension: 4.2
				BindImageTexture = Switch_BindImageTexture;
				DrawArraysInstancedBaseInstance = Switch_DrawArraysInstancedBaseInstance;
				DrawElementsInstancedBaseInstance = Switch_DrawElementsInstancedBaseInstance;
				DrawElementsInstancedBaseVertexBaseInstance = Switch_DrawElementsInstancedBaseVertexBaseInstance;
				DrawTransformFeedbackInstanced = Switch_DrawTransformFeedbackInstanced;
				DrawTransformFeedbackStreamInstanced = Switch_DrawTransformFeedbackStreamInstanced;
				GetActiveAtomicCounterBufferiv = Switch_GetActiveAtomicCounterBufferiv;
				GetInternalformativ = Switch_GetInternalformativ;
				MemoryBarrier = Switch_MemoryBarrier;
				TexStorage1D = Switch_TexStorage1D;
				TexStorage2D = Switch_TexStorage2D;
				TexStorage3D = Switch_TexStorage3D;
				
				// Extension: 4.3
				BindVertexBuffer = Switch_BindVertexBuffer;
				ClearBufferData = Switch_ClearBufferData;
				ClearBufferSubData = Switch_ClearBufferSubData;
				CopyImageSubData = Switch_CopyImageSubData;
				DebugMessageCallback = Switch_DebugMessageCallback;
				DebugMessageControl = Switch_DebugMessageControl;
				DebugMessageInsert = Switch_DebugMessageInsert;
				DispatchCompute = Switch_DispatchCompute;
				DispatchComputeIndirect = Switch_DispatchComputeIndirect;
				FramebufferParameteri = Switch_FramebufferParameteri;
				GetDebugMessageLog = Switch_GetDebugMessageLog;
				GetFramebufferParameteriv = Switch_GetFramebufferParameteriv;
				GetInternalformati64v = Switch_GetInternalformati64v;
				GetObjectLabel = Switch_GetObjectLabel;
				GetObjectPtrLabel = Switch_GetObjectPtrLabel;
				GetProgramInterfaceiv = Switch_GetProgramInterfaceiv;
				GetProgramResourceIndex = Switch_GetProgramResourceIndex;
				GetProgramResourceLocation = Switch_GetProgramResourceLocation;
				GetProgramResourceLocationIndex = Switch_GetProgramResourceLocationIndex;
				GetProgramResourceName = Switch_GetProgramResourceName;
				GetProgramResourceiv = Switch_GetProgramResourceiv;
				InvalidateBufferData = Switch_InvalidateBufferData;
				InvalidateBufferSubData = Switch_InvalidateBufferSubData;
				InvalidateFramebuffer = Switch_InvalidateFramebuffer;
				InvalidateSubFramebuffer = Switch_InvalidateSubFramebuffer;
				InvalidateTexImage = Switch_InvalidateTexImage;
				InvalidateTexSubImage = Switch_InvalidateTexSubImage;
				MultiDrawArraysIndirect = Switch_MultiDrawArraysIndirect;
				MultiDrawElementsIndirect = Switch_MultiDrawElementsIndirect;
				ObjectLabel = Switch_ObjectLabel;
				ObjectPtrLabel = Switch_ObjectPtrLabel;
				PopDebugGroup = Switch_PopDebugGroup;
				PushDebugGroup = Switch_PushDebugGroup;
				ShaderStorageBlockBinding = Switch_ShaderStorageBlockBinding;
				TexBufferRange = Switch_TexBufferRange;
				TexStorage2DMultisample = Switch_TexStorage2DMultisample;
				TexStorage3DMultisample = Switch_TexStorage3DMultisample;
				TextureView = Switch_TextureView;
				VertexAttribBinding = Switch_VertexAttribBinding;
				VertexAttribFormat = Switch_VertexAttribFormat;
				VertexAttribIFormat = Switch_VertexAttribIFormat;
				VertexAttribLFormat = Switch_VertexAttribLFormat;
				VertexBindingDivisor = Switch_VertexBindingDivisor;
				
				// Extension: 4.4
				BindBuffersBase = Switch_BindBuffersBase;
				BindBuffersRange = Switch_BindBuffersRange;
				BindImageTextures = Switch_BindImageTextures;
				BindSamplers = Switch_BindSamplers;
				BindTextures = Switch_BindTextures;
				BindVertexBuffers = Switch_BindVertexBuffers;
				BufferStorage = Switch_BufferStorage;
				ClearTexImage = Switch_ClearTexImage;
				ClearTexSubImage = Switch_ClearTexSubImage;
				
				// Extension: 4.5
				BindTextureUnit = Switch_BindTextureUnit;
				BlitNamedFramebuffer = Switch_BlitNamedFramebuffer;
				CheckNamedFramebufferStatus = Switch_CheckNamedFramebufferStatus;
				ClearNamedBufferData = Switch_ClearNamedBufferData;
				ClearNamedBufferSubData = Switch_ClearNamedBufferSubData;
				ClearNamedFramebufferfi = Switch_ClearNamedFramebufferfi;
				ClearNamedFramebufferfv = Switch_ClearNamedFramebufferfv;
				ClearNamedFramebufferiv = Switch_ClearNamedFramebufferiv;
				ClearNamedFramebufferuiv = Switch_ClearNamedFramebufferuiv;
				ClipControl = Switch_ClipControl;
				CompressedTextureSubImage1D = Switch_CompressedTextureSubImage1D;
				CompressedTextureSubImage2D = Switch_CompressedTextureSubImage2D;
				CompressedTextureSubImage3D = Switch_CompressedTextureSubImage3D;
				CopyNamedBufferSubData = Switch_CopyNamedBufferSubData;
				CopyTextureSubImage1D = Switch_CopyTextureSubImage1D;
				CopyTextureSubImage2D = Switch_CopyTextureSubImage2D;
				CopyTextureSubImage3D = Switch_CopyTextureSubImage3D;
				CreateBuffers = Switch_CreateBuffers;
				CreateFramebuffers = Switch_CreateFramebuffers;
				CreateProgramPipelines = Switch_CreateProgramPipelines;
				CreateQueries = Switch_CreateQueries;
				CreateRenderbuffers = Switch_CreateRenderbuffers;
				CreateSamplers = Switch_CreateSamplers;
				CreateTextures = Switch_CreateTextures;
				CreateTransformFeedbacks = Switch_CreateTransformFeedbacks;
				CreateVertexArrays = Switch_CreateVertexArrays;
				DisableVertexArrayAttrib = Switch_DisableVertexArrayAttrib;
				EnableVertexArrayAttrib = Switch_EnableVertexArrayAttrib;
				FlushMappedNamedBufferRange = Switch_FlushMappedNamedBufferRange;
				GenerateTextureMipmap = Switch_GenerateTextureMipmap;
				GetCompressedTextureImage = Switch_GetCompressedTextureImage;
				GetCompressedTextureSubImage = Switch_GetCompressedTextureSubImage;
				GetGraphicsResetStatus = Switch_GetGraphicsResetStatus;
				GetNamedBufferParameteri64v = Switch_GetNamedBufferParameteri64v;
				GetNamedBufferParameteriv = Switch_GetNamedBufferParameteriv;
				GetNamedBufferPointerv = Switch_GetNamedBufferPointerv;
				GetNamedBufferSubData = Switch_GetNamedBufferSubData;
				GetNamedFramebufferAttachmentParameteriv = Switch_GetNamedFramebufferAttachmentParameteriv;
				GetNamedFramebufferParameteriv = Switch_GetNamedFramebufferParameteriv;
				GetNamedRenderbufferParameteriv = Switch_GetNamedRenderbufferParameteriv;
				GetQueryBufferObjecti64v = Switch_GetQueryBufferObjecti64v;
				GetQueryBufferObjectiv = Switch_GetQueryBufferObjectiv;
				GetQueryBufferObjectui64v = Switch_GetQueryBufferObjectui64v;
				GetQueryBufferObjectuiv = Switch_GetQueryBufferObjectuiv;
				GetTextureImage = Switch_GetTextureImage;
				GetTextureLevelParameterfv = Switch_GetTextureLevelParameterfv;
				GetTextureLevelParameteriv = Switch_GetTextureLevelParameteriv;
				GetTextureParameterIiv = Switch_GetTextureParameterIiv;
				GetTextureParameterIuiv = Switch_GetTextureParameterIuiv;
				GetTextureParameterfv = Switch_GetTextureParameterfv;
				GetTextureParameteriv = Switch_GetTextureParameteriv;
				GetTextureSubImage = Switch_GetTextureSubImage;
				GetTransformFeedbacki64_v = Switch_GetTransformFeedbacki64_v;
				GetTransformFeedbacki_v = Switch_GetTransformFeedbacki_v;
				GetTransformFeedbackiv = Switch_GetTransformFeedbackiv;
				GetVertexArrayIndexed64iv = Switch_GetVertexArrayIndexed64iv;
				GetVertexArrayIndexediv = Switch_GetVertexArrayIndexediv;
				GetVertexArrayiv = Switch_GetVertexArrayiv;
				GetnCompressedTexImage = Switch_GetnCompressedTexImage;
				GetnTexImage = Switch_GetnTexImage;
				GetnUniformdv = Switch_GetnUniformdv;
				GetnUniformfv = Switch_GetnUniformfv;
				GetnUniformiv = Switch_GetnUniformiv;
				GetnUniformuiv = Switch_GetnUniformuiv;
				InvalidateNamedFramebufferData = Switch_InvalidateNamedFramebufferData;
				InvalidateNamedFramebufferSubData = Switch_InvalidateNamedFramebufferSubData;
				MapNamedBuffer = Switch_MapNamedBuffer;
				MapNamedBufferRange = Switch_MapNamedBufferRange;
				MemoryBarrierByRegion = Switch_MemoryBarrierByRegion;
				NamedBufferData = Switch_NamedBufferData;
				NamedBufferStorage = Switch_NamedBufferStorage;
				NamedBufferSubData = Switch_NamedBufferSubData;
				NamedFramebufferDrawBuffer = Switch_NamedFramebufferDrawBuffer;
				NamedFramebufferDrawBuffers = Switch_NamedFramebufferDrawBuffers;
				NamedFramebufferParameteri = Switch_NamedFramebufferParameteri;
				NamedFramebufferReadBuffer = Switch_NamedFramebufferReadBuffer;
				NamedFramebufferRenderbuffer = Switch_NamedFramebufferRenderbuffer;
				NamedFramebufferTexture = Switch_NamedFramebufferTexture;
				NamedFramebufferTextureLayer = Switch_NamedFramebufferTextureLayer;
				NamedRenderbufferStorage = Switch_NamedRenderbufferStorage;
				NamedRenderbufferStorageMultisample = Switch_NamedRenderbufferStorageMultisample;
				ReadnPixels = Switch_ReadnPixels;
				TextureBarrier = Switch_TextureBarrier;
				TextureBuffer = Switch_TextureBuffer;
				TextureBufferRange = Switch_TextureBufferRange;
				TextureParameterIiv = Switch_TextureParameterIiv;
				TextureParameterIuiv = Switch_TextureParameterIuiv;
				TextureParameterf = Switch_TextureParameterf;
				TextureParameterfv = Switch_TextureParameterfv;
				TextureParameteri = Switch_TextureParameteri;
				TextureParameteriv = Switch_TextureParameteriv;
				TextureStorage1D = Switch_TextureStorage1D;
				TextureStorage2D = Switch_TextureStorage2D;
				TextureStorage2DMultisample = Switch_TextureStorage2DMultisample;
				TextureStorage3D = Switch_TextureStorage3D;
				TextureStorage3DMultisample = Switch_TextureStorage3DMultisample;
				TextureSubImage1D = Switch_TextureSubImage1D;
				TextureSubImage2D = Switch_TextureSubImage2D;
				TextureSubImage3D = Switch_TextureSubImage3D;
				TransformFeedbackBufferBase = Switch_TransformFeedbackBufferBase;
				TransformFeedbackBufferRange = Switch_TransformFeedbackBufferRange;
				UnmapNamedBuffer = Switch_UnmapNamedBuffer;
				VertexArrayAttribBinding = Switch_VertexArrayAttribBinding;
				VertexArrayAttribFormat = Switch_VertexArrayAttribFormat;
				VertexArrayAttribIFormat = Switch_VertexArrayAttribIFormat;
				VertexArrayAttribLFormat = Switch_VertexArrayAttribLFormat;
				VertexArrayBindingDivisor = Switch_VertexArrayBindingDivisor;
				VertexArrayElementBuffer = Switch_VertexArrayElementBuffer;
				VertexArrayVertexBuffer = Switch_VertexArrayVertexBuffer;
				VertexArrayVertexBuffers = Switch_VertexArrayVertexBuffers;
				
			}
		};

		InitializeVariables g_initVariables;
	}
	
	namespace sys
	{
		namespace 
		{
			void ClearExtensionVariables()
			{
			}
			
			struct MapEntry
			{
				const char *extName;
				bool *extVariable;
			};
			
			struct MapCompare
			{
				MapCompare(const char *test_) : test(test_) {}
				bool operator()(const MapEntry &other) { return strcmp(test, other.extName) == 0; }
				const char *test;
			};
			
			struct ClearEntry
			{
			  void operator()(MapEntry &entry) { *(entry.extVariable) = false;}
			};
			
			MapEntry g_mappingTable[1]; //This is intensionally left uninitialized. 
			
			void LoadExtByName(const char *extensionName)
			{
				MapEntry *tableEnd = &g_mappingTable[0];
				MapEntry *entry = std::find_if(&g_mappingTable[0], tableEnd, MapCompare(extensionName));
				
				if(entry != tableEnd)
					*(entry->extVariable) = true;
			}
			
			void ProcExtsFromExtList()
			{
				GLint iLoop;
				GLint iNumExtensions = 0;
				GetIntegerv(NUM_EXTENSIONS, &iNumExtensions);
			
				for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
				{
					const char *strExtensionName = (const char *)GetStringi(EXTENSIONS, iLoop);
					LoadExtByName(strExtensionName);
				}
			}
		}
		void CheckExtensions()
		{
			ClearExtensionVariables();
			std::for_each(&g_mappingTable[0], &g_mappingTable[0], ClearEntry());
			
			ProcExtsFromExtList();
		}
		
	}
}
