// compress.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "file_reader.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"
#include "compress.hpp"

using namespace std;


void compress(string inputFilename, string outputFilename, size_t chunkSize) {
    FileReader fileReader(inputFilename, chunkSize);
    vector<string> data;
    unordered_map<string, unsigned int> frequency;

    // Read data from file
    fileReader.read(data, frequency);

    // Build Huffman tree
    HuffmanTreeNode *root = buildHuffmanTree(frequency);
}

HuffmanCode concatenateHuffmanCodes(const HuffmanCode &a, const HuffmanCode &b) {
    // Copy all bytes from a to code
    string code(a.getCode());

    if (a.getLength() % 8 == 0) {
        code.push_back(0);
    }

    for (unsigned int bChar = 0; bChar <= (b.getLength() / 8); bChar++) {
        code[a.getLength() / 8 + bChar] |= (unsigned char) b.getCode()[bChar] >> (a.getLength() % 8);  // Bitwise right shift zero extend
        code.push_back(0);
        code[a.getLength() / 8 + bChar + 1] |= b.getCode()[bChar] << (8 - (a.getLength() % 8));
    }

    // Remove last byte if unnecessary
    if (a.getLength() % 8 + b.getLength() % 8 <= 8) {
        code.pop_back();
    }

    return HuffmanCode(code, a.getLength() + b.getLength());
}
