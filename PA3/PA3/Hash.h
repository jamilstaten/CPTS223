#ifndef __HASH_H
#define __HASH_H

#include <utility>      // for std::pair reference: https://www.educative.io/answers/how-to-use-stdpair-in-cpp

/*
 *  Hash - Abstract Base Class
 *
 *  Provides a general interface for concrete hash table implementations
 *  This interface is inspired by the C++11 STL unordered_map
 *
 *  Expected derived classes: ChainingHash, ProbingHash
 */

template <typename K, typename V>
class Hash {
public:
    virtual ~Hash() {}

    // returns the number of elements in the hash table
    virtual int size() const = 0;

    // finds the value associated with key throws exception if key not found.
    virtual V& operator[](const K& key) = 0;

    // inserts a key value pair into the hash table
    virtual bool insert(const std::pair<K, V>& pair) = 0;

    // erases an element with the given key
    virtual void erase(const K& key) = 0;

    // clears the hash table
    virtual void clear() = 0;

    // returns the number of buckets in the hash table
    virtual int bucket_count() const = 0;

    // returns the current load factor of the hash table
    virtual float load_factor() const = 0;

protected:
    // hashes a key
    virtual int hash(const K& key) const = 0;
};

#endif  

