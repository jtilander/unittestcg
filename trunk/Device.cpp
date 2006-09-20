#include "Precompiled.h"
#include "Device.h"
#include "UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
	#include "DirectX/DxDevice.h"
#endif

#ifdef UNITTESTCG_ENABLE_OPENGL
	#include "OpenGL/OglDevice.h"
#endif

#include "Core.h"

namespace aurora { 

Device::~Device()
{
}

Device* Device::create( const BackendType backendType, const int width, const int height )
{
	Device* result = 0;
	switch( backendType )
	{
	case kBackendOpenGL:
#ifdef UNITTESTCG_ENABLE_OPENGL
		AURORA_DEBUG( "Creating an OpenGL device." );
		result = new OglDevice();
		break;
#endif
		
#ifdef UNITTESTCG_ENABLE_DIRECTX
	case kBackendDirectX:
		AURORA_DEBUG( "Creating a DirectX " << (int)(D3D_SDK_VERSION & ~0x80000000)<< " device." );
		result = new DxDevice();
		break;
#endif
	}
	
	if( !result )
		return 0;
	
	if( !result->initialize(width, height) )
	{
		delete result;
		return 0;
	}
	
	return result;
}

}
