# Base converter
### Command line utility written in C++ for converting data representation with respect to some particular base
Program reads standard input and writes standard output. Supported are ASCII, decimal and hexadecimal base and bitcoin base58.

Two special bases given by standard [BIP39](https://github.com/bitcoin/bips/blob/master/bip-0039/bip-0039-wordlists.md) are also supported. Digits in these bases are represented each by exactly one of 2048 words (where zero corresponds to the first word). In effect it is representation in base 2048. There are two versions with two different dictionaries: the one with english dictionary and second one with czech.

Bitcoin [base58](https://en.wikipedia.org/wiki/Base58) is representation, where each digit encodes one of 58 symbols (`123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz` where `1` is for zero, `2` for one etc. and `z` for 57). The idea is to make use of every digit and every letter lowercase and uppercase excluding similar characters `0`, `O`, `I` and `l`.

### Basic usage:
`converter [<input enc>] [<outputenc>]`
converter [ -h ]
each `<input enc>` and `<output enc>` can take form of `[ -d | -a | -x | -b | -c | -e ]` options
which sets the input and output encodings. Reading hexadecimal and BIP format is case insensitive. If only one encoding is given, then the output encoding is `base58`. If no encoding is given, default conversion is from hexadecimal to base58.

| Option | Meaning      |
| ----- | :-------     |
| -h    | help         |
| -d    | decimal      |
| -a    | ASCII        |
| -x    | hexadecimal  |
| -b    | base58       |
| -c    | czech BIP39  |
| -e    | english BIP39 |
| default | hexadecimal -> base58  |

