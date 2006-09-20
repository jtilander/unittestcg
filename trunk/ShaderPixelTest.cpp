#include "Precompiled.h"
#include "ShaderPixelTest.h"
#include "Shader.h"
#include "Device.h"
#include "StringHelp.h"
#include "UnitTestCg.h"

namespace aurora { namespace {
const char g_shaderSource[] = 
{
	#include "PixelTestScaffold.fx.inl"
	0
};
}}

namespace aurora { 

ShaderPixelTest::ShaderPixelTest(Shader* shader)
	: ShaderTest(shader)
{
}

ShaderPixelTest::~ShaderPixelTest()
{
}

ShaderPixelTest* ShaderPixelTest::create( Device& device, const std::string& filename, const DefinesMap& defines, const IncludeSet& includes )
{
	const std::string fixedName = replace( filename, "\\", "/" );
	const std::string code = replace( g_shaderSource, kFixedTestName, fixedName );
	
	Shader* shader = device.createShader(code, filename, defines, includes);
	if( !shader )
		return 0;
	
	ShaderPixelTest* test = new ShaderPixelTest(shader);
	return test;
}

}

