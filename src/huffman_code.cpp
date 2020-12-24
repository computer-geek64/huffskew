// huffman_code.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include "huffman_code.hpp"

using namespace std;


HuffmanCode::HuffmanCode() {}

HuffmanCode::HuffmanCode(string code, size_t length) : code(code), length(length) {}

string HuffmanCode::getFullBytes() {
    string sub = code.substr(0, length / 8);
    code.erase(0, length / 8);
    return sub;
}

string HuffmanCode::getCode() const {
    return code;
}

size_t HuffmanCode::getLength() const {
    return length;
}

HuffmanCode::~HuffmanCode() {
}
