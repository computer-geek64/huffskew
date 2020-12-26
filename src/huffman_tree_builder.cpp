// huffman_tree_builder.cpp
// Ashish

#include <vector>
#include <queue>
#include <unordered_map>
#include "vector_hash.hpp"
#include "huffman_code.hpp"
#include "huffman_tree_node.hpp"
#include "huffman_tree_builder.hpp"

using namespace std;


HuffmanTreeNode* buildHuffmanTree(unordered_map<vector<char>, unsigned int, VectorHash<vector<char>>> &frequencies) {

    // Build priority queue of Huffman tree nodes
    class HuffmanTreeNodeComparator {
    public:
        bool operator()(HuffmanTreeNode *const a, HuffmanTreeNode *const b) const {
            return a->getFrequency() > b->getFrequency();
        }
    };

    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, HuffmanTreeNodeComparator> priorityQueue;
    for(auto symbol : frequencies) {
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

    return priorityQueue.top();
}

unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> assignHuffmanCodes(HuffmanTreeNode *node, vector<char> stack) {
    unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> symbolTable;

    // Assign Huffman code if node is a leaf
    if(node->isLeaf()) {
        vector<char> code;
        char c = 0;
        unsigned int i;
        for(i = 0; i < stack.size(); i++) {
            c |= stack[i] << ((7 - i) % 8);
            if(i % 8 == 7) {
                code.push_back(c);
                c = 0;
            }
        }

        if(i % 8 != 0) code.push_back(c);

        HuffmanCode huffmanCode(code, stack.size());
        symbolTable[node->getSymbol()] = huffmanCode;
        node->setHuffmanCode(huffmanCode);
    }

    // Recursively assign Huffman codes on left subtree
    stack.push_back(0);
    if(node->getLeft() != nullptr) {
        unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> leftSymbolTable = assignHuffmanCodes(node->getLeft(), stack);
        symbolTable.insert(leftSymbolTable.begin(), leftSymbolTable.end());
    }

    // Recursively assign Huffman codes on right subtree
    stack[stack.size() - 1] = 1;
    if(node->getRight() != nullptr) {
        unordered_map<vector<char>, HuffmanCode, VectorHash<vector<char>>> rightSymbolTable = assignHuffmanCodes(node->getRight(), stack);
        symbolTable.insert(rightSymbolTable.begin(), rightSymbolTable.end());
    }

    return symbolTable;
}
