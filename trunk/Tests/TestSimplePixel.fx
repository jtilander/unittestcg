// This is the default dummy shader.

bool runTest()
{
#ifdef DEBUG
	return false;
#else
	#include "SimpleInclude.fx"
#endif
}
