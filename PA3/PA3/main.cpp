#include <iostream>
#include <fstream>
#include <chrono>
#include "ChainingHash.h"
#include "ProbingHash.h"

void testHashTable(Hash<int, int>* hashTable, std::ofstream& outFile) {
    outFile << "current size: " << hashTable->size()
        << " bucket count: " << hashTable->bucket_count()
        << " load factor: " << hashTable->load_factor() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        hashTable->insert(std::make_pair(i, i * 2));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    outFile << "Time difference = " << duration << "[ms]" << std::endl;

    hashTable->erase(97);
    outFile << "current size: " << hashTable->size()
        << " bucket count: " << hashTable->bucket_count()
        << " load factor: " << hashTable->load_factor() << std::endl;
}

int main() {
    std::ofstream outFile("output.txt");

    outFile << "Testing ChainingHash:" << std::endl;
    ChainingHash<int, int> chainingHash(101);
    testHashTable(&chainingHash, outFile);
    outFile << "============================" << std::endl;

    outFile << "Testing ProbingHash:" << std::endl;
    ProbingHash<int, int> probingHash(101);
    testHashTable(&probingHash, outFile);
    outFile << "============================" << std::endl;

    outFile.close();
    return 0;
}

