#include "Precompiled.h"
#include "OglDevice.h"

#ifdef UNITTESTCG_ENABLE_OPENGL

#include "OglShader.h"
#include "OglSimpleMesh.h"
#include "OglIncludes.h"
#include "../Core.h"
#include "../Win32/Window.h"
#include <vector>

namespace aurora { 

struct OglDevice::Pimpl
{
	Pimpl()
		: width(0)
		, height(0)
		, window(0)
		, glContext(0)
		, cgContext(0)
	{
	}
	
	int width;
	int height;
	Window* window;
	HGLRC glContext;
	CGcontext cgContext;
};

OglDevice::OglDevice()
	: m( *new Pimpl )
{
}

OglDevice::~OglDevice()
{
	if( m.window )
	{
		if( m.cgContext )
			cgDestroyContext( m.cgContext );
		wglMakeCurrent( GetDC(m.window->c_ptr()), 0 );
		if( m.glContext )
			wglDeleteContext( m.glContext );
	}
	
	delete m.window;
	delete &m;
}

bool OglDevice::initialize( int width, int height )
{
	m.width = width;
	m.height = height;
	m.window = Window::create( width, height, "UnitTestCg", "UnitTestCg" );
	if( !m.window )
		return false;

	PIXELFORMATDESCRIPTOR pfd = 
	{ 
		sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
		1,                     			// version number 
		PFD_DRAW_TO_WINDOW |   			// support window 
		PFD_SUPPORT_OPENGL |   			// support OpenGL 
		PFD_DOUBLEBUFFER,      			// double buffered 
		PFD_TYPE_RGBA,         			// RGBA type 
		24,                    			// 24-bit color depth 
		0, 0, 0, 0, 0, 0,      			// color bits ignored 
		8,                     			// no alpha buffer 
		0,                     			// shift bit ignored 
		0,                     			// no accumulation buffer 
		0, 0, 0, 0,            			// accum bits ignored 
		32,                    			// 32-bit z-buffer     
		0,                     			// no stencil buffer 
		0,                     			// no auxiliary buffer 
		PFD_MAIN_PLANE,        			// main layer 
		0,                     			// reserved 
		0, 0, 0                			// layer masks ignored 
	}; 

	const HDC hdc = GetDC(m.window->c_ptr());
	const int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if( pixelFormat == 0 )
	{
		AURORA_ERROR( "Failed to choose a pixel format" );
		return false;
	}

	if( !SetPixelFormat(hdc, pixelFormat, &pfd ) )
	{
		AURORA_ERROR( "Failed to set pixelformat" );
		return false;
	}

	m.glContext = wglCreateContext( hdc );
	if( !m.glContext )
	{	
		AURORA_ERROR( "Failed to create a wgl context" );
		return false;
	}
	
	wglMakeCurrent( hdc, m.glContext );

	m.cgContext = cgCreateContext();
	if( !m.cgContext )
	{
		AURORA_ERROR( "Failed to create a cg context" );
		return false;
	}
		
	//cgSetErrorHandler(myErrorHandlerStub,this);
	cgGLRegisterStates(m.cgContext);
	
	AURORA_DEBUG ("Window: " << width << " x " << height << " x 32" );
	AURORA_DEBUG ("OpenGL Vendor: " << glGetString(GL_VENDOR) );
	AURORA_DEBUG ("OpenGL Renderer: " << glGetString(GL_RENDERER) );
	AURORA_DEBUG ("OpenGL Version: " << glGetString(GL_VERSION) );
	AURORA_DEBUG ("Cg Version: " << cgGetString( CG_VERSION ) );
	//AURORA_DEBUG ("OpenGL Extensions: " << glGetString(GL_EXTENSIONS) );
	
	glViewport( 0, 0, width, height );

	glDisable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );


	return true;
}

Shader* OglDevice::createShader( const std::string& code, const std::string& name, const DefinesMap& defines, const IncludeSet& includes )
{
	std::vector< const char* > argv;
	argv.reserve( defines.size() + includes.size() + 1);
	
	char buffer[AURORA_MAX_PATH + 3];
	for( DefinesMap::const_iterator it = defines.begin(); it != defines.end(); ++it )
	{
		int len = 0;
		if( it->second.empty() )
			len = sprintf( buffer, "-D%s", it->first.c_str() );
		else
			len = sprintf( buffer, "-D%s=%s", it->first.c_str(), it->second.c_str() );
		char* str = new char[ len + 1 ];
		strcpy( str, buffer );
		argv.push_back( str );
	}
	
	for( IncludeSet::const_iterator it = includes.begin(); it != includes.end(); ++it )
	{
		const int len = sprintf( buffer, "-I%s", it->c_str() );
		char* str = new char[ len + 1 ];
		strcpy(str, buffer);
		argv.push_back( str );
	}
	
	{
		const int len = sprintf(buffer, "-DAURORA_OPENGL");	
		char* str = new char[ len + 1 ];
		strcpy(str, buffer);
		argv.push_back(str);
	}
	
	argv.push_back(0);
		
	Shader* shader = OglShader::create( m.cgContext, code, name, &argv[0] );

	for( int i=0; i < (int)argv.size(); i++ )
		delete[] argv[i];

	return shader;
}

Mesh* OglDevice::createSimpleMesh()
{
	return new OglSimpleMesh();
}

void OglDevice::begin()
{
	AURORA_CHECK_GL_ERRORS();

	glClearColor( 0,0,0,1 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void OglDevice::end()
{
	AURORA_CHECK_GL_ERRORS();
	wglSwapLayerBuffers(wglGetCurrentDC(), WGL_SWAP_MAIN_PLANE);
}

bool OglDevice::getLastRGBA( float (&rgba)[4] ) const
{
	glReadPixels( 0, 0, 1, 1, GL_RGBA, GL_FLOAT, rgba );
	return true;
}

}
#endif
