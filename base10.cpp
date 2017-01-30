#include <iostream>
#include <vector>

#include "base10.h"

namespace base10
{
        namespace
        {
                const char * s("0123456789");
        }

        int  findSymbol( const char c ) 
        {
                for ( int i=0; i<10; i++ )
                {
                        if ( s[i] == c )
                                return i;
                }
                return -1;
        }

        void write ( const int index, std::ostream & out )
        {
                if ( index < 0 || index > 10 )
                        throw "base10: error in making output string";
                out << s[ index ];
        }

        void read ( std::istream & ist, std::vector< int > & out )
        {
                while ( ! ist.eof() )
                {
                        char buff[1024];
                        ist.read( buff, 1024 );
                        int imax = ist.gcount();
                        for ( int i=0; i<imax; i++ )
                        {
                                if ( buff[ i ] == '\n' )
                                        return;
                                int tmp = findSymbol( buff[ i ] );
                                if ( tmp != -1 )
                                        out.push_back( tmp );
                                else
                                        throw "base10: incorrect symbol found";
                        }
                }
        }
}
