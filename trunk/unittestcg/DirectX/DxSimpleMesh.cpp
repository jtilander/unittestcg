#include "Precompiled.h"
#include "DxSimpleMesh.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../Core.h"
#include "DxIncludes.h"

namespace aurora { 

DxSimpleMesh::DxSimpleMesh(IDirect3DDevice9& device, IDirect3DVertexDeclaration9* declaration)
	: m_device(device)
	, m_declaration(declaration)
{
}

DxSimpleMesh::~DxSimpleMesh()
{
	if( m_declaration )
		m_declaration->Release();
}


bool DxSimpleMesh::bind() const
{
	HRESULT hr = m_device.SetVertexDeclaration( m_declaration );
	if( FAILED(hr) )
		return false;
	return true;
}

void DxSimpleMesh::submit() const
{
	const float startX = -1.0f;
	const float startY = 1.0f;
	const float endX = 3.0f;
	const float endY = -3.0f;
	const float startU = 0.0f;
	const float startV = 0.0f;
	const float endU = 4.0f;
	const float endV = 4.0f;
	
	const float vertices[] = 
	{
		startX, startY, 0, startU, startV,
		endX, startY, 0, endU, startV,
		endX, endY, 0, endU, endV,
	};

	const HRESULT hr = m_device.DrawPrimitiveUP( D3DPT_TRIANGLELIST, 1, vertices, sizeof(float)*5 );
	AURORA_ASSERT( !FAILED(hr), "Failed to sumbit vertices" );
}

DxSimpleMesh* DxSimpleMesh::create(IDirect3DDevice9& device)
{
	const D3DVERTEXELEMENT9 decl[4] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
		D3DDECL_END()
	};

	IDirect3DVertexDeclaration9* declaration = 0;
	HRESULT hr = device.CreateVertexDeclaration( decl, &declaration );
	if( FAILED( hr ) )
	{
		AURORA_ERROR( "Failed to create vertexdeclaration" );
		return 0;
	}

	return new DxSimpleMesh(device, declaration);
}


}

#endif
