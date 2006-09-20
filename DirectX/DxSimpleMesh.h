#ifndef aurora_directx_dxsimplemesh_h
#define aurora_directx_dxsimplemesh_h

#include "../UnitTestCgConfig.h"
#ifdef UNITTESTCG_ENABLE_DIRECTX
#include "../Mesh.h"

struct IDirect3DDevice9;
struct IDirect3DVertexDeclaration9;

namespace aurora { 

class DxSimpleMesh : public Mesh
{
	DxSimpleMesh(IDirect3DDevice9& device, IDirect3DVertexDeclaration9* declaration);
public:
	~DxSimpleMesh();

	virtual bool bind() const;
	virtual void submit() const;

	static DxSimpleMesh* create(IDirect3DDevice9& device);

private:
	IDirect3DDevice9& m_device;
	IDirect3DVertexDeclaration9* m_declaration;
};

}

#endif
#endif
