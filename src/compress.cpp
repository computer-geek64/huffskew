// compress.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"
#include "file_analyzer.hpp"
#include "bit_reader.hpp"
#include "bit_writer.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"
#include "compress.hpp"

using namespace std;


void compress(string inputFilename, string outputFilename, size_t chunkSize) {
    // Analyze file
    FileAnalyzer fileAnalyzer(inputFilename, chunkSize);
    unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> frequencies;
    vector<vector<char>> singular;

    size_t totalChunks = fileAnalyzer.read(frequencies, singular);

    // Optimize algorithm by replacing singular frequencies
    replaceSingularFrequencies(frequencies, singular);

    // Build Huffman tree
    HuffmanTreeNode *root = buildHuffmanTree(frequencies);

    // Generate symbol table
    unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> symbolTable = assignHuffmanCodes(root);

    // Write to file
    BitWriter bitWriter(outputFilename);

    // Write number of bytes in each symbol
    bitWriter.write(vector<char>(1, (unsigned char) chunkSize << 4), 4);

    // Write number of rows in symbol table
    vector<char> symbolTableRows;
    for(unsigned int i = 0; i < chunkSize * 8; i += 8) {
        symbolTableRows.push_back((unsigned char) (symbolTable.size() >> i));
    }
    bitWriter.write(symbolTableRows);

    // Write symbol table
    for(const auto &symbol : symbolTable) {
        if(singular.empty() || symbol.first != singular[0]) {
            // Write symbol
            bitWriter.write(symbol.first);

            // Write number of bits in symbol code
            bitWriter.write(vector<char>(1, (unsigned char) symbol.second.getLength()));

            // Write symbol code
            bitWriter.write(symbol.second.getCode(), symbol.second.getLength());
        }
    }

    if(!singular.empty()) {
        // Write replacement symbol
        bitWriter.write(singular[0]);

        // Write number of bits in replacement symbol code
        HuffmanCode symbolCode = symbolTable[singular[0]];
        bitWriter.write(vector<char>(1, (unsigned char) symbolCode.getLength()));

        // Write replacement symbol code
        bitWriter.write(symbolCode.getCode(), symbolCode.getLength());
    }

    // Write number of replacement values
    bitWriter.write(vector<char>(1, (unsigned char) singular.size()));

    // Write replacement values (excluding first one, which is the replacement symbol itself and already in the symbol table)
    for(unsigned int i = 1; i < singular.size(); i++) {
        bitWriter.write(singular[i]);
    }

    // Write number of bytes in data length
    size_t dataLength = totalChunks;
    unsigned int dataLengthBytes;
    for(dataLengthBytes = 0; dataLength > 0; dataLengthBytes++) dataLength >>= 8;
    bitWriter.write(vector<char>(1, (unsigned char) dataLengthBytes << 4), 4);

    // Write data length (number of symbols in data)
    dataLength = totalChunks;
    vector<char> dataLengthVector;
    for(int i = dataLengthBytes - 1; i >= 0; i--) {
        dataLengthVector.push_back((unsigned char) (dataLength >> i * 8));
    }
    bitWriter.write(dataLengthVector);

    // Add replacement values into symbol table for actual data compression
    for(unsigned int i = 1; i < singular.size(); i++) {
        symbolTable[singular[i]] = symbolTable[singular[0]];
    }

    // Compress actual data
    BitReader bitReader(inputFilename);
    for(size_t i = 0; i < totalChunks; i++) {
        HuffmanCode symbolCode = symbolTable[bitReader.read(chunkSize * 8)];
        bitWriter.write(symbolCode.getCode(), symbolCode.getLength());
    }

    // Destroy Huffman tree
    destroyHuffmanTree(root);
}

void replaceSingularFrequencies(unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequencies, const vector<vector<char>> &singular) {
    if(singular.empty()) return;

    frequencies[singular[0]] = singular.size();

    for(unsigned int i = 1; i < singular.size(); i++) {
        frequencies.erase(singular[i]);
    }
}
