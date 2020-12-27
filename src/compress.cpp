// compress.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"
#include "compress_file_reader.hpp"
#include "compress_file_writer.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"
#include "compress.hpp"
#include <iostream>

using namespace std;


void compress(string inputFilename, string outputFilename, size_t chunkSize) {
    // Read data from file
    FileReader fileReader(inputFilename, chunkSize);
    vector<vector<char>> data;
    unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> frequencies;
    vector<vector<char>> singular;

    fileReader.read(data, frequencies, singular);

    // Optimize algorithm by replacing singular frequencies
    replaceSingularFrequencies(frequencies, singular);

    // Build Huffman tree
    HuffmanTreeNode *root = buildHuffmanTree(frequencies);

    // Generate symbol table
    unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> symbolTable = assignHuffmanCodes(root);

    // Write to file
    FileWriter fileWriter(outputFilename);

    // Write number of bytes in each symbol
    fileWriter.write(vector<char>(1, (unsigned char) chunkSize << 4), 4);

    // Write number of rows in symbol table
    vector<char> symbolTableRows;
    for(unsigned int i = 0; i < chunkSize * 8; i += 8) {
        symbolTableRows.push_back((unsigned char) (symbolTable.size() >> i));
    }
    fileWriter.write(symbolTableRows);

    // Write symbol table
    for(const auto &symbol : symbolTable) {
        if(singular.empty() || symbol.first != singular[0]) {
            // Write symbol
            fileWriter.write(symbol.first);

            // Write number of bits in symbol code
            fileWriter.write(vector<char>(1, (unsigned char) symbol.second.getLength()));

            // Write symbol code
            fileWriter.write(symbol.second.getCode(), symbol.second.getLength());
        }
    }

    if(!singular.empty()) {
        // Write replacement symbol
        fileWriter.write(singular[0]);

        // Write number of bits in replacement symbol code
        HuffmanCode symbolCode = symbolTable[singular[0]];
        fileWriter.write(vector<char>(1, (unsigned char) symbolCode.getLength()));

        // Write replacement symbol code
        fileWriter.write(symbolCode.getCode(), symbolCode.getLength());
    }

    // Write number of replacement values
    fileWriter.write(vector<char>(1, (unsigned char) singular.size()));

    // Write replacement values (excluding first one, which is the replacement symbol itself and already in the symbol table)
    for(unsigned int i = 1; i < singular.size(); i++) {
        fileWriter.write(singular[i]);
    }

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

void replaceSingularFrequencies(unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequencies, const vector<vector<char>> &singular) {
    if(singular.empty()) return;

    frequencies[singular[0]] = singular.size();

    for(unsigned int i = 1; i < singular.size(); i++) {
        frequencies.erase(singular[i]);
    }
}
