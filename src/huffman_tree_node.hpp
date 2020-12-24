// huffman_tree_node.hpp
// Ashish D'Souza

#ifndef HUFFMAN_TREE_NODE_HPP
#define HUFFMAN_TREE_NODE_HPP

#include <cstddef>
#include <string>


class HuffmanTreeNode {
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    std::string symbol;
    unsigned int frequency;
    std::string code;
    std::size_t codeLength;


public:
    HuffmanTreeNode(std::string, unsigned int);
    HuffmanTreeNode(HuffmanTreeNode*, HuffmanTreeNode*);

    bool isLeaf();

    void setLeft(HuffmanTreeNode*);

    HuffmanTreeNode* getLeft() const;

    void setRight(HuffmanTreeNode*);

    HuffmanTreeNode* getRight() const;

    std::string getSymbol() const;

    unsigned int getFrequency() const;

    void setCode(std::string, std::size_t);

    std::string getCode() const;

    std::size_t getCodeLength() const;

    ~HuffmanTreeNode();
};

#endif
