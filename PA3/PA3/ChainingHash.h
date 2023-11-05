#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include "Hash.h"

template<typename K, typename V>
class ChainingHash : public Hash<K, V> {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    int num_elements;

    int hash(const K& key) const {
        return std::hash<K>{}(key) % table.size();
    }

    void rehash() {
        int newSize = findNextPrime(table.size() * 2);
        std::vector<std::list<std::pair<K, V>>> newTable(newSize);

        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                int newHash = std::hash<K>{}(pair.first) % newSize;
                newTable[newHash].push_back(pair);
            }
        }

        table = std::move(newTable);
    }

    int findNextPrime(int n) const {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;

        if (n % 2 == 0 || n % 3 == 0) return false;

        int i = 5;
        while (i * i <= n) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
            i += 6;
        }

        return true;
    }

public:
    ChainingHash(int n = 11) : table(n), num_elements(0) {}

    ~ChainingHash() {
        clear();
    }

    int size() const override {
        return num_elements;
    }

    V& operator[](const K& key) override {
        auto& bucket = table[hash(key)];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::runtime_error("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) override {
        if (load_factor() > 0.75) {
            rehash();
        }

        auto& bucket = table[hash(pair.first)];
        for (const auto& existingPair : bucket) {
            if (existingPair.first == pair.first) {
                return false; // key already exists
            }
        }

        bucket.push_back(pair);
        num_elements++;
        return true;
    }

    void erase(const K& key) override {
        auto& bucket = table[hash(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ) {
            if (it->first == key) {
                it = bucket.erase(it);
                num_elements--;
            }
            else {
                ++it;
            }
        }
    }

    void clear() override {
        for (auto& bucket : table) {
            bucket.clear();
        }
        num_elements = 0;
    }

    int bucket_count() const override {
        return table.size();
    }

    float load_factor() const override {
        return static_cast<float>(num_elements) / static_cast<float>(bucket_count());
    }
};

#endif


