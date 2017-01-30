LD=g++
CXX=g++
CXXFLAGS=-std=c++14 -Wall -pedantic -c
LDFLAGS=-Wall -pedantic

converter: main.o baseBIP.o converter.o base10.o base58.o base16.o baseASCII.o
	$(LD) $(LDFLAGS) -o converter main.o baseBIP.o converter.o base10.o base58.o base16.o baseASCII.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

base10.o: base10.cpp base10.h
base16.o: base16.cpp base16.h
base58.o: base58.cpp base58.h
baseASCII.o: baseASCII.cpp
baseBIP.o: baseBIP.cpp baseBIP.h
converter.o: converter.cpp baseBIP.h base10.h base58.h base16.h \
 baseASCII.h converter.h
main.o: main.cpp converter.h
