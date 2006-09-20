#include "Precompiled.h"
#include "ShaderTest.h"
#include "Shader.h"

namespace aurora { 

ShaderTest::ShaderTest( Shader* takesOwnership )
	: m_shader( takesOwnership )
{
}

ShaderTest::~ShaderTest()
{
	delete m_shader;
}

Shader& ShaderTest::shader()
{
	return *m_shader;
}

const Shader& ShaderTest::shader() const
{
	return *m_shader;
}


}

