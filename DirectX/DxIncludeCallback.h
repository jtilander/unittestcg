#ifndef aurora_unittestcg_dxincludecallback_h
#define aurora_unittestcg_dxincludecallback_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "DxIncludes.h"
#include "../IncludeSet.h"

namespace aurora { 

class DxIncludeCallback : public ID3DXInclude
{
public:
	explicit DxIncludeCallback( const IncludeSet& includePaths );

	virtual HRESULT STDMETHODCALLTYPE Open( D3DXINCLUDE_TYPE /*IncludeType*/, LPCSTR pFileName, LPCVOID /*pParentData*/, LPCVOID * ppData, UINT * pBytes);
	virtual HRESULT STDMETHODCALLTYPE Close(LPCVOID /*pData*/);

private:
	const IncludeSet m_includePaths;
};

}

#endif
#endif
