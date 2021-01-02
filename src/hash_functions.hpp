// hash_functions.hpp
// Ashish D'Souza

#ifndef HASH_FUNCTIONS_HPP
#define HASH_FUNCTIONS_HPP

#include <cstddef>
#include <vector>
#include <boost/functional/hash.hpp>
#include "huffman_code.hpp"


template <typename T>
class VectorHash {
public:
    std::size_t operator()(const T &v) const {
        return boost::hash_range(v.begin(), v.end());
    }
};

class HuffmanCodeHash {
public:
    std::size_t operator()(const HuffmanCode &huffmanCode) const {
        std::size_t seed = 0;
        std::vector<char> code = huffmanCode.getCode();
        boost::hash_combine(seed, boost::hash_range(code.begin(), code.end()));
        boost::hash_combine(seed, std::hash<std::size_t>()(huffmanCode.getLength()));
        return seed;
    }
};

#endif
