#include <iostream>

#include "converter.h"

#define pol( x, y ) ( ( (int) (x)) * 256 + (int)(y) )

namespace
{
        void printHelp( std::ostream & ost )
        {
               ost <<
                       "\t\t-n   prints newline in the end\n"
                       "\tpossoble conversions:\n\t\t"
                       "-ac  ascii  --------->  czech mnemo  \n\t\t"
                       "-ae  ascii  --------->  english mnemo\n\t\t"
                       "-ax  ascii  --------->  base16       \n\t\t"
                       "-dx  base10   ------->  base16       \n\t\t"
                       "-db  base10   ------->  base58       \n\t\t"
                       "-dc  base10   ------->  czech mnemo  \n\t\t"
                       "-de  base10   ------->  english mnemo\n\t\t"
                       "-xa  base16 --------->  ascii        \n\t\t"
                       "-xd  base16   ------->  base10       \n\t\t"
                       "-xb  base16   ------->  base58       \n\t\t"
                       "-xc  base16   ------->  czech mnemo  \n\t\t"
                       "-xe  base16   ------->  english mnemo\n\t\t"
                       "-bx  base58 --------->  base16       \n\t\t"
                       "-bd  base58   ------->  base10       \n\t\t"
                       "-be  base58   ------->  english mnemo\n\t\t"
                       "-cx  czech mnemo ---->  base16       \n\t\t"
                       "-cd  czech mnemo ---->  base10       \n\t\t"
                       "-ce  czech mnemo ---->  english mnemo\n\t\t"
                       "-ex  english mnemo -->  base16       \n\t\t"
                       "-eb  english mnemo -->  base58       \n\t\t"
                       "-ed  english mnemo -->  base10" << std::endl;
        }

        void convert( const int sett ) throw ( const char * )
        {
                switch ( sett )
                {
                        case pol('a','c'):
                               ascii2cze(std::cin, std::cout );
                               break;
                        case pol('a','e'):
                               ascii2eng(std::cin, std::cout );
                               break;
                        case pol('a','x'):
                               ascii2b16(std::cin, std::cout );
                               break;
                        case pol('d','x'):
                               b10toB16( std::cin, std::cout );
                               break;
                        case pol('x','a'):
                               b16toAscii(std::cin, std::cout );
                               break;
                        case pol('x','d'):
                               b16toB10( std::cin, std::cout );
                               break;
                        case pol('x','b'):
                               b16toB58( std::cin, std::cout );
                               break;
                        case pol('x','c'):
                               b16toCze( std::cin, std::cout );
                               break;
                        case pol('x','e'):
                               b16toEng( std::cin, std::cout );
                               break;
                        case pol('b','x'):
                               b58toB16( std::cin, std::cout );
                               break;
                        case pol('b','d'):
                               b58toDec( std::cin, std::cout );
                               break;
                        case pol('b','e'):
                               b58toEng( std::cin, std::cout );
                               break;
                        case pol('c','x'):
                               cze2b16 ( std::cin, std::cout );
                               break;
                        case pol('c','d'):
                               cze2dec ( std::cin, std::cout );
                               break;
                        case pol('c','e'):
                               cze2eng ( std::cin, std::cout );
                               break;
                        case pol('d','b'):
                               dec2b58 ( std::cin, std::cout );
                               break;
                        case pol('d','c'):
                               dec2cze ( std::cin, std::cout );
                               break;
                        case pol('d','e'):
                               dec2eng ( std::cin, std::cout );
                               break;
                        case pol('e','x'):
                               eng2b16 ( std::cin, std::cout );
                               break;
                        case pol('e','b'):
                               eng2b58 ( std::cin, std::cout );
                               break;
                        case pol('e','d'):
                               eng2dec ( std::cin, std::cout );
                               break;
                        default:
                               throw "Invalid parameter";
                }
        }
}

int main( int argc, char * argv[] )
{
        int settings(0);
        bool newline(false);

        for( int iarg=1; iarg<argc; iarg ++ ) 
        {
                if ( argv[iarg][0] != '-' )
                {
                        std::cerr << "Invalid option\n";
                        return 1;
                }
                else if ( argv[iarg][1] == '\0' )
                {
                        std::cerr << "Invalid option\n";
                        return 1;
                }
                if ( argv[iarg][1] == 'h' && argv[iarg][2] == '\0' )
                {
                        printHelp( std::cout );
                        return 0;
                }
                else if ( argv[iarg][1] == 'n' && argv[iarg][2] == '\0' )
                {
                        newline = true;
                        continue;
                }
                else if ( argv[iarg][2] != '\0' )
                        settings = argv[iarg][1] * 256 + argv[iarg][2];
        }


        try
        {
                convert( settings );
                if ( newline ) std::cout << std::endl;

        }
        catch ( const char *s )
        {
                std::cout << s << std::endl;
        }
        return 0;
}
