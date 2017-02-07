#include <iostream>
#include <vector>

namespace baseASCII
{
        void write( const int index, std::ostream & out )
        {
                if ( index < 0 || index > 255 )
                        throw "baseASCII: error in making output string";
                out << (unsigned char) index;
        }

        void read( std::istream & ist, std::vector< int > & out )
        {
                while ( ! ist.eof() )
                {
                        unsigned char buff[1024];
                        ist.read( (char * ) buff, 1024 );
                        int imax = ist.gcount();
                        if ( ( buff[ imax - 1 ] == '\n' ) && ist.eof() )
                                imax -- ;
                        for ( int i=0; i<imax; i++ )
                        {
                                out.push_back( (int) buff[ i ] );
                        }
                }
        }
}
