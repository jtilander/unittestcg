#include "Precompiled.h"
#include "DxDevice.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "DxShader.h"
#include "DxSimpleMesh.h"
#include "DxIncludeCallback.h"
#include "../Core.h"
#include "../Win32/Platform.h"
#include "../Win32/Window.h"
#include "DxIncludes.h"

namespace aurora { 

struct DxDevice::Pimpl
{
	Pimpl()
		: window(0)
		, d3d(0)
		, device(0)
		, renderTarget(0)
		, systemTexture(0)
	{
	}
	
	Window* window;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DTEXTURE9 renderTarget;
	LPDIRECT3DTEXTURE9 systemTexture;
};

DxDevice::DxDevice()
	: m( *new Pimpl )
{
}

DxDevice::~DxDevice()
{
	if( m.systemTexture )
		m.systemTexture->Release();
		
	if( m.renderTarget )
		m.renderTarget->Release();

	if( m.device )
		m.device->Release();
	
	if( m.d3d )
		m.d3d->Release();

	delete m.window;
	delete &m;
}

bool DxDevice::initialize( int width, int height )
{
	m.window = Window::create( width, height, "UnitTestCg", "UnitTestCg" );
	if( 0 == m.window )
	{
		AURORA_ERROR( "Failed to create window" );
		return false;
	}
	
	m.d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( 0 == m.d3d )
	{
		AURORA_ERROR( "Failed to create D3D object for SDK " << (int)(D3D_SDK_VERSION & ~0x80000000) );
		return false;
	}
	
    D3DPRESENT_PARAMETERS d3dpp = {0}; 
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    HRESULT hr = m.d3d->CreateDevice(	D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_REF, 
										m.window->c_ptr(),
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, 
										&m.device );

	if( FAILED(hr) )
	{
		AURORA_ERROR( "Failed to create software device" );
		return false;
	}

	hr = D3DXCreateTexture(m.device, m.window->width, m.window->height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m.renderTarget );
	if( FAILED( hr ) )
	{
		AURORA_ERROR( "Failed to create render target texture" );
		return false;
	}
	
	hr = D3DXCreateTexture(m.device, m.window->width, m.window->height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m.systemTexture );
	if( FAILED( hr ) )
	{
		AURORA_ERROR( "Failed to create system memory texture" );
		return false;
	}
	
	return true;
}

Shader* DxDevice::createShader( const std::string& code, const std::string& name, const DefinesMap& defines, const IncludeSet& includes )
{
	// TODO: Make sure that we modify the code snippet to make the forward include.
	DxIncludeCallback includer(includes);
	return DxShader::create(m.device, code, name, &includer, &defines);
}

Mesh* DxDevice::createSimpleMesh()
{
	return DxSimpleMesh::create(*m.device);
}

void DxDevice::begin()
{
	HRESULT hr;
	
	IDirect3DSurface9* surface = 0;
	m.renderTarget->GetSurfaceLevel(0, &surface);
	
	D3DVIEWPORT9 viewPort;
	viewPort.X = 0;
	viewPort.Y = 0;
	viewPort.Width = m.window->width;
	viewPort.Height = m.window->height;
	viewPort.MinZ = 0;
	viewPort.MaxZ = 1.0f;
	hr = m.device->SetViewport(&viewPort);
	hr = m.device->SetRenderTarget(0, surface);
	
	m.device->BeginScene();
	m.device->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255,0,0,0), 1.0f, 0 );
}

void DxDevice::end()
{
	m.device->EndScene();
	m.device->Present(0,0,0,0);
}

bool DxDevice::getLastRGBA( float (&rgba)[4] ) const
{
	IDirect3DSurface9* renderTargetSurface = 0;
	m.renderTarget->GetSurfaceLevel(0, &renderTargetSurface);

	IDirect3DSurface9* systemTextureSurface = 0;
	m.systemTexture->GetSurfaceLevel(0, &systemTextureSurface);
	
	HRESULT hr;
	hr = m.device->GetRenderTargetData( renderTargetSurface, systemTextureSurface );
	if( FAILED( hr ) )
		return false;
		
	D3DLOCKED_RECT rect;
	hr = systemTextureSurface->LockRect(&rect, 0, D3DLOCK_READONLY);
	if( FAILED(hr) )
		return false;
	
	rgba[0] = float(((unsigned char*)rect.pBits)[2]) / 0xff;
	rgba[1] = float(((unsigned char*)rect.pBits)[1]) / 0xff;
	rgba[2] = float(((unsigned char*)rect.pBits)[0]) / 0xff;
	rgba[3] = float(((unsigned char*)rect.pBits)[3]) / 0xff;
	
	systemTextureSurface->UnlockRect();
	
	// DEBUG: Save the system texture out to file.
	// hr = D3DXSaveTextureToFile( "test.png", D3DXIFF_PNG, m.systemTexture, 0 );
	return true;
}

}
#endif
