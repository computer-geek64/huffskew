// vector_hash.hpp
// Ashish D'Souza

#ifndef VECTOR_HASH_HPP
#define VECTOR_HASH_HPP

#include <cstddef>
#include <boost/functional/hash.hpp>


template <typename T>
class VectorHash {
public:
    std::size_t operator()(const T &v) const {
        return boost::hash_range(v.begin(), v.end());
    }
};

#endif
