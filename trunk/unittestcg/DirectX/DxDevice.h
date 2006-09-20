#ifndef aurora_directx_dxdevice_h
#define aurora_directx_dxdevice_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../Device.h"

namespace aurora { 

class DxDevice : public Device
{
public:
	DxDevice();
	virtual ~DxDevice();

private:
	virtual bool initialize( int width, int height );
	
public:
	virtual Shader* createShader( const std::string& code, const std::string& name, const DefinesMap& defines, const IncludeSet& includes );
	virtual Mesh* createSimpleMesh();
	
	virtual void begin();
	virtual void end();
	virtual bool getLastRGBA( float (&rgba)[4] ) const;

private:
	struct Pimpl;
	Pimpl& m;
};

}

#endif
#endif
