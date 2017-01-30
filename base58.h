#ifndef BASE58
#define BASE58

#include <iostream>
#include <vector>

namespace base58
{
        int  findSymbol( const char c ) ;
        void write( const int index, std::ostream & out );
        void read( std::istream & ist, std::vector< int > & out );
}
#endif
