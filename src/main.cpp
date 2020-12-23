// main.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "file_reader.hpp"
#include "main.hpp"

using namespace std;


int main(int argc, char **argv) {
    if(argc < 5) {
        // Show help
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
    vector<char*> data;
    size_t bytesRead = fileReader.read(data);

    for(unsigned int i = 0; i < data.size(); i++) {
        for(unsigned int c = 0; c < chunkSize; c++) {
            cout << data[i][c];
        }
    }
    cout << endl;

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