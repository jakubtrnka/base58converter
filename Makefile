CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++14
LD=g++
LDFLAGS=-Wall -pedantic -std=c++14

converter: main.o ascii2base58.o dec2base58.o hex2base58.o
	$(LD) $(LDFLAGS) main.o ascii2base58.o dec2base58.o hex2base58.o -o converter

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ascii2base58.o: ascii2base58.cpp
dec2base58.o: dec2base58.cpp
hex2base58.o: hex2base58.cpp
main.o: main.cpp ascii2base58.h dec2base58.h hex2base58.h
