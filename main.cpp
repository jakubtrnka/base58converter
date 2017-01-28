#include <iostream>

#include "ascii2base58.h"
#include "decimal2base58.h"
#include "hex2base58.h"


// void ascii2base58( std::istream & ist, std::ostream & ost );
// void base58toAscii( std::istream & ist, std::ostream & ost );
// void decimal2base58( std::istream & ist, std::ostream & ost );
// void base58toDecimal( std::istream & ist, std::ostream & ost );
// void hexa2base58( std::istream & ist, std::ostream & ost );
// void base58toHexadecimal( std::istream & ist, std::ostream & ost );

int main()
{

	ascii2base58( std::cin, std::cout );
	return 0;
}
