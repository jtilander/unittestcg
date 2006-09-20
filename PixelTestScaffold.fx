#pragma pack_matrix (row_major)

float4x4 g_testMatrix;
float4x4 g_testMatrixTranspose;
float4 g_testVector;

float4 VsMain( float4 vPos : POSITION ) : POSITION
{
    return vPos;
}

bool runTest();
#include "__thetest.fx"
float4 PsMain() : COLOR0
{ 
	if( runTest() )
		return float4(0,1,0,1);
	else
		return float4(1,0,0,1);	
}

technique Basic
{
    pass pass0
    {          
        #ifdef AURORA_DIRECTX
        VertexShader = compile vs_3_sw VsMain();
        PixelShader  = compile ps_3_sw PsMain();
        #else
        VertexProgram = compile arbvp1 VsMain();
        FragmentProgram = compile arbfp1 PsMain();
        #endif
    }
}


