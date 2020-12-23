// file_reader.hpp
// Ashish D'Souza

#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>


class FileReader {
    std::string filename;
    std::size_t chunkSize;
    std::ifstream file;

public:
    FileReader(const std::string, const std::size_t);

    void open(const std::string, const std::size_t);

    void read(std::vector<std::string>&, std::unordered_map<std::string, unsigned int>&);

    ~FileReader();
};

#endif
