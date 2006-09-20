#ifndef aurora_unittestcg_shadervertextest_h
#define aurora_unittestcg_shadervertextest_h
#include "ShaderTest.h"
#include "DefinesMap.h"
#include "IncludeSet.h"
#include <cstddef>

namespace aurora { 

class Shader;
class Device;

class ShaderVertexTest : public ShaderTest
{
	explicit ShaderVertexTest( Shader* shader );
public:
	static ShaderVertexTest* create( Device& device, const std::string& filename, const DefinesMap& defines, const IncludeSet& includes );
};

}

#endif
