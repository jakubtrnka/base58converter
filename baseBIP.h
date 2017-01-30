#ifndef BASEBIP39
#define BASEBIP39

#include <iostream>
#include <vector>

namespace baseBIP39
{
        int  findSymbol( const char *s , const char * where[] ) ;
        void writeCze ( const int index, std::ostream & out );
        void writeEng ( const int index, std::ostream & out );
        void readCze ( std::istream & ist, std::vector< int > & out );
        void readEng ( std::istream & ist, std::vector< int > & out );
}
#endif
