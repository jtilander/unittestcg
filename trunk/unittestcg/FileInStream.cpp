#include "Precompiled.h"
#include "FileInStream.h"
#include <cstdio>
namespace aurora { 

struct FileInStream::Pimpl
{
	Pimpl()
		: file(0)
		, name("<none>")
		, bytesLeft(0)
	{
	}
	
	std::FILE* file;
	std::string name;
	std::size_t bytesLeft;
};

FileInStream::FileInStream()
	: m( *new Pimpl )
{
}

FileInStream::~FileInStream()
{
	if( m.file )
		std::fclose( m.file );

	delete &m;
}

bool FileInStream::open( const char* name )
{
	m.file = std::fopen(name, "rb");
	if( 0 == m.file )
		return false;
	
	m.name = name;
	std::fseek( m.file, 0, SEEK_END );
	m.bytesLeft = std::ftell(m.file);
	std::fseek( m.file, 0, SEEK_SET );
	std::clearerr(m.file);
	return true;
}

std::size_t FileInStream::bytesLeft() const
{
	return m.bytesLeft;
}

std::size_t FileInStream::read( void* dest, const std::size_t size )
{
	int bytesRead = 0;
	int bytesLeft = (int)size;
	while( bytesLeft > 0 && !error() )
	{
		const int eaten = (int)std::fread( (char*)dest + bytesRead, 1, bytesLeft, m.file );
		bytesRead += eaten;
		bytesLeft -= eaten;
	}
	
	m.bytesLeft -= bytesRead;
	return bytesRead;
}

std::string FileInStream::name() const
{
	return m.name;
}

bool FileInStream::error() const
{
	return 0 != std::ferror(m.file);
}

}

