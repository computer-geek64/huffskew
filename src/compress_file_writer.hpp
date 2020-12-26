// compress_file_writer.hpp
// Ashish D'Souza

#ifndef COMPRESS_FILE_WRITER_HPP
#define COMPRESS_FILE_WRITER_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>


class FileWriter {
    std::string filename;
    std::ofstream file;
    char buffer;
    std::size_t bufferLength;

public:
    FileWriter(const std::string);

    void open(const std::string);

    void write(std::vector<char>);

    void write(std::vector<char>, std::size_t);

    void flush();

    ~FileWriter();
};

#endif
