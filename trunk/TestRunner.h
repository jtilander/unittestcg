#ifndef aurora_unittestcg_testrunner_h
#define aurora_unittestcg_testrunner_h

#include "UnitTestCg.h"
#include "DefinesMap.h"
#include "IncludeSet.h"

namespace aurora { 

class InStream;

class TestRunner
{
	TestRunner( const TestRunner& );
	TestRunner& operator=( const TestRunner& );
public:
	TestRunner( const TestType testType, const VerbosityFlag verbosity, const BackendType backend );
	~TestRunner();
	
	bool runTest( InStream& testSource, const DefinesMap& defines, const IncludeSet& includes );

private:
	const TestType m_testType;
	const VerbosityFlag m_verbosity;
	const BackendType m_backendType;
};

}

#endif
