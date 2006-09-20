#ifndef aurora_unittestcg_stringhelp_h
#define aurora_unittestcg_stringhelp_h
#include <string>
#include <utility>

namespace aurora { 

std::string replace( const std::string& str, const std::string& oldStr, const std::string& newStr );
std::pair< std::string, std::string > split( const std::string& original, const char delimiter );

}

#endif
