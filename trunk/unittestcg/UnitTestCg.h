#ifndef aurora_unittestcg_unittestcg_h
#define aurora_unittestcg_unittestcg_h

#include <string>

namespace aurora { 

enum ErrorCodes
{
	kSuccess = 0,
	kFailure = 1,
	kParseError = 2,
	kArgumentError = 4,
};

enum TestType
{
	kTestTypeNone = 0,
	kTestTypePixel,
	kTestTypeVertex,
};

enum VerbosityFlag
{
	kVerboseNone = 0,
	kVerboseInfo,
	kVerboseDebug,
};

enum BackendType
{
	kBackendNone = 0,
	kBackendOpenGL,
	kBackendDirectX,
};

extern const char* kFixedTestName;
extern const char* kFixedTechniqueName;

BackendType stringToBackend( const std::string& name );
TestType stringToProfile( const std::string& name );

}

#endif
