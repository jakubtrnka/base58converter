#!/bin/bash
cp dec2base58.cpp base58toAscii.cpp
cp dec2base58.cpp base58toDecimal.cpp
cp dec2base58.cpp decimal2base58.cpp
cp dec2base58.cpp ascii2base58.cpp

g++ -std=c++17 -Wall -pedantic -o base58toAscii    base58toAscii.cpp
g++ -std=c++17 -Wall -pedantic -o base58toDecimal  base58toDecimal.cpp
g++ -std=c++17 -Wall -pedantic -o decimal2base58   decimal2base58.cpp
g++ -std=c++17 -Wall -pedantic -o ascii2base58     ascii2base58.cpp
