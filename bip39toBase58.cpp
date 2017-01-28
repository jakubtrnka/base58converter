#include <iostream>
#include <cctype>
#include <vector>

#include "bip39.h"

/*
namespace
{
        const char * bip_english = {
                "abandon", "ability", "able", "about", "above",
                "absent", "absorb", "abstract", "absurd", "abuse",
                "access", "accident", "account", "accuse", "achieve",
                "acid", "acoustic", "acquire", "across", "act",
*/

namespace
{
        const char * b58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

        int bLetter( const char c )
        {
                int i(0);
                while ( b58[i] != '\0' )
                {
                        if ( b58[ i ] == c )
                                return i;
                        i++;
                }
                return -1;
        }
}

/*
void czech2base58( std::istream & ist, std::ostream & ost )
{
        std::vector< int > data;
        char buff[1024];
        data.reserve( 1024);

        int clock(65536);

        do
        {
                if ( --clock == 0 ) throw "Too long input";
                ist.read( buff, 1024 );
                int imax = ist.gcount();
                for ( int i=0; i<imax; i++ )
                {
                        if ( buff[ i ] == '\n' ) break;
                        int tmp = hLetter( buff[ i ] );
                        if ( tmp == -1 ) throw "chyba inputu";
                        data.push_back( tmp );
                }

        } while ( ! ist.eof() );

        if ( data.back() == (int) '\n' )
                data.pop_back();

        std::vector< int > outputnum( (int) (0.6829 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 16;
                        (*oup) += carry;
                        carry = (*oup) / 58;
                        (*oup) %= 58;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 ) inp++;
        while ( inp != outputnum.crend() )
        {
                ost << b58[ *inp ];
                inp++;
        }
        ost << std::endl;
}
*/


void base58toCzech( std::istream & ist, std::ostream & ost )
{
        std::vector< int > data;
        char buff[1024];
        data.reserve( 1024);

        int clock(65536);

        do
        {
                if ( --clock == 0 ) throw "Too long input";
                ist.read( buff, 1024 );
                int imax = ist.gcount();
                for ( int i=0; i<imax; i++ )
                {
                        if ( buff[ i ] ==  '\n' ) break;
                        int tmp = bLetter( buff[ i ] );
                        if ( tmp == -1 ) throw "chyba ve vstupu";
                        data.push_back( tmp );
                }

        } while ( ! ist.eof() );

        std::vector< int > outputnum( (int) (0.5326 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 58;
                        (*oup) += carry;
                        carry = (*oup) / 2048;
                        (*oup) %= 2048;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 )
        {
                if ( inp == outputnum.crend() )
                {
                        ost << bip_czech[0] << std::endl;
			return;
                }
                inp++;
        }
        while ( true )
        {
                ost << bip_czech[ *inp ] ;
                inp++;
                if ( inp == outputnum.crend() )
                        break;
                ost << " ";
        }
        ost << std::endl;
}
