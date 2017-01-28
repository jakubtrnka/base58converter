#include <iostream>
#include <sstream>

#include "ascii2base58.h"
#include "dec2base58.h"
#include "hex2base58.h"
#include "bip39toBase58.h"

enum class base
{
        DEC, HEX, B58, ASC, BIPC, BIPE
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
                                                << "[ -h ] [ -d | -a | -x | -b | -c | -e ] [ -d | -a | -x | -b | -c | -e ]\n"
                                                << "\th: help\n\td: decimal\n\ta: ASCII\n\tx:hexadecimal\n\t"
                                                << "b: base58\n\tc: czech BIP39\n\te: english BIP39\n\t"
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
                                case 'c':
                                        (first ? inp : oup) = base::BIPC;
                                        break;
                                case 'e':
                                        (first ? inp : oup) = base::BIPE;
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

        std::stringstream tmp;
        std::istream * tmpstr = & tmp;
        try
        {
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
                        case base::BIPC:
                                czech2base58 ( std::cin, tmp );
                                break;
                        case base::BIPE:
                                eng2base58 ( std::cin, tmp );
                                break;
                }
        } catch ( const char * s )
        {
                std::cerr << s << std::endl;
                return 1;
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
                case base::BIPC:
                        base58toCzech ( *tmpstr, std::cout );
                        break;
                case base::BIPE:
                        base58toEng ( *tmpstr, std::cout );
                        break;
                case base::B58:
                        std::string ts;
                        *tmpstr >> ts;
                        std::cout << ts << std::endl ;
                        break;

        }
        return 0;
}
