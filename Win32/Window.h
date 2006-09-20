#ifndef aurora_win32_window_h
#define aurora_win32_window_h

#include "Platform.h"

namespace aurora { 

class Window
{
	Window( const Window& );
	Window& operator=( const Window& );
	
	Window( HWND takesOwnership, int width, int height );
public:
	~Window();

	HWND c_ptr();

	const int width;
	const int height;

	static Window* create( int width, int height, const char* caption, const char* windowClass );

private:
	HWND m_handle;
};

}

#endif
