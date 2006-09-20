#include "Precompiled.h"
#include "OglShader.h"
#ifdef UNITTESTCG_ENABLE_OPENGL
#include "../Core.h"
#include "../UnitTestCg.h"

namespace aurora { namespace {
int countPasses( CGtechnique technique )
{
	int count = 0;
	CGpass pass = cgGetFirstPass( technique );
	while( pass )
	{
		pass = cgGetNextPass(pass);
		count++;
	}
	
	return count;
}

CGpass getPassByIndex(CGtechnique technique, int index)
{
	int count = 0;
	CGpass pass = cgGetFirstPass( technique );
	while( pass && index != count )
	{
		pass = cgGetNextPass(pass);
		count++;
	}
	
	if( index != count )
		return 0;
	return pass;
}

}}


namespace aurora { 

OglShader::OglShader( CGeffect takesOwnership )
	: m_effect(takesOwnership)
	, m_currentTechnique(0)
	, m_currentPass(0)
{
}

OglShader::~OglShader()
{
	cgDestroyEffect(m_effect);	
}

bool OglShader::setVector4( const char* name, const float* values )
{
	const CGparameter parameter = cgGetNamedEffectParameter( m_effect, name );
	if( !parameter )
		return false;
	cgSetParameter4fv( parameter, values );
	return true;
}

bool OglShader::setMatrix4x4( const char* name, const float* values )
{
	const CGparameter parameter = cgGetNamedEffectParameter( m_effect, name );
	if( !parameter )
		return false;

	cgSetMatrixParameterfr( parameter, values );
	return true;
}

bool OglShader::setMatrix4x4Transpose( const char* name, const float* values )
{
	const CGparameter parameter = cgGetNamedEffectParameter( m_effect, name );
	if( !parameter )
		return false;

	cgSetMatrixParameterfc( parameter, values );
	return true;
}

int OglShader::begin() const
{
	m_currentTechnique = cgGetNamedTechnique(m_effect, kFixedTechniqueName);
	return countPasses(m_currentTechnique);
}

void OglShader::end() const
{
	m_currentTechnique = 0;
}

void OglShader::beginPass(int i) const
{
	m_currentPass = getPassByIndex(m_currentTechnique, i);
	cgSetPassState(m_currentPass);
}

void OglShader::endPass() const
{
	cgResetPassState(m_currentPass);
	m_currentPass = 0;
}

void OglShader::dump( std::ostream& stream ) const 
{
	//for( CGtechnique technique = cgGetFirstTechnique(m_effect); 0 != technique; technique = cgGetNextTechnique(technique) )
	CGtechnique technique = cgGetNamedTechnique(m_effect, kFixedTechniqueName);
	cgValidateTechnique(technique);
	if( technique )
	{
		stream << "Technique " << cgGetTechniqueName(technique) << std::endl;
		
		for( CGpass pass = cgGetFirstPass(technique); 0 != pass; pass = cgGetNextPass(pass) )
		{
			stream << "Pass " << cgGetPassName(pass) << std::endl;
			
			CGprogram vertexProgram = cgGetProgramStateAssignmentValue(cgGetNamedStateAssignment(pass, "VertexProgram"));
			CGprogram fragmentProgram = cgGetProgramStateAssignmentValue(cgGetNamedStateAssignment(pass, "FragmentProgram"));
			
			stream << "Profile: " << cgGetProgramString( vertexProgram, CG_PROGRAM_PROFILE ) << std::endl;
			stream << "Entry: " << cgGetProgramString( vertexProgram, CG_PROGRAM_ENTRY ) << std::endl;
			stream << cgGetProgramString( vertexProgram, CG_COMPILED_PROGRAM  ) << std::endl;
						
			stream << "Profile: " << cgGetProgramString( fragmentProgram, CG_PROGRAM_PROFILE ) << std::endl;
			stream << "Entry: " << cgGetProgramString( fragmentProgram, CG_PROGRAM_ENTRY ) << std::endl;
			stream << cgGetProgramString( fragmentProgram, CG_COMPILED_PROGRAM  ) << std::endl;
		}	
	}
}

OglShader* OglShader::create( CGcontext context, const std::string& code, const std::string& name, const char** argv )
{
	CGeffect effect = cgCreateEffect( context, code.c_str(), argv );
	if( !effect )
	{
		AURORA_ERROR( "Failed to compile shader " << name );
		AURORA_ERROR( "CG said:" );
		AURORA_ERROR( cgGetLastListing(context) );
		return 0;
	}
	
	return new OglShader( effect );
}

}

#endif
