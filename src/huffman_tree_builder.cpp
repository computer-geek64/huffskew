// huffman_tree_builder.cpp
// Ashish

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"

using namespace std;


void buildHuffmanTree(unordered_map<string, unsigned int> &frequency) {
    vector<string> singular = replaceSingularFrequencies(frequency);

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

    while(priorityQueue.size() > 1) {
        HuffmanTreeNode *left = priorityQueue.top();
        priorityQueue.pop();
        HuffmanTreeNode *right = priorityQueue.top();
        priorityQueue.pop();

        HuffmanTreeNode *huffmanTreeNode = new HuffmanTreeNode(left, right);
        priorityQueue.push(huffmanTreeNode);
    }

    HuffmanTreeNode *root = priorityQueue.top();
    vector<char> stack;
    assignCodes(root);

    cout << "Root: " << root->getFrequency() << endl;
    cout << "Left: " << root->getLeft()->getSymbol() << ": " << root->getLeft()->getFrequency() << ": " << hex << (short) root->getLeft()->getCode()[0] << endl;
    cout << "Right: " << root->getRight()->getFrequency() << endl;
    cout << "Right Left: " << root->getRight()->getLeft()->getSymbol() << ": " << root->getRight()->getLeft()->getFrequency() << ": " << (short) root->getRight()->getLeft()->getCode()[0] << endl;
    cout << "Right Right: " << root->getRight()->getRight()->getSymbol() << ": " << root->getRight()->getRight()->getFrequency() << ": " << (short) root->getRight()->getRight()->getCode()[0] << endl;
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

        node->setCode(code, stack.size());
    }

    stack.push_back(0);
    if(node->getLeft() != nullptr) assignCodes(node->getLeft(), stack);

    stack[stack.size() - 1] = 1;
    if(node->getRight() != nullptr) assignCodes(node->getRight(), stack);
}
