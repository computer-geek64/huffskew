// bit_writer.hpp
// Ashish D'Souza

#ifndef BIT_WRITER_HPP
#define BIT_WRITER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>


class BitWriter {
    std::string filename;
    std::ofstream file;
    char buffer;
    std::size_t bufferLength;

public:
    BitWriter(const std::string);

    void open(const std::string);

    void write(std::vector<char>);

    void write(std::vector<char>, std::size_t);

    void flush();

    ~BitWriter();
};

#endif
