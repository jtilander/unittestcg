#ifndef aurora_directx_dxshader_h
#define aurora_directx_dxshader_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../Shader.h"
#include "../DefinesMap.h"
#include <string>

struct ID3DXEffect;
struct ID3DXInclude;
struct IDirect3DDevice9;

namespace aurora { 

class DxShader : public Shader
{
	DxShader( ID3DXEffect* takesOwnership, const std::string& disasm );
public:
	virtual ~DxShader();

	virtual bool setVector4( const char* name, const float* values );
	virtual bool setMatrix4x4( const char* name, const float* values );
	virtual bool setMatrix4x4Transpose( const char* name, const float* values );

	virtual int begin() const;
	virtual void end() const;
	virtual void beginPass(int i) const;
	virtual void endPass() const;

	virtual void dump( std::ostream& stream ) const;

	static Shader* create( IDirect3DDevice9* device, const std::string& code, const std::string& name, ID3DXInclude* includes = 0, const DefinesMap* defines = 0);

private:
	ID3DXEffect* m_effect;
	const std::string m_disasm;
};

}

#endif
#endif
