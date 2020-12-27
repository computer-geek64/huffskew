// compress_file_writer.cpp
// Ashish D'Souza

#include <fstream>
#include <string>
#include <vector>
#include "compress_file_writer.hpp"

using namespace std;


FileWriter::FileWriter(const string filename) {
    open(filename);
}

void FileWriter::open(const string filename) {
    this->filename = filename;
    buffer = 0;
    bufferLength = 0;

    file = ofstream(filename, fstream::binary);
}

void FileWriter::write(vector<char> data) {
    write(data, data.size() * 8);
}

void FileWriter::write(vector<char> data, size_t dataLength) {
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

void FileWriter::flush() {
    if(bufferLength >= 0) {
        file.put(buffer);
    }

    file.flush();
}

FileWriter::~FileWriter() {
    flush();
    file.close();
}