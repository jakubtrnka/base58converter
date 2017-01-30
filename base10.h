#ifndef BASE10
#define BASE10

#include <iostream>
#include <vector>

namespace base10
{
        int  findSymbol( const char c );
        void write ( const int index, std::ostream & out );
        void read ( std::istream & ist, std::vector< int > & out );
}
#endif
