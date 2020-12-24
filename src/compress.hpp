// compress.hpp
// Ashish D'Souza

#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <cstddef>
#include <string>
#include "huffman_code.hpp"


void compress(std::string, std::string, std::size_t = 1);

HuffmanCode concatenateHuffmanCodes(const HuffmanCode&, const HuffmanCode&);

#endif
