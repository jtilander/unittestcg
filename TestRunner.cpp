#include "Precompiled.h"
#include "TestRunner.h"
#include "Device.h"
#include "Shader.h"
#include "ShaderPixelTest.h"
#include "ShaderVertexTest.h"
#include "RenderHelp.h"
#include "Core.h"
#include "InStream.h"
#include "Mesh.h"

#include <vector>
#include <cmath>

namespace aurora { 

TestRunner::TestRunner( const TestType testType, const VerbosityFlag verbosity, const BackendType backend )
	: m_testType(testType)
	, m_verbosity(verbosity)
	, m_backendType(backend)
{
}

TestRunner::~TestRunner()
{
}

bool TestRunner::runTest( InStream& testSource, const DefinesMap& defines, const IncludeSet& includes )
{
	Device* device = Device::create( m_backendType, 200, 200 );
	if( !device )
	{
		AURORA_ERROR( testSource.name() << ": Fatal error, failed to create device." );
		return false;
	}
	
	ShaderTest* test = 0;
	
	switch( m_testType )
	{
	case kTestTypePixel:
		test = ShaderPixelTest::create( *device, testSource.name(), defines, includes );
		break;
	case kTestTypeVertex:
		test = ShaderVertexTest::create( *device, testSource.name(), defines, includes );
		break;
	}
			
	if( !test )
	{
		AURORA_ERROR( testSource.name() << ": Failed to create the test shader."  );
		return false;
	}
			
	// TODO: Move this to somewhere where we can get values from the command line.
	const float testVector[4] = { 0,1,2,3 };
	const float testMatrix[16] =
	{
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15 
	};

	if( !test->shader().setVector4( "g_testVector", testVector ) )
	{
		AURORA_ERROR( "Failed to set testvector" );
		return false;
	}
	
	if( !test->shader().setMatrix4x4( "g_testMatrix", testMatrix ) )
	{
		AURORA_ERROR( "Failed to set testmatrix" );
		return false;
	}

	if( !test->shader().setMatrix4x4( "g_testMatrixTranspose", testMatrix ) )
	{
		AURORA_ERROR( "Failed to set transpose testmatrix" );
		return false;
	}
				
	bool result = false;
	do
	{
		Mesh* mesh = device->createSimpleMesh();

		if( m_verbosity >= kVerboseDebug )
			test->shader().dump(std::cout);

		device->begin();
		render( *mesh, test->shader() );
		device->end();

		float rgba[4] = {0};
		if( !device->getLastRGBA( rgba ) )
			break;

		
		const float tolerance = 0.0001f;
		if( std::fabsf( 1.0f - rgba[1] ) > tolerance || std::fabsf(rgba[0]) > tolerance || std::fabsf(rgba[2]) > tolerance || std::fabsf( 1.0f - rgba[3] ) )
		{
			AURORA_ERROR( testSource.name() << ": error: Test failed. Color was [" << rgba[0] << ", " << rgba[1] << ", " << rgba[2] << ", " << rgba[3] << "]" );
			break;
		}

		result = true;
		
		if( m_verbosity >= kVerboseInfo )
			AURORA_INFO( testSource.name() << ": ok." );
		
		delete mesh;
	} while( false );
	
	delete test;
	delete device;
	return result;
}

}
