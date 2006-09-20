#ifndef aurora_unittestcg_shader_h
#define aurora_unittestcg_shader_h

#include <iostream>

namespace aurora { 

class Device;

class Shader
{
	Shader( const Shader& );
	Shader& operator=( const Shader& );
	
public:
	Shader();
	virtual ~Shader();

	virtual bool setVector4( const char* name, const float* values ) = 0;
	virtual bool setMatrix4x4( const char* name, const float* values ) = 0;
	virtual bool setMatrix4x4Transpose( const char* name, const float* values ) = 0;
	
	virtual int begin() const = 0;
	virtual void end() const = 0;
	virtual void beginPass(int i) const = 0;
	virtual void endPass() const = 0;

	virtual void dump( std::ostream& stream ) const = 0;
};

}

#endif
