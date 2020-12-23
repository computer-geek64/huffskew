// file_reader.cpp
// Ashish D'Souza

#include <string>
#include <vector>
#include <fstream>
#include <cstddef>
#include "file_reader.hpp"

using namespace std;


FileReader::FileReader(const string filename, const size_t chunkSize) {
    open(filename, chunkSize);
}

void FileReader::open(const string filename, const size_t chunkSize) {
    this->filename = filename;
    this->chunkSize = chunkSize;

    file = ifstream(filename, fstream::binary);
}

int FileReader::read(vector<char*> &data) {
    char *buffer;
    size_t bytesRead;

    while((bytesRead = file.readsome(buffer = new char[chunkSize], chunkSize)) == chunkSize) {
        data.push_back(buffer);
    }

    if(bytesRead > 0) {
        for(unsigned int i = bytesRead; i < chunkSize; i++) {
            buffer[i] = 0;
        }

        data.push_back(buffer);
    }
    else {
        delete [] buffer;
    }

    return bytesRead;
}

FileReader::~FileReader() {
    file.close();
}
