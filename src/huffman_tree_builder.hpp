// huffman_tree_builder.hpp
// Ashish D'Souza

#ifndef HUFFMAN_TREE_BUILDER_HPP
#define HUFFMAN_TREE_BUILDER_HPP

#include <vector>
#include <unordered_map>
#include "vector_hash.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"


HuffmanTreeNode* buildHuffmanTree(std::unordered_map<std::vector<char>, unsigned int, VectorHash<std::vector<char>>>&);

std::unordered_map<std::vector<char>, HuffmanCode, VectorHash<std::vector<char>>> assignHuffmanCodes(HuffmanTreeNode*, std::vector<char> = std::vector<char>());

void destroyHuffmanTree(HuffmanTreeNode*);

#endif
