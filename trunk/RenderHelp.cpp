#include "Precompiled.h"
#include "RenderHelp.h"
#include "Mesh.h"
#include "Shader.h"
#include "Device.h"

namespace aurora { 

void render( const Mesh& mesh, const Shader& shader )
{
	if( !mesh.bind() )
		return;
	
	const int count = shader.begin();
	for( int i=0; i < count; i++ )
	{
		shader.beginPass(i);
		mesh.submit();
		shader.endPass();
	}
	shader.end();
}

}

