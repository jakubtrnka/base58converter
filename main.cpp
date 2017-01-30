#include <iostream>

#include "converter.h"

#define pol( x, y ) ( ( (int) (x)) * 256 + (int)(y) )


int main( int argc, char * argv[] )
{
        int settings(0);
        if ( argc > 1 )
        {
                if ( argv[1][0] != '-' )
                {
                        std::cerr << "Invalid option\n";
                        return 1;
                }
                if ( argv[1][1] == '\0' || argv[1][2] == '\0'  )
                {
                        std::cerr << "Invalid option\n";
                        return 1;
                }
                settings = argv[1][1] * 256 + argv[1][2];
        }


        try {
                switch ( settings )
                {
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
                               std::cerr << "invalid parameter" << std::endl;
                               return 1;
                }

        }
        catch ( const char *s )
        {
                std::cout << s << std::endl;
        }
        return 0;
}
