# Base converter
### Command line utility written in C++ for converting data representation with respect to some particular base
Program reads standard input and writes standard output. Supported are ASCII, decimal and hexadecimal base and bitcoin base58.

Two special bases given by standard [BIP39](https://github.com/bitcoin/bips/blob/master/bip-0039/bip-0039-wordlists.md) are also supported. Digits in these bases are represented each by exactly one of 2048 words (where zero corresponds to the first word). In effect it is representation in base 2048. There are two versions with two different dictionaries: the one with english dictionary and second one with czech.

Bitcoin [base58](https://en.wikipedia.org/wiki/Base58) is representation, where each digit encodes one of 58 symbols (`123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz` where `1` is for zero, `2` for one etc. and `z` for 57). The idea is to make use of every digit and every letter lowercase and uppercase excluding similar characters `0`, `O`, `I` and `l`.

### Basic usage:
`converter -ij`

`converter  -h `


Where `ij` are input/output parameters.


| -ij  | input enc.    | output enc      |
| -----| :------------ |:--------------- |
| -ax  | ascii         |  base16         |
| -dx  | base10        |  base16         |
| -db  | base10        |  base58         |
| -dc  | base10        |  czech mnemo    |
| -de  | base10        |  english mnemo  |
| -xa  | base16        |  ascii          |
| -xd  | base16        |  base10         |
| -xb  | base16        |  base58         |
| -xc  | base16        |  czech mnemo    |
| -xe  | base16        |  english mnemo  |
| -bx  | base58        |  base16         |
| -bd  | base58        |  base10         |
| -be  | base58        |  english mnemo  |
| -cx  | czech mnemo   |  base16         |
| -cd  | czech mnemo   |  base10         |
| -ce  | czech mnemo   |  english mnemo  |
| -ex  | english mnemo |  base16         |
| -eb  | english mnemo |  base58         |
| -ed  | english mnemo |  base10         |
| -h   | help          |  none           |
