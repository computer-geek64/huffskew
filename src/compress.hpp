// compress.hpp
// Ashish D'Souza

#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"


void compress(std::string, std::string, std::size_t = 1);

void replaceSingularFrequencies(std::unordered_map<std::vector<char>, unsigned int, VectorHash<std::vector<char>>>&, const std::vector<std::vector<char>>&);

#endif
