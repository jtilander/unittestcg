#include "Precompiled.h"
#include "StringHelp.h"

namespace aurora { 

std::string replace( const std::string& str, const std::string& oldStr, const std::string& newStr )
{
	std::string::size_type start = 0;
	std::string result;
	
	while( std::string::npos != start && start < str.size() )
	{
		std::string::size_type finish = str.find( oldStr, start );
		result += str.substr(start, finish - start);
		if( finish == std::string::npos )
			break;
		
		result += newStr;
		start = finish + oldStr.size();
	}

	return result;	
}

std::pair< std::string, std::string > split( const std::string& original, const char delimiter )
{
	std::pair< std::string, std::string > result;

	const int pos = (int)original.find(delimiter);
	result.first = original.substr(0,pos);
	if( pos >= 0 )
		result.second = original.substr(pos + 1, std::string::npos);
	return result;
}


}

