#ifndef aurora_opengl_oglshader_h
#define aurora_opengl_oglshader_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_OPENGL

#include "../Shader.h"
#include "OglIncludes.h"

namespace aurora { 

class OglShader : public Shader
{
	explicit OglShader( CGeffect takesOwnership );
public:
	virtual ~OglShader();

	virtual bool setVector4( const char* name, const float* values );
	virtual bool setMatrix4x4( const char* name, const float* values );
	virtual bool setMatrix4x4Transpose( const char* name, const float* values );

	virtual int begin() const;
	virtual void end() const;
	virtual void beginPass(int i) const;
	virtual void endPass() const;

	virtual void dump( std::ostream& stream ) const ;


	static OglShader* create( CGcontext context, const std::string& code, const std::string& name, const char** argv );

private:
	CGeffect m_effect;
	mutable CGtechnique m_currentTechnique;
	mutable CGpass m_currentPass;
};

}


#endif
#endif
