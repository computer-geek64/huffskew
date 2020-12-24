// huffman_tree_node.cpp
// Ashish D'Souza

#include <cstddef>
#include <string>
#include "huffman_tree_node.hpp"

using namespace std;


HuffmanTreeNode::HuffmanTreeNode(string symbol, unsigned int frequency) : symbol(symbol), frequency(frequency) {}

HuffmanTreeNode::HuffmanTreeNode(HuffmanTreeNode *left, HuffmanTreeNode *right) : left(left), right(right), frequency(left->getFrequency() + right->getFrequency())  {}

bool HuffmanTreeNode::isLeaf() {
    return left == nullptr && right == nullptr;
}

void HuffmanTreeNode::setLeft(HuffmanTreeNode *left) {
    this->left = left;
}

HuffmanTreeNode* HuffmanTreeNode::getLeft() const {
    return left;
}

void HuffmanTreeNode::setRight(HuffmanTreeNode *right) {
    this->right = right;
}

HuffmanTreeNode* HuffmanTreeNode::getRight() const {
    return right;
}

string HuffmanTreeNode::getSymbol() const {
    return symbol;
}

unsigned int HuffmanTreeNode::getFrequency() const {
    return frequency;
}

void HuffmanTreeNode::setCode(string code, size_t codeLength) {
    this->code = code;
    this->codeLength = codeLength;
}

string HuffmanTreeNode::getCode() const {
    return code;
}

size_t HuffmanTreeNode::getCodeLength() const {
    return codeLength;
}

HuffmanTreeNode::~HuffmanTreeNode() {
    delete left;
    delete right;
}
