// main.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "file_reader.hpp"
#include "huffman_tree_builder.hpp"
#include "main.hpp"

using namespace std;


int main(int argc, char **argv) {
    if(argc < 5) {
        showHelp();

        return 1;
    }

    vector<string> args;
    for(unsigned int i = 0; i < argc; i++) {
        string arg(*(argv + i));
        if(arg == "-h") {
            showHelp();

            return 0;
        }

        args.push_back(arg);
    }

    string action(args[1]);
    string inputFilename(args[2]);
    string outputFilename(args[4]);

    size_t chunkSize = 1;  // Bytes
    FileReader fileReader(inputFilename, chunkSize);
    vector<string> data;
    unordered_map<string, unsigned int> frequency;
    fileReader.read(data, frequency);

    for(unsigned int i = 0; i < data.size(); i++) {
        cout << data[i];
    }
    cout << endl;

    for(auto &x : frequency) {
        cout << x.first << ": " << x.second << endl;
    }

    buildHuffmanTree(frequency);

    return 0;
}

void showHelp() {
    cout << "Usage: huffskew [action] [filename] -o [filename]" << "\n";
    cout << "\n";
    cout << "Option\t\tDescription" << "\n";
    cout << "-h\t\tShow this help screen" << "\n";
    cout << "-c [filename]\tCompress action" << "\n";
    cout << "-u [filename]\tUncompress action" << "\n";
    cout << "-o [filename]\tOutput file, use \"-\" for STDOUT" << endl;
}