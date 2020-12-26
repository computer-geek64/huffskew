// huffman_code.hpp
// Ashish D'Souza

#ifndef HUFFMAN_CODE_HPP
#define HUFFMAN_CODE_HPP

#include <cstddef>
#include <vector>


class HuffmanCode {
    std::vector<char> code;
    std::size_t length;

public:
    HuffmanCode();

    HuffmanCode(std::vector<char>, std::size_t);

    std::vector<char> getFullBytes();

    std::vector<char> getCode() const;

    std::size_t getLength() const;

    ~HuffmanCode();
};

#endif
