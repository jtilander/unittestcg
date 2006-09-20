#ifndef aurora_unittestcg_mesh_h
#define aurora_unittestcg_mesh_h

namespace aurora { 
class Device;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual bool bind() const = 0;
	virtual void submit() const = 0;
};

}

#endif
