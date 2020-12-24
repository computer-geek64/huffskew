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

    cout << "Root: " << root->getSymbol() << ": " << root->getFrequency() << endl;
    cout << "Left: " << root->getLeft()->getSymbol() << ": " << root->getLeft()->getFrequency() << endl;
    cout << "Right: " << root->getRight()->getSymbol() << ": " << root->getRight()->getFrequency() << endl;
    cout << "Right Left: " << root->getRight()->getLeft()->getSymbol() << ": " << root->getRight()->getLeft()->getFrequency() << endl;
    cout << "Right Right: " << root->getRight()->getRight()->getSymbol() << ": " << root->getRight()->getRight()->getFrequency() << endl;
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
