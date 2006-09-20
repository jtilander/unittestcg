#ifndef aurora_unittestcg_shaderpixeltest_h
#define aurora_unittestcg_shaderpixeltest_h

#include "ShaderTest.h"
#include "DefinesMap.h"
#include "IncludeSet.h"
#include <cstddef>

namespace aurora { 

class Shader;
class Device;

class ShaderPixelTest : public ShaderTest
{
	explicit ShaderPixelTest(Shader* shader);
public:
	~ShaderPixelTest();

	static ShaderPixelTest* create( Device& device, const std::string& filename, const DefinesMap& defines, const IncludeSet& includes );
};

}

#endif
