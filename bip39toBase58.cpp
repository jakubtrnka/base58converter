#include <iostream>
#include <cctype>
#include <vector>
#include <strings.h>

#include "bip39.h"
#include "bip39toBase58.h"


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

        int eWord( const std::string & s )
        {
                const char *cs = s.c_str();
                for ( int i=0; i<2048; i++ )
                {
                        if ( strncasecmp(bip_english[i], cs, 4) == 0 )
                        {
                                return i;
                        }
                }
                return -1;
        }

        int cWord( const std::string & s )
        {
                const char *cs = s.c_str();
                for ( int i=0; i<2048; i++ )
                {
                        if ( strncasecmp(bip_czech[i], cs, 4) == 0 )
                        {
                                return i;
                        }
                }
                return -1;
        }
}

void czech2base58( std::istream & ist, std::ostream & ost )
{
        bip32toBase58( ist, ost, cWord );
}

void eng2base58( std::istream & ist, std::ostream & ost )
{
        bip32toBase58( ist, ost, eWord );
}

void bip32toBase58( std::istream & ist, std::ostream & ost, int (*wordNum) (const std::string & slovo) )
{
        std::vector< int > data;
        data.reserve( 128 );

        int clock(262144);

        while ( ! ist.eof() )
        {
                if ( --clock == 0 ) throw "Too long input";
                std::string tmps;
                ist >> tmps;
                if ( tmps.size() == 0 ) break;
                int tmp = wordNum( tmps );
                if ( tmp == -1 ) throw "incorrect word";
                data.push_back( tmp );
        }

        if ( data.back() == (int) '\n' )
                data.pop_back();

        std::vector< int > outputnum( (int) (1.8778 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 2048;
                        (*oup) += carry;
                        carry = (*oup) / 58;
                        (*oup) %= 58;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 )
        {
                if ( inp == outputnum.crend() )
                {
                        ost << 1;
                        break;
                }
                inp++;
        }
        while ( inp != outputnum.crend() )
        {
                ost << b58[ *inp ];
                inp++;
        }
        ost << std::endl;
}

void base58toCzech( std::istream & ist, std::ostream & ost )
{
        base58toBip32( ist, ost, bip_czech );
}

void base58toEng( std::istream & ist, std::ostream & ost )
{
        base58toBip32( ist, ost, bip_english );
}

void base58toBip32( std::istream & ist, std::ostream & ost, const char * bip_wordlist[] )
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
                        ost << bip_wordlist[0] << std::endl;
                        return;
                }
                inp++;
        }
        while ( true )
        {
                ost << bip_wordlist[ *inp ] ;
                inp++;
                if ( inp == outputnum.crend() )
                        break;
                ost << " ";
        }
        ost << std::endl;
}
