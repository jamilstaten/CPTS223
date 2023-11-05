#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Hash.h"

enum BucketStatus { EMPTY, FULL, DELETED };

template<typename K, typename V>
class ProbingHash : public Hash<K, V> {
private:
    struct Bucket {
        std::pair<K, V> pair;
        BucketStatus status;
        Bucket() : status(EMPTY) {}
    };

    std::vector<Bucket> table;
    int num_elements;

    int hash(const K& key) const {
        return std::hash<K>{}(key) % table.size();
    }

    void rehash() {
        int newSize = findNextPrime(table.size() * 2);
        std::vector<Bucket> newTable(newSize);

        for (const auto& bucket : table) {
            if (bucket.status == FULL) {
                int idx = std::hash<K>{}(bucket.pair.first) % newSize;
                while (newTable[idx].status == FULL) {
                    idx = (idx + 1) % newSize;
                }
                newTable[idx].pair = bucket.pair;
                newTable[idx].status = FULL;
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
    ProbingHash(int n = 101) : table(n), num_elements(0) {}

    ~ProbingHash() {
        clear();
    }

    int size() const override {
        return num_elements;
    }

    V& operator[](const K& key) override {
        int idx = hash(key);
        int start_idx = idx;
        do {
            if (table[idx].status == FULL && table[idx].pair.first == key) {
                return table[idx].pair.second;
            }
            idx = (idx + 1) % table.size();
        } while (table[idx].status != EMPTY && idx != start_idx);

        throw std::runtime_error("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) override {
        if (load_factor() > 0.75) {
            rehash();
        }

        int idx = hash(pair.first);
        while (table[idx].status == FULL && table[idx].pair.first != pair.first) {
            idx = (idx + 1) % table.size();
        }

        if (table[idx].status == FULL) {
            return false; // key already exists
        }

        table[idx].pair = pair;
        table[idx].status = FULL;
        num_elements++;
        return true;
    }

    void erase(const K& key) override {
        int idx = hash(key);
        while (table[idx].status != EMPTY && table[idx].pair.first != key) {
            idx = (idx + 1) % table.size();
        }

        if (table[idx].status == FULL && table[idx].pair.first == key) {
            table[idx].status = DELETED;
            num_elements--;
        }
    }

    void clear() override {
        for (auto& bucket : table) {
            bucket.status = EMPTY;
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


