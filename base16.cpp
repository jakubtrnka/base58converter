#include <iostream>
#include <vector>

#include "base16.h"

namespace base16
{
        namespace
        {
                const char * s("0123456789abcdef0123456789ABCDEF");
        }
        int  findSymbol( const char c ) 
        {
                for ( int i=0; i< 32; i++ )
                {
                        if ( s[i] == c )
                                return i % 16 ;
                }
                return -1;
        }

        void write( const int index, std::ostream & out )
        {
                if ( index < 0 || index > 15 )
                {
                        throw "base16: error in making output string";
                }
                out << s[ index ];
        }

        void read( std::istream & ist, std::vector< int > & out )
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
                                        throw "base16: incorrect symbol found";
                        }
                }
        }
}
