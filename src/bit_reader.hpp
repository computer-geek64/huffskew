// bit_reader.hpp
// Ashish D'Souza

#ifndef BIT_READER_HPP
#define BIT_READER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

class BitReader {
    std::string filename;
    std::ifstream file;
    char buffer;
    std::size_t bufferLength;

public:
    BitReader(const std::string);

    void open(const std::string);

    std::vector<char> read(const std::size_t);

    ~BitReader();
};

#endif
