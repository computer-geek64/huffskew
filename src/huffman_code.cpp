// huffman_code.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include "huffman_code.hpp"

using namespace std;


HuffmanCode::HuffmanCode() {}

HuffmanCode::HuffmanCode(string code, size_t length) : code(code), length(length) {}

string HuffmanCode::getCode() const {
    return code;
}

size_t HuffmanCode::getLength() const {
    return length;
}

HuffmanCode::~HuffmanCode() {
}
