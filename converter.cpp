#include <iostream>
#include <vector>

#include "baseBIP.h"
#include "base10.h"
#include "base58.h"
#include "base16.h"
#include "baseASCII.h"
#include "converter.h"

void alfa2beta( std::istream & ist, std::ostream & ost,
             void (* readDigits) ( std::istream & , std::vector< int > & ),
             const short from, const short to, const double extensionFactor,
             void (* writeDigits) ( const int, std::ostream & ) )
{
        std::vector< int > data;
        data.reserve( 1024 );


        //interpret input sequence
        readDigits ( ist, data );

        //container for output sequence
        std::vector< int > outputnum( (int) (extensionFactor * data.size()) + 2 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= from;
                        (*oup) += carry;
                        carry = (*oup) / to;
                        (*oup) %= to;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 )
        {
                if ( inp == outputnum.crend() )
                {
                        writeDigits( 0, ost );
                        return;
                }
                inp++;
        }
        while ( inp != outputnum.crend() )
        {
                writeDigits( * inp, ost );
                inp++;
        }
        ost << std::endl;
}

void cze2eng ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readCze, 2048, 2048, 1, baseBIP39::writeEng );
}

/**********************************************************************/

void eng2b58 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readEng, 2048, 58, 1.8778, base58::write );
}

void b58toEng ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base58::read, 58, 2048, 0.5325, baseBIP39::writeEng );
}

/**********************************************************************/

void cze2dec ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readCze, 2048, 10, 3.3114, base10::write );
}

void eng2dec ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readEng, 2048, 10, 3.3114, base10::write );
}

void dec2cze ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base10::read, 10, 2048, 0.3020, baseBIP39::writeCze );
}

void dec2eng ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base10::read, 10, 2048, 0.3020, baseBIP39::writeEng );
}

/***************************************************************************************/

void dec2b58 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base10::read, 10, 58, 0.5671, base58::write );
}

void b58toDec ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base58::read, 58, 10, 1.7635, base10::write );
}

/***************************************************************************************/

void ascii2b16 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseASCII::read, 256, 16, 2.0001, base16::write );
}

void b58toB16 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base58::read, 58, 16, 1.4645, base16::write );
}

void b10toB16 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base10::read, 10, 16, 0.8305, base16::write );
}

void cze2b16 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readCze, 2048, 16, 2.7501, base16::write );
}

void eng2b16 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, baseBIP39::readEng, 2048, 16, 2.7501, base16::write );
}

/***************************************************************************************/

void b16toB58 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base16::read, 16, 58, 0.6829, base58::write );
}

void b16toB10 ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base16::read, 16, 10, 1.2042, base10::write );
}

void b16toCze ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base16::read, 16, 2048, 0.3637, baseBIP39::writeCze );
}
void b16toEng ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base16::read, 16, 2048, 0.3637, baseBIP39::writeEng );
}

void b16toAscii ( std::istream & ist, std::ostream & ost )
{
        alfa2beta( ist, ost, base16::read, 16, 256, 0.5001, baseASCII::write );
}

