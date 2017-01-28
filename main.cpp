#include <iostream>
#include <sstream>

#include "ascii2base58.h"
#include "dec2base58.h"
#include "hex2base58.h"



enum class base
{
        DEC, HEX, B58, ASC
};

int main(int argc, char * argv[] )
{

        base inp(base::HEX), oup(base::B58);

        bool first=true;

        for ( int i=1; i<argc; i++ )
        {
                if ( argv[i][0] == '-' )
                {
                        switch ( argv[i][1] )
                        {
                                case 'h':
                                        std::cout << "usage:\t" << argv[0] << " <input enc> <outputenc>\n\t"<< argv[0] << " "
                                                << "[ -h ] [ -d | -a | -x | -b ] [ -d | -a | -x | -b ]\n"
                                                << "\th: help\n\td: decimal\n\ta: ASCII\n\tx:hexadecimal\n\tb: base58\n\t"
                                                << "default: hexadecimal -> base58" << std::endl;
                                        return 0;
                                case 'd':
                                        (first ? inp : oup) = base::DEC;
                                        break;
                                case 'x':
                                        (first ? inp : oup) = base::HEX;
                                        break;
                                case 'b':
                                        (first ? inp : oup) = base::B58;
                                        break;
                                case 'a':
                                        (first ? inp : oup) = base::ASC;
                                        break;
                                default:
                                        std::cerr << "invalid option" << std::endl;
                                        return 1;
                        }
                        if (argv[i][2] != '\0')
                        {
                                std::cerr << "invalid option" << std::endl;
                                return 1;
                        }
                }
                first = false;
        }
// void ascii2base58( std::istream & ist, std::ostream & ost );
// void base58toAscii( std::istream & ist, std::ostream & ost );
// void decimal2base58( std::istream & ist, std::ostream & ost );
// void base58toDecimal( std::istream & ist, std::ostream & ost );
// void hexa2base58( std::istream & ist, std::ostream & ost );
// void base58toHexadecimal( std::istream & ist, std::ostream & ost );

//#define DEBUG

#ifndef DEBUG
        std::stringstream tmp;
        std::istream * tmpstr = & tmp;
        switch ( inp )
        {
                case base::HEX:
                        hex2base58 ( std::cin, tmp );
                        break;
                case base::DEC:
                        dec2base58 ( std::cin, tmp );
                        break;
                case base::ASC:
                        ascii2base58 ( std::cin, tmp );
                        break;
                case base::B58:
                        tmpstr = & std::cin;
                        break;
        }

        switch ( oup )
        {
                case base::HEX:
                        base58toHex ( *tmpstr, std::cout );
                        break;
                case base::DEC:
                        base58toDec ( *tmpstr, std::cout );
                        break;
                case base::ASC:
                        base58toAscii ( *tmpstr, std::cout );
                        break;
                case base::B58:
                        std::string ts;
                        *tmpstr >> ts;
                        std::cout << ts << std::endl ;
                        break;

        }

#else

        try
        {
                base58toAscii ( std::cin, std::cout );
        }
        catch (const char * s)
        {
                std::cout << s << std::endl;
        }

#endif

        return 0;
}
