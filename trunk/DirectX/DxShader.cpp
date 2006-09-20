#include "Precompiled.h"
#include "DxShader.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../Core.h"
#include "../UnitTestCg.h"
#include "../StringHelp.h"
#include "../Win32/Platform.h"
#include "DxIncludes.h"
#include <vector>

namespace aurora { 

DxShader::DxShader( ID3DXEffect* takesOwnership, const std::string& disasm )
	: m_effect( takesOwnership )
	, m_disasm( disasm )
{
}

DxShader::~DxShader()
{
	if( m_effect )
		m_effect->Release();
}

bool DxShader::setVector4( const char* name, const float* values )
{
	const D3DXHANDLE handle =  m_effect->GetParameterByName( 0, name );
	if( 0 == handle )
		return false;
	
	const HRESULT hr = m_effect->SetVector( handle, reinterpret_cast< const D3DXVECTOR4* >(values) );
	return !FAILED(hr);
}

bool DxShader::setMatrix4x4( const char* name, const float* values )
{
	const D3DXHANDLE handle =  m_effect->GetParameterByName( 0, name );
	if( 0 == handle )
		return false;
	
	const HRESULT hr = m_effect->SetMatrix( handle, reinterpret_cast< const D3DXMATRIX* >(values) );
	return !FAILED(hr);
}

bool DxShader::setMatrix4x4Transpose( const char* name, const float* values )
{
	const D3DXHANDLE handle =  m_effect->GetParameterByName( 0, name );
	if( 0 == handle )
		return false;
	
	const HRESULT hr = m_effect->SetMatrixTranspose( handle, reinterpret_cast< const D3DXMATRIX* >(values) );
	return !FAILED(hr);
}

int DxShader::begin() const
{
	UINT count = 0;
	m_effect->Begin( &count, 0 );
	return int(count);
}

void DxShader::end() const
{
	m_effect->End();
}

void DxShader::beginPass(int i) const
{
	m_effect->BeginPass(i);
}

void DxShader::endPass() const
{
	m_effect->EndPass();
}

void DxShader::dump( std::ostream& stream ) const
{
	stream << m_disasm << std::endl;
}

Shader* DxShader::create( IDirect3DDevice9* device, const std::string& code, const std::string& name, ID3DXInclude* includes, const DefinesMap* defines )
{
	HRESULT hr;
	
	ID3DXEffect* effect = 0;
	ID3DXBuffer* errors = 0;
	
	std::vector< D3DXMACRO > macros;
	if( defines )
	{
		for( DefinesMap::const_iterator it = defines->begin(); it != defines->end(); ++it )
		{
			D3DXMACRO m;
			m.Name = it->first.c_str();
			m.Definition = it->second.c_str();
			macros.push_back( m );
		}
	}
	
	macros.push_back(D3DXMACRO());
	macros.back().Name = "AURORA_DIRECTX";
	macros.back().Definition = 0;
	macros.push_back(D3DXMACRO());
	macros.back().Name = 0;
	macros.back().Definition = 0;
	
	hr = D3DXCreateEffectEx( device,
						code.c_str(),
						(UINT)code.size(),
						&macros[0],
						includes,
						0,
						D3DXSHADER_DEBUG /*| D3DXSHADER_PACKMATRIX_ROWMAJOR*/,
						0,
						&effect,
						&errors );
						
	if( 0 != errors )
	{
		if( 0 == includes )
		{
			AURORA_ERROR( static_cast<const char*>( errors->GetBufferPointer() ) );
		}
		else
		{
			const std::string errorMessage( static_cast<const char*>( errors->GetBufferPointer() ) );
			const std::string fixedMessage = replace( errorMessage, kFixedTestName, name );
			AURORA_ERROR( fixedMessage );
		}
		
		errors->Release();
	}
	if( FAILED( hr ) )
		return 0;

	D3DXHANDLE handle = 0;
	hr = effect->FindNextValidTechnique(0, &handle);
	if( FAILED(hr) )
	{
		AURORA_ERROR( "Failed to find a valid technique: " << name );
		effect->Release();
		return 0;
	}
	
	hr = effect->ValidateTechnique(handle);
	if( FAILED(hr) )
	{
		AURORA_ERROR( "Failed to find a validate technique: " << name );
		effect->Release();
		return 0;
	}
	
	hr = effect->SetTechnique(handle);
	if( FAILED(hr) )
	{
		AURORA_ERROR( "Failed to set technique: " << name );
		effect->Release();
		return 0;
	}

	ID3DXBuffer* disasm = 0;
	hr = D3DXDisassembleEffect( effect, false, &disasm );
	if( FAILED( hr ) )
	{
		AURORA_ERROR( "Failed to disasseble effect: " << name );
		effect->Release();
		return 0;
	}
	
	const std::string disasmString = static_cast<const char*>(disasm->GetBufferPointer());
	disasm->Release();
	
	return new DxShader( effect, disasmString );
}

}

#endif
