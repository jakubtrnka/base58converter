#ifndef BASEASCII
#define BASEASCII

#include <iostream>
#include <vector>

namespace baseASCII
{
        void write( const int index, std::ostream & out );
        void read( std::istream & ist, std::vector< int > & out );
}
#endif
