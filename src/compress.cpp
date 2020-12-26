// compress.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"
#include "compress_file_reader.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"
#include "compress.hpp"
#include <iostream>

using namespace std;


void compress(string inputFilename, string outputFilename, size_t chunkSize) {
    FileReader fileReader(inputFilename, chunkSize);
    vector<vector<char>> data;
    unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> frequency;

    // Read data from file
    fileReader.read(data, frequency);

    // Build Huffman tree
    vector<vector<char>> singular;
    HuffmanTreeNode *root = buildHuffmanTree(frequency, singular);

    // Generate symbol table
    /*map<vector<char>, HuffmanCode> symbolTable = assignHuffmanCodes(root);
    for(unsigned int i = 1; i < singular.size(); i++) {
        symbolTable[singular[i]] = symbolTable[singular[0]];
    }

    for(auto symbol : symbolTable) {
        cout << symbol.first[0] << ": " << hex << (short) symbol.second.getCode()[0] << ": " << dec << symbol.second.getLength() << endl;
    }

    // Prints huffman compression of file
    HuffmanCode curr = symbolTable[data[0]];
    HuffmanCode next;
    for(unsigned int i = 0; i < data.size() - 1; i++) {
        next = symbolTable[data[i + 1]];

        curr = concatenateHuffmanCodes(curr, next);
        cout << "Size: " << curr.getCode().size() << endl;
        cout << "Length: " << curr.getLength() << endl;
        for(char c : curr.getFullBytes()) {
            cout << "NEW BYTES: " << hex << (short) c << endl;
        }
        cout << "New size: " << curr.getCode().size() << endl;
        cout << "New length: " << curr.getLength() << endl;
    }
    cout << hex << (short) curr.getCode()[0] << endl;*/
}
