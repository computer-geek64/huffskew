// file_reader.hpp
// Ashish D'Souza

#ifndef COMPRESS_FILE_READER_HPP
#define COMPRESS_FILE_READER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"


class FileReader {
    std::string filename;
    std::size_t chunkSize;
    std::ifstream file;

public:
    FileReader(const std::string, const std::size_t);

    void open(const std::string, const std::size_t);

    void read(std::vector<std::vector<char>>&, std::unordered_map<std::vector<char>, unsigned int, VectorHash<std::vector<char>>>&, std::vector<std::vector<char>>&);

    ~FileReader();
};

#endif
