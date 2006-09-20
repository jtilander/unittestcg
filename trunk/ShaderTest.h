#ifndef aurora_unittestcg_shadertest_h
#define aurora_unittestcg_shadertest_h

namespace aurora { 

class Shader;

class ShaderTest
{
	ShaderTest( const ShaderTest& );
	ShaderTest& operator=( const ShaderTest& );
	
protected:
	explicit ShaderTest( Shader* takesOwnership );

public:
	virtual ~ShaderTest() = 0;

	virtual Shader& shader();
	virtual const Shader& shader() const;

private:
	Shader* m_shader;
};

}

#endif
