// bit_reader.cpp
// Ashish D'Souza

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include "bit_reader.hpp"
#include <iostream>

using namespace std;


BitReader::BitReader(const string filename) {
    open(filename);
}

void BitReader::open(const string filename) {
    this->filename = filename;
    buffer = 0;
    bufferLength = 0;

    file = ifstream(filename, fstream::binary);
}

vector<char> BitReader::read(const size_t bits) {
    vector<char> bytes;
    for(unsigned int i = 0; i < bits / 8; i++) {
        char byte = file.get();
        if(file.eof()) return bytes;

        bytes.push_back(buffer | (unsigned char) byte >> bufferLength);
        buffer = byte << (8 - bufferLength);
    }

    if(bits % 8 == 0) {
        return bytes;
    }
    else if(bits % 8 <= bufferLength) {
        bytes.push_back(buffer & -1 << (8 - bits % 8));
        buffer <<= bits % 8;
        bufferLength -= bits % 8;
    }
    else {
        char byte = file.get();
        if(file.eof()) return bytes;

        bytes.push_back((buffer | (unsigned char) byte >> bufferLength) & -1 << (8 - bits % 8));
        buffer = byte << (bits % 8 - bufferLength);
        bufferLength += (8 - bits % 8);
    }

    return bytes;
}

BitReader::~BitReader() {
    file.close();
}
