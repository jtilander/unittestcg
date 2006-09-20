#ifndef aurora_unittestcg_device_h
#define aurora_unittestcg_device_h

#include "DefinesMap.h"
#include "IncludeSet.h"
#include "UnitTestCg.h"
#include <string>

namespace aurora { 

class Shader;
class Mesh;

class Device
{
public:
	virtual ~Device();

private:
	virtual bool initialize( int width, int height ) = 0;

public:
	virtual Shader* createShader( const std::string& code, const std::string& name, const DefinesMap& defines, const IncludeSet& includes ) = 0;
	virtual Mesh* createSimpleMesh() = 0;

	virtual void begin() = 0;
	virtual void end() = 0;
	virtual bool getLastRGBA( float (&rgba)[4] ) const = 0;
	
	static Device* create( BackendType backendType, int width, int height );
};

}


#endif
