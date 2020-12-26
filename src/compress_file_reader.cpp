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

void FileReader::read(vector<vector<char>> &data, unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequencies, vector<vector<char>> &singular) {
    char buffer[chunkSize];
    size_t bytesRead;

    while((bytesRead = file.readsome(buffer, chunkSize)) == chunkSize) {
        vector<char> chunk;
        for(unsigned int i = 0; i < bytesRead; i++) {
            chunk.push_back(buffer[i]);
        }

        if(frequencies.find(chunk) == frequencies.end()) {
            frequencies[chunk] = 1;
            singular.push_back(chunk);
        }
        else {
            frequencies[chunk]++;

            for(unsigned int position = 0; position < singular.size(); position++) {
                if(singular[position] == chunk) {
                    singular.erase(singular.begin() + position);
                    break;
                }
            }
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
