// file_analyzer.cpp
// Ashish D'Souza

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "hash_functions.hpp"
#include "file_analyzer.hpp"

using namespace std;


FileAnalyzer::FileAnalyzer(const string filename, const size_t chunkSize) {
    open(filename, chunkSize);
}

void FileAnalyzer::open(const string filename, const size_t chunkSize) {
    this->filename = filename;
    this->chunkSize = chunkSize;

    file = ifstream(filename, fstream::binary);
}

size_t FileAnalyzer::read(unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequencies, vector<vector<char>> &singular) {
    char buffer[chunkSize];
    size_t chunks = 0;

    file.read(buffer, chunkSize);
    while(!file.eof()) {
        vector<char> chunk;
        for(unsigned int i = 0; i < chunkSize; i++) {
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

        chunks++;
        file.read(buffer, chunkSize);
    }

    return chunks;
}

FileAnalyzer::~FileAnalyzer() {
    file.close();
}
