UnitTestCg 0.1
(c) 2006 Jim Tilander

While I was working on CppUnitLite2 with Noel Llopis we also wrote a lot of shaders.
Seeing that everything else in our engine was unittested except
the shaders and the fact that we spent a lot of time in the shaders it seemed
really silly not to have a unittest framework for the shaders as well. 

But as all good ideas it had to grow a little while. Recently I had more and
more trouble with getting more complex shaders to work for me and I finally
got tired of the printf like debugging I had to do with PIX or just trying
to output different colours in the game. I do have hotloading of the shaders
here in the game, but it's just a pain to get it all to work that way.

So here it is. The very first installment of UnitTestCg. The name is from the
fact that Cg is the language that's beeing parsed for the OpenGL version,
for the DirectX version we're parsing HLSL, the two languages are very close
though so it should in most cases not make any difference.

UnitTestCg uses under the hood:
	- TCLAP
	- DirectX	(Aug2006)
	- OpenGL
	- Cg		(1.5b2)

Writing tests are pretty easy, simple fire up a text editor and enter the following:

--- cut ---
bool runTest()
{
	if( g_testMatrix[1][3] != 7 )
		return false;
	else
		return true;
}
--- cut ---

Then issue the following command:

UnitTestCg -I . -v 1 yourfilename.fx

The output should look something like:

yourfilename.fx: ok.

That means that your test succeeded. There are three predefined variables,

float4x4 g_testMatrix;
float4x4 g_testMatrixTranspose;
float4 g_testVector;

They are prepopulated with the following values:

--- cut ---
	const float testVector[4] = { 0,1,2,3 };
	const float testMatrix[16] =
	{
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15 
	};
--- cut ---

The g_testMatrix is loaded in row major format, i.e. g_testMatrix[3].x == 12 and the transpose is, well
simply transposed.

The install should come with a sample directory with some tests and a sample nant script that I use
to test the distribution. It should give a nice introduction to the possibilities.

How does it work internally? There are two stub HLSL/Cg effects files that internally include your test
and then evaluate them. The internall shaders look like this:

--- cut ---
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

--- cut ---

Cracking open the executable with a simple text editor will reveal the current shader that it loaded.
That's all for now.

Happy TDD-ing,

Jim Tilander
2006, San Francisco



(This was downloaded through http://www.tilander.org/aurora)

