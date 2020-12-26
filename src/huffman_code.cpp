// huffman_code.cpp
// Ashish D'Souza

#include <cstddef>
#include <vector>
#include "huffman_code.hpp"

using namespace std;


HuffmanCode::HuffmanCode() {}

HuffmanCode::HuffmanCode(vector<char> code, size_t length) : code(code), length(length) {}

vector<char> HuffmanCode::getFullBytes() {
    vector<char> sub;
    for(unsigned int i = 0; i < (int) (length / 8); i++) {
        sub.push_back(code[0]);
        code.erase(code.begin());
    }

    length -= length / 8 * 8;

    return sub;
}

vector<char> HuffmanCode::getCode() const {
    return code;
}

size_t HuffmanCode::getLength() const {
    return length;
}

HuffmanCode::~HuffmanCode() {
}
