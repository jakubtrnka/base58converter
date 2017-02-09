#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>

void alfa2beta(
                std::istream & ist,
                std::ostream & ost,
                void (* readDigits) ( std::istream & , std::vector< int > & ),
                const short from,
	        const short to,
                const double extensionFactor,
                void (* writeDigits) ( const int, std::ostream & )
              );
void cze2eng ( std::istream & ist, std::ostream & ost );
void eng2b58 ( std::istream & ist, std::ostream & ost );
void b58toEng ( std::istream & ist, std::ostream & ost );
void cze2dec ( std::istream & ist, std::ostream & ost );
void eng2dec ( std::istream & ist, std::ostream & ost );
void dec2cze ( std::istream & ist, std::ostream & ost );
void dec2eng ( std::istream & ist, std::ostream & ost );
void dec2b58 ( std::istream & ist, std::ostream & ost );
void b58toDec ( std::istream & ist, std::ostream & ost );
void ascii2b16 ( std::istream & ist, std::ostream & ost );
void b58toB16 ( std::istream & ist, std::ostream & ost );
void b10toB16 ( std::istream & ist, std::ostream & ost );
void cze2b16 ( std::istream & ist, std::ostream & ost );
void eng2b16 ( std::istream & ist, std::ostream & ost );
void b16toB58 ( std::istream & ist, std::ostream & ost );
void b16toB10 ( std::istream & ist, std::ostream & ost );
void b16toCze ( std::istream & ist, std::ostream & ost );
void b16toEng ( std::istream & ist, std::ostream & ost );
void b16toAscii ( std::istream & ist, std::ostream & ost );
void ascii2eng ( std::istream & ist, std::ostream & ost );
void ascii2cze ( std::istream & ist, std::ostream & ost );
#endif
