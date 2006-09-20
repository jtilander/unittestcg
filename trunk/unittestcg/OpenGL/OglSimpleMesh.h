#ifndef aurora_opengl_oglsimplemesh_h
#define aurora_opengl_oglsimplemesh_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_OPENGL

#include "../Mesh.h"

namespace aurora { 

class OglSimpleMesh : public Mesh
{
public:
	virtual bool bind() const;
	virtual void submit() const;

};

}
#endif
#endif
