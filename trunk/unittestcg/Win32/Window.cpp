#include "Precompiled.h"
#include "Window.h"
#include "Platform.h"

namespace aurora { namespace {

LRESULT WINAPI messageProcStub( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}
}}

namespace aurora { 

Window::Window(HWND takesOwnership, int width, int height)
	: m_handle(takesOwnership)
	, width(width)
	, height(height)
{
}

Window::~Window()
{
	SendMessage( m_handle, WM_CLOSE, 0, 0 );
	SendMessage( m_handle, WM_QUIT, 0, 0 );
}

HWND Window::c_ptr()
{
	return m_handle;
}

Window* Window::create( int width, int height, const char* caption, const char* windowClass )
{
	const WNDCLASSEX wc = 
	{ 
		sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		messageProcStub, 
		0L, 
		0L, 
		GetModuleHandle(NULL), 
		NULL, 
		NULL, 
		NULL, 
		NULL, 
		windowClass, 
		NULL 
	};

	RegisterClassEx( &wc );

	HWND handle = CreateWindow(	windowClass, 
								caption, 
								WS_OVERLAPPEDWINDOW, 
								100, 
								100, 
								width, 
								height,
								GetDesktopWindow(), 
								NULL, 
								wc.hInstance, 
								NULL );
	
	if( 0 == handle )
		return 0;

	return new Window(handle, width, height);
}

}

