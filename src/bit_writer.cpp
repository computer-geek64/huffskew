// bit_writer.cpp
// Ashish D'Souza

#include <fstream>
#include <string>
#include <vector>
#include "bit_writer.hpp"

using namespace std;


BitWriter::BitWriter(const string filename) {
    open(filename);
}

void BitWriter::open(const string filename) {
    this->filename = filename;
    buffer = 0;
    bufferLength = 0;

    file = ofstream(filename, fstream::binary);
}

void BitWriter::write(vector<char> data) {
    write(data, data.size() * 8);
}

void BitWriter::write(vector<char> data, size_t dataLength) {
    for(unsigned int i = 0; i < dataLength / 8; i++) {
        char o = buffer | (unsigned char) data[i] >> bufferLength;
        file.put(o);
        buffer = data[i] << (8 - bufferLength);
    }

    if(dataLength % 8 == 0) {
        file.flush();
        return;
    }

    buffer |= (unsigned char) data[dataLength / 8] >> bufferLength;

    if(bufferLength + dataLength % 8 < 8) {
        bufferLength += dataLength % 8;
    }
    else {
        file.put(buffer);
        buffer = data[dataLength / 8] << (8 - bufferLength);
        bufferLength = (dataLength % 8) - (8 - bufferLength);
    }

    if(bufferLength == 0) {
        file.flush();
    }
}

void BitWriter::flush() {
    if(bufferLength > 0) {
        file.put(buffer);
    }

    file.flush();
}

BitWriter::~BitWriter() {
    flush();
    file.close();
}