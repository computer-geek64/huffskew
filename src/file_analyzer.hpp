// file_analyzer.hpp
// Ashish D'Souza

#ifndef FILE_ANALYZER_HPP
#define FILE_ANALYZER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "hash_functions.hpp"


class FileAnalyzer {
    std::string filename;
    std::size_t chunkSize;
    std::ifstream file;

public:
    FileAnalyzer(const std::string, const std::size_t);

    void open(const std::string, const std::size_t);

    std::size_t read(std::unordered_map<std::vector<char>, unsigned int, VectorHash<std::vector<char>>>&, std::vector<std::vector<char>>&);

    ~FileAnalyzer();
};

#endif
