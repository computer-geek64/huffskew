// huffman_code.hpp
// Ashish D'Souza

#ifndef HUFFMAN_CODE_HPP
#define HUFFMAN_CODE_HPP

#include <cstddef>
#include <string>


class HuffmanCode {
    std::string code;
    std::size_t length;

public:
    HuffmanCode();

    HuffmanCode(std::string, std::size_t);

    std::string getFullBytes();

    std::string getCode() const;

    std::size_t getLength() const;

    ~HuffmanCode();
};

#endif
