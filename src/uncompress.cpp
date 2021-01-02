// uncompress.cpp
// Ashish D'Souza

#include <string>
#include <vector>
#include "bit_reader.hpp"
#include "uncompress.hpp"
#include <iostream>

using namespace std;


void uncompress(string inputFilename, string outputFilename) {
    BitReader bitReader(inputFilename);
    cout << hex << (unsigned short) bitReader.read(7)[0] << dec << endl;
    cout << hex << (unsigned short) bitReader.read(4)[0] << dec << endl;
    cout << hex << (unsigned short) bitReader.read(5)[0] << dec << endl;
}
