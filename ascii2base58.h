#include <iostream>
#include <cctype>
#include <vector>

static const char * b58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

void ascii2base58( std::istream & ist, std::ostream & ost )
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
                        data.push_back( (int) buff[ i ] );

        } while ( ! ist.eof() );

        if ( data.back() == (int) '\n' )
                data.pop_back();

        std::vector< int > outputnum( (int) (1.3657 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 256;
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

void base58toAscii( std::istream & ist, std::ostream & ost )
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

        std::vector< int > outputnum( (int) (0.7323 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 58;
                        (*oup) += carry;
                        carry = (*oup) / 256;
                        (*oup) %= 256;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 ) inp++;
        while ( inp != outputnum.crend() )
        {
                ost << (char) *inp;
                inp++;
        }
        ost << std::endl;
}
