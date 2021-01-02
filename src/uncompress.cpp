// uncompress.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "hash_functions.hpp"
#include "huffman_code.hpp"
#include "bit_reader.hpp"
#include "bit_writer.hpp"
#include "uncompress.hpp"
#include <iostream>

using namespace std;


void uncompress(string inputFilename, string outputFilename) {
    // Read compressed file
    BitReader bitReader(inputFilename);

    // Read number of bytes in each symbol
    size_t chunkSize = (unsigned char) bitReader.read(4)[0] >> 4;

    // Read number of rows in symbol table
    size_t symbolTableRows = bytesToNumber(bitReader.read(chunkSize * 8));

    // Read symbol table
    unordered_map<HuffmanCode, vector<char>, HuffmanCodeHash> reverseSymbolTable;
    vector<char> replacementSymbol;
    HuffmanCode replacementCode;

    for(unsigned long i = 0; i < symbolTableRows; i++) {
        vector<char> symbol = bitReader.read(chunkSize * 8);
        size_t codeBits = bitReader.read(8)[0];
        vector<char> code = bitReader.read(codeBits);
        HuffmanCode huffmanCode(code, codeBits);

        reverseSymbolTable[huffmanCode] = symbol;
        if(i == symbolTableRows - 1) {
            replacementSymbol = symbol;
            replacementCode = huffmanCode;
        }
    }

    // Read number of replacement values
    size_t replacementValues = bitReader.read(8)[0];

    // Read replacment values
    vector<vector<char>> replacements(1, replacementSymbol);
    for(unsigned long i = 1; i < replacementValues; i++) replacements.push_back(bitReader.read(chunkSize * 8));

    // Read number of bytes in data length
    size_t dataLengthBytes = (unsigned char) bitReader.read(4)[0] >> 4;

    // Read data length (number of symbols in data)
    size_t dataLength = bytesToNumber(bitReader.read(dataLengthBytes * 8));

    // Uncompress actual data
    BitWriter bitWriter(outputFilename);
    unsigned long replacementValueIndex = 0;
    for(unsigned long i = 0; i < dataLength; i++) {
        vector<char> code(1, bitReader.read(1)[0]);
        size_t codeLength = 1;
        while(reverseSymbolTable.find(HuffmanCode(code, codeLength)) == reverseSymbolTable.end()) {
            appendBit(code, codeLength, (unsigned char) bitReader.read(1)[0] >> 7);
        }

        HuffmanCode huffmanCode(code, codeLength);
        vector<char> symbol = huffmanCode == replacementCode ? replacements[replacementValueIndex++] : reverseSymbolTable[huffmanCode];
        bitWriter.write(symbol);
    }
}

unsigned long bytesToNumber(vector<char> bytes) {
    unsigned long num = 0;
    for(unsigned int i = 0, j = bytes.size() * 8 - 8; i < bytes.size(); i++, j -= 8) num |= bytes[i] << j;
    return num;
}

void appendBit(vector<char> &code, size_t &codeLength, char bit) {
    if(codeLength % 8 == 0) {
        code.push_back(0);
    }

    code.back() |= bit << (7 - codeLength % 8);
    codeLength++;
}
