#ifndef aurora_unittestcg_instream_h
#define aurora_unittestcg_instream_h

#include <string>
#include <cstddef>

namespace aurora { 

class InStream
{
	InStream( const InStream& );
	InStream& operator=( const InStream& );
public:
	InStream();
	virtual ~InStream();
	
	virtual std::size_t bytesLeft() const = 0;
	virtual std::size_t read( void* dest, const std::size_t size ) = 0;
	virtual std::string name() const = 0;
	virtual bool error() const = 0;
};

}

#endif
