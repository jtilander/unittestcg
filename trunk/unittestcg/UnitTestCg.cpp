#include "PreCompiled.h"
#include "UnitTestCg.h"


const char* aurora::kFixedTestName = "__thetest.fx";
const char* aurora::kFixedTechniqueName = "Basic";


aurora::BackendType aurora::stringToBackend( const std::string& name )
{
	if( "ogl" == name )
		return kBackendOpenGL;
	if( "dx" == name )
		return kBackendDirectX;
	return kBackendNone;
}

aurora::TestType aurora::stringToProfile( const std::string& name )
{
	if( "ps" == name )
		return kTestTypePixel;
	if( "vs" == name )
		return kTestTypeVertex;
	return kTestTypeNone;
}

