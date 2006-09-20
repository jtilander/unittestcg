#ifndef aurora_opengl_ogldevice_h
#define aurora_opengl_ogldevice_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_OPENGL

#include "../Device.h"

namespace aurora { 

class OglDevice : public Device
{
public:
	OglDevice();
	~OglDevice();

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
