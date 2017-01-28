#ifndef B39HDR
#define B39HDR

void czech2base58( std::istream & ist, std::ostream & ost );
void eng2base58( std::istream & ist, std::ostream & ost );
void bip32toBase58( std::istream & ist, std::ostream & ost, int (*wordNum) (const std::string & slovo) );
void base58toCzech( std::istream & ist, std::ostream & ost );
void base58toEng( std::istream & ist, std::ostream & ost );
void base58toBip32( std::istream & ist, std::ostream & ost, const char * bip_wordlist[] );

#endif
