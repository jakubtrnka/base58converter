#include <iostream>
#include <cctype>
#include <vector>

static const char * b58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

static int hLetter( const char c )
{
	const char * hex = "0123456789abcdef0123456789ABCDEF";
        int i(0);
        while ( hex[i] != '\0' )
        {
                if ( b58[ i ] == c )
                        return i % 16;
                i++;
        }
        return -1;
}

void hexa2base58( std::istream & ist, std::ostream & ost )
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
                        data.push_back( (int) buff[ i ] );
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
                        //std::cout << "-----" << i << "<<<<<";
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


static int bLetter( const char c )
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

void base58toHexadecimal( std::istream & ist, std::ostream & ost )
{
        std::vector< int > data;
        char buff[1024];
        data.reserve( 1024);
	const char * hx = "0123456789abcdef";

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

        std::vector< int > outputnum( (int) (1.4645 * data.size()) + 1 , 0 );

        for ( auto inp=data.cbegin(); inp != data.cend(); inp ++ )
        {
                int carry(*inp);
                for ( auto oup=outputnum.begin(); oup != outputnum.end(); oup++ )
                {
                        (*oup) *= 58;
                        (*oup) += carry;
                        carry = (*oup) / 16;
                        (*oup) %= 16;
                }
        }
        auto inp=outputnum.crbegin();
        while ( *inp == 0 ) inp++;
        while ( inp != outputnum.crend() )
        {
                ost << hx[ *inp ] ;
                inp++;
        }
        ost << std::endl;
}
