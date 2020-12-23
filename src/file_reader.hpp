// file_reader.hpp
// Ashish D'Souza

#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <cstddef>


class FileReader {
    std::string filename;
    std::size_t chunkSize;
    std::ifstream file;

public:
    FileReader(const std::string, const std::size_t);

    void open(const std::string, const std::size_t);

    void read(std::vector<char*> &);

    ~FileReader();
};

#endif
