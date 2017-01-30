#ifndef BASE16
#define BASE16

#include <iostream>
#include <vector>

namespace base16
{
        int  findSymbol( const char c );
        void write( const int index, std::ostream & out );
        void read( std::istream & ist, std::vector< int > & out );
}

#endif
