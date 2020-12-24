// huffman_tree_builder.hpp
// Ashish D'Souza

#ifndef HUFFMAN_TREE_BUILDER_HPP
#define HUFFMAN_TREE_BUILDER_HPP

#include <string>
#include <vector>
#include <unordered_map>


void buildHuffmanTree(std::unordered_map<std::string, unsigned int>&);

std::vector<std::string> replaceSingularFrequencies(std::unordered_map<std::string, unsigned int>&);

#endif