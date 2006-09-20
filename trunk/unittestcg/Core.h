#ifndef __aurora_core_h__
#define __aurora_core_h__

#include <iostream>

#ifdef _DEBUG
	#define AURORA_FILE_LINE_STREAM __FILE__ << "(" << __LINE__ << "):"
#else
	#define AURORA_FILE_LINE_STREAM ""
#endif


#define AURORA_ERROR( arg )\
	do\
	{\
		std::cerr << AURORA_FILE_LINE_STREAM << arg << std::endl;\
	} while( false )

#define AURORA_WARNING( arg )\
	do\
	{\
		std::cout << AURORA_FILE_LINE_STREAM << arg << std::endl;\
	} while( false )

#define AURORA_INFO( arg )\
	do\
	{\
		std::cout << AURORA_FILE_LINE_STREAM << arg << std::endl;\
	} while( false )
	
	
#ifdef _DEBUG	
#define AURORA_DEBUG( arg )\
	do\
	{\
		std::cout << AURORA_FILE_LINE_STREAM << arg << std::endl;\
	} while( false )
#else
	#define AURORA_DEBUG( arg ) do { } while( false )
#endif


#define AURORA_BREAK() do { __asm { int 3 }; } while(false)
#define AURORA_ASSERT( expr, message )\
	do\
	{\
		if( !(expr) )\
		{\
			AURORA_ERROR( message );\
			AURORA_BREAK();\
		}\
	} while( false )



#define AURORA_MAX_PATH 512


#endif
