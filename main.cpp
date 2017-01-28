#include <iostream>
#include <sstream>

#include "ascii2base58.h"
#include "decimal2base58.h"
#include "hex2base58.h"



enum class base
{
        DEC, HEX, B58, ASC
};

int main(int argc, char * argv[] )
{

        std::stringstream tmp;
        std::istream * tmpstr = & tmp;
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
                                        first ? inp : oup = base::DEC;
                                        break;
                                case 'x':
                                        first ? inp : oup = base::HEX;
                                        break;
                                case 'b':
                                        first ? inp : oup = base::B58;
                                        break;
                                case 'a':
                                        first ? inp : oup = base::ASC;
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
        }
// void ascii2base58( std::istream & ist, std::ostream & ost );
// void base58toAscii( std::istream & ist, std::ostream & ost );
// void decimal2base58( std::istream & ist, std::ostream & ost );
// void base58toDecimal( std::istream & ist, std::ostream & ost );
// void hexa2base58( std::istream & ist, std::ostream & ost );
// void base58toHexadecimal( std::istream & ist, std::ostream & ost );

        switch ( inp )
        {
                case base::HEX:
                        std::cout <<"h\n";
                        hexa2base58 ( std::cin, tmp );
                        break;
                case base::DEC:
                        std::cout <<"d\n";
                        decimal2base58 ( std::cin, tmp );
                        break;
                case base::ASC:
                        std::cout <<"a\n";
                        ascii2base58 ( std::cin, tmp );
                        break;
                case base::B58:
                        std::cout <<"b\n";
                        tmpstr = & std::cin;
                        break;
        }

        switch ( oup )
        {
                case base::HEX:
                        base58toHexadecimal ( *tmpstr, std::cout );
                        break;
                case base::DEC:
                        base58toDecimal ( *tmpstr, std::cout );
                        break;
                case base::ASC:
                        base58toAscii ( *tmpstr, std::cout );
                        break;
                case base::B58:
                        std::string ts;
                        *tmpstr >> ts;
                        std::cout << ts;
                        break;

        }

        return 0;
}
