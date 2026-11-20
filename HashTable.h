#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Word.h"
#include <string>
using namespace std;

class HashTable {
private:
    struct Node {
        string key;
        Word data;
        Node* next;
        Node(const string& k, const Word& w) : key(k), data(w), next(nullptr) {}
    };
    Node** buckets;
    int capacity;
    int itemCount;
    int maxChain;
    mutable int lastProbes;
    int hashFunction(const string& key) const;
    static bool isPrime(int n);
    static int nextPrime(int n);
    void rehash(int newCapacity);
public:
    explicit HashTable(int initialCapacity = 101);
    ~HashTable();
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    bool insert(const string& key, const Word& value);
    bool search(const string& key, Word& result) const;
    bool remove(const string& key);
    void clear();
    int size() const;
    int bucketCount() const;
    double loadFactor() const;
    int longestChain() const;
    int getLastProbes() const;
    void printStats() const;
};
#endif
