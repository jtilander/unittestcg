#include "PreCompiled.h"
#include "TestRunner.h"
#include "FileInStream.h"
#include "Core.h"
#include "DefinesMap.h"
#include "IncludeSet.h"
#include "StringHelp.h"
#include "UnitTestCgConfig.h"
#include <TCLAP/cmdLine.h>
#include <string>
#include <iostream>

namespace aurora { namespace {

struct Options
{
	Options()
		: verbose(kVerboseNone)
		, backend(kBackendNone)
		, profile(kTestTypeNone)
		, nologo(false)
	{
	}
	
	std::vector< std::string > filenames;
	DefinesMap defines;
	IncludeSet includes;
	VerbosityFlag verbose;
	BackendType backend;
	TestType profile;
	bool nologo;
};

bool parseCommandLine( Options& options, int argc, char* argv[] )
{
	try
	{
		TCLAP::CmdLine cmd("UnitTestCg (c) 2006 Jim Tilander", ' ', "0.1");
		if( argc == 1 )
		{
			std::cout << cmd.getMessage() << std::endl;
			std::cout << "Give the '-h' switch to see the help" << std::endl;
			std::cout << "This version compiled on " << __DATE__ << std::endl;
			
#ifdef UNITTESTCG_ENABLE_OPENGL
			std::cout << "This version have support for OpenGL" << std::endl;
#endif
#ifdef UNITTESTCG_ENABLE_DIRECTX
			std::cout << "This version have support for DirectX" << std::endl;
#endif
			
			
			return false;
		}
		
		std::vector<int> levels;
		levels.push_back(kVerboseNone);
		levels.push_back(kVerboseInfo);
		levels.push_back(kVerboseDebug);
		TCLAP::ValuesConstraint<int> validLevels(levels);
		TCLAP::ValueArg<int> verboseLevel("v","verbose","Set the verbosity level",false,0,&validLevels);
		
		std::vector<std::string> profiles;
		profiles.push_back( "ps" );
		profiles.push_back( "vs" );
		TCLAP::ValuesConstraint<std::string> validProfiles(profiles);
		TCLAP::ValueArg<std::string> profile( "p", "profile", "Chose a profile", false, "ps", &validProfiles );
		
		std::vector<std::string> backends;
		backends.push_back( "ogl" );
		backends.push_back( "dx" );
		TCLAP::ValuesConstraint<std::string> validBackends(backends);
		TCLAP::ValueArg<std::string> backend( "b", "backend", "Choose the backend", false, "ogl", &validBackends );
		
		
		TCLAP::SwitchArg nologo("n", "nologo", "supresses the logo", cmd, false );
		
		TCLAP::MultiArg<std::string> includes( "I", "include", "Include paths", false, "path" );
		TCLAP::MultiArg<std::string> defines( "D", "define", "Defines", false, "symbol" );
		
		TCLAP::UnlabeledMultiArg<std::string> testNames("tests", ".fx test files",true, "filenames");
		
		cmd.add( verboseLevel );
		cmd.add( includes );
		cmd.add( defines );
		cmd.add( backend );
		cmd.add( profile );
		cmd.add( testNames );
		
		cmd.parse( argc, argv );
		
		options.verbose = VerbosityFlag( verboseLevel.getValue() );
		options.filenames = testNames.getValue();
		
		for( int i=0; i < (int)includes.getValue().size(); i++ )
			options.includes.insert( includes.getValue()[i] );
		
		for( int i=0; i < (int)defines.getValue().size(); i++ )
			options.defines.insert( split( defines.getValue()[i], '=' ) );
			
		options.backend = stringToBackend(backend.getValue());
		options.profile = stringToProfile(profile.getValue());
		
		options.nologo = nologo.getValue();
	} 
	catch( TCLAP::ArgException& e )
	{
		std::cerr << "Arg error: " << e.error() << " for arg " << e.argId() << std::endl;
		return false;
	}
	
	return true;
}

bool runTests( const Options& options )
{
	if( kVerboseDebug == options.verbose )
	{
		for( IncludeSet::const_iterator it = options.includes.begin(); it != options.includes.end(); ++it )
			AURORA_DEBUG( "-I " << *it );
		
		for( DefinesMap::const_iterator it = options.defines.begin(); it != options.defines.end(); ++it )
			AURORA_DEBUG( "-D" << it->first << "=" << it->second );
	}

	const int count = (int)options.filenames.size();
	for( int i=0; i < count; i++ )
	{
		const std::string& filename = options.filenames[i];
		TestRunner runner( options.profile, options.verbose, options.backend );

		FileInStream stream;
		if( !stream.open( filename.c_str() ) )
		{
			AURORA_ERROR( "Failed to open: " << filename );
			return false;
		}
	
		if( !runner.runTest( stream, options.defines, options.includes ) )
			return false;
	}
	
	return true;
}
}}

int main( int argc, char* argv[] )
{
	aurora::Options options;
	if( !aurora::parseCommandLine(options, argc, argv) )
		return aurora::kFailure;

	if( !options.nologo )
		std::cout << "UnitTestCg (c) 2006 Jim Tilander" << std::endl;
	
	if( !aurora::runTests(options) )
		return aurora::kFailure;
	return aurora::kSuccess;
}
