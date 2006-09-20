#ifndef aurora_unittestcg_fileinstream_h
#define aurora_unittestcg_fileinstream_h
#include "InStream.h"

namespace aurora { 

class FileInStream : public InStream
{
public:
	FileInStream();
	virtual ~FileInStream();

	bool open( const char* name );

	virtual std::size_t bytesLeft() const;
	virtual std::size_t read( void* dest, const std::size_t size );
	virtual std::string name() const;
	virtual bool error() const;

private:
	struct Pimpl;
	Pimpl& m;
};

}

#endif
