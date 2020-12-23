// file_reader.cpp
// Ashish D'Souza

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
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

void FileReader::read(vector<string> &data, unordered_map<string, unsigned int> &frequency) {
    char *buffer;
    size_t bytesRead;

    while((bytesRead = file.readsome(buffer = new char[chunkSize], chunkSize)) == chunkSize) {
        string chunk(buffer, bytesRead);

        if(frequency.find(buffer) == frequency.end()) {
            frequency[chunk] = 1;
        }
        else {
            frequency[chunk]++;
        }

        data.push_back(chunk);
    }

    if(bytesRead > 0) {
        string chunk(buffer, bytesRead);
        data.push_back(chunk);
    }
}

FileReader::~FileReader() {
    file.close();
}
