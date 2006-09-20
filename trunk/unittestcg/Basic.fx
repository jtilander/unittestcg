
float4 VsMain( float4 vPos : POSITION ) : POSITION
{
    return vPos;
}

float4 PsMain() : COLOR0
{ 
	return float4(1,0,0.1,1);
}

technique Basic
{
    pass pass0
    {          
        VertexShader = compile vs_3_sw VsMain();
        PixelShader  = compile ps_3_sw PsMain();
    }
}
