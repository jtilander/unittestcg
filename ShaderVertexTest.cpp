#include "Precompiled.h"
#include "ShaderVertexTest.h"
#include "Shader.h"
#include "Device.h"
#include "StringHelp.h"
#include "UnitTestCg.h"

namespace aurora { namespace {
const char g_shaderSource[] = 
{
	#include "VertexTestScaffold.fx.inl"
	0
};
}}

namespace aurora { 

ShaderVertexTest::ShaderVertexTest( Shader* shader )
	: ShaderTest(shader)
{
}

ShaderVertexTest* ShaderVertexTest::create( Device& device, const std::string& filename, const DefinesMap& defines, const IncludeSet& includes )
{
	const std::string fixedName = replace( filename, "\\", "/" );
	const std::string code = replace( g_shaderSource, kFixedTestName, fixedName );
	
	Shader* shader = device.createShader( code, filename, defines, includes );
	if( !shader )
		return 0;
	
	ShaderVertexTest* test = new ShaderVertexTest(shader);
	return test;
}

}

