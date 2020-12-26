// file_reader.cpp
// Ashish D'Souza

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"
#include "compress_file_reader.hpp"

using namespace std;


FileReader::FileReader(const string filename, const size_t chunkSize) {
    open(filename, chunkSize);
}

void FileReader::open(const string filename, const size_t chunkSize) {
    this->filename = filename;
    this->chunkSize = chunkSize;

    file = ifstream(filename, fstream::binary);
}

void FileReader::read(vector<vector<char>> &data, unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequency) {
    char *buffer;
    size_t bytesRead;

    while((bytesRead = file.readsome(buffer = new char[chunkSize], chunkSize)) == chunkSize) {
        vector<char> chunk;
        for(unsigned int i = 0; i < bytesRead; i++) {
            chunk.push_back(buffer[i]);
        }

        if(frequency.find(chunk) == frequency.end()) {
            frequency[chunk] = 1;
        }
        else {
            frequency[chunk]++;
        }

        data.push_back(chunk);
    }

    if(bytesRead > 0) {
        vector<char> chunk;
        for(unsigned int i = 0; i < bytesRead; i++) {
            chunk.push_back(buffer[i]);
        }

        data.push_back(chunk);
    }
}

FileReader::~FileReader() {
    file.close();
}
