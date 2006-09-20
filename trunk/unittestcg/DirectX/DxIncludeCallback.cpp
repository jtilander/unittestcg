#include "Precompiled.h"
#include "DxIncludeCallback.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../FileInStream.h"
#include <cstring>

namespace aurora { 

DxIncludeCallback::DxIncludeCallback( const IncludeSet& includePaths )
	: m_includePaths(includePaths)
{
}

HRESULT STDMETHODCALLTYPE DxIncludeCallback::Open( D3DXINCLUDE_TYPE /*IncludeType*/, LPCSTR pFileName, LPCVOID /*pParentData*/, LPCVOID * ppData, UINT * pBytes)
{
	for( IncludeSet::const_iterator it = m_includePaths.begin(); it != m_includePaths.end(); ++it )
	{
		FileInStream stream;
		
		char buffer[512];
		std::sprintf( buffer, "%s\\%s", it->c_str(), pFileName );
		
		if( !stream.open( buffer ) )
			continue;
		
		const int len = (int)stream.bytesLeft();
		char** dst = (char**)ppData;
		*dst = new char[ len + 1 ];
		stream.read( *dst, len );
		(*dst)[len] = 0;
		*pBytes = len;
		
		return S_OK;
	}
		
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE DxIncludeCallback::Close(LPCVOID pData)
{
	const char* pointer = (const char*)pData;
	delete[] pointer;
	
	return S_OK;
}

}

#endif
