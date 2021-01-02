// uncompress.hpp
// Ashish D'Souza

#ifndef UNCOMPRESS_HPP
#define UNCOMPRESS_HPP

#include <cstddef>
#include <string>
#include <vector>


void uncompress(std::string, std::string);

unsigned long bytesToNumber(std::vector<char>);

void appendBit(std::vector<char>&, std::size_t&, char);

#endif
