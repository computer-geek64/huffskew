// huffman_tree_builder.cpp
// Ashish

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"

using namespace std;


HuffmanTreeNode* buildHuffmanTree(unordered_map<string, unsigned int> &frequency) {
    // Get list of symbols with singular frequencies
    vector<string> singular = replaceSingularFrequencies(frequency);

    // Build priority queue of Huffman tree nodes
    class HuffmanTreeNodeComparator {
    public:
        bool operator()(HuffmanTreeNode *const a, HuffmanTreeNode *const b) const {
            return a->getFrequency() > b->getFrequency();
        }
    };

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, HuffmanTreeNodeComparator> priorityQueue;
    for(auto symbol : frequency) {
        HuffmanTreeNode *huffmanTreeNode = new HuffmanTreeNode(symbol.first, symbol.second);
        priorityQueue.push(huffmanTreeNode);
    }

    // Build Huffman tree using priority queue
    while(priorityQueue.size() > 1) {
        HuffmanTreeNode *left = priorityQueue.top();
        priorityQueue.pop();
        HuffmanTreeNode *right = priorityQueue.top();
        priorityQueue.pop();

        HuffmanTreeNode *huffmanTreeNode = new HuffmanTreeNode(left, right);
        priorityQueue.push(huffmanTreeNode);
    }

    // Assign variable-length codes to each symbol
    HuffmanTreeNode *root = priorityQueue.top();
    assignCodes(root);

    return root;
}

vector<string> replaceSingularFrequencies(unordered_map<string, unsigned int> &frequency) {
    vector<string> singular;
    for(auto symbol : frequency) {
        if(symbol.second == 1) singular.push_back(symbol.first);
    }

    frequency[singular[0]] = singular.size();
    for(unsigned int i = 1; i < singular.size(); i++) {
        frequency.erase(singular[i]);
    }

    return singular;
}

void assignCodes(HuffmanTreeNode *node, vector<char> stack) {
    if(node->isLeaf()) {
        string code;
        char c = 0;
        for(unsigned int i = 0; i < stack.size(); i++) {
            c |= stack[i] << ((7 - i) % 8);
            if(i % 8 == 7) {
                code.push_back(c);
                c = 0;
            }
        }

        if(c != 0) code.push_back(c);

        node->setHuffmanCode(HuffmanCode(code, stack.size()));
    }

    stack.push_back(0);
    if(node->getLeft() != nullptr) assignCodes(node->getLeft(), stack);

    stack[stack.size() - 1] = 1;
    if(node->getRight() != nullptr) assignCodes(node->getRight(), stack);
}
