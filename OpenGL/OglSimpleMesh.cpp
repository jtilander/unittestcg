#include "Precompiled.h"
#include "OglSimpleMesh.h"
#ifdef UNITTESTCG_ENABLE_OPENGL
#include "OglIncludes.h"

namespace aurora { 

bool OglSimpleMesh::bind() const
{
	return true;
}

void OglSimpleMesh::submit() const
{
	glBegin( GL_TRIANGLES );
		glVertex3f(-1,-1,0);
		glVertex3f(-1,3,0);
		glVertex3f(3,-1,0);
	glEnd();
}

}

#endif
