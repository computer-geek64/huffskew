// huffman_tree_node.hpp
// Ashish D'Souza

#ifndef HUFFMAN_TREE_NODE_HPP
#define HUFFMAN_TREE_NODE_HPP

#include <cstddef>
#include <vector>
#include "huffman_code.hpp"


class HuffmanTreeNode {
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    std::vector<char> symbol;
    unsigned int frequency;
    HuffmanCode huffmanCode;


public:
    HuffmanTreeNode(std::vector<char>, unsigned int);

    HuffmanTreeNode(HuffmanTreeNode*, HuffmanTreeNode*);

    bool isLeaf() const;

    void setLeft(HuffmanTreeNode*);

    HuffmanTreeNode* getLeft() const;

    void setRight(HuffmanTreeNode*);

    HuffmanTreeNode* getRight() const;

    std::vector<char> getSymbol() const;

    unsigned int getFrequency() const;

    void setHuffmanCode(HuffmanCode);

    HuffmanCode getHuffmanCode() const;

    ~HuffmanTreeNode();
};

#endif
