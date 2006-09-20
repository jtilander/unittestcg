bool runTest()
{
	float4 a = float4(1,2,3,4);
	float4 r = mul( g_testMatrix, a );
	
	return a - r;
}
