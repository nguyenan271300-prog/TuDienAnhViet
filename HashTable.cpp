#include "HashTable.h"
#include "Utils.h"
#include <iostream>
using namespace std;

HashTable::HashTable(int initialCapacity) {
    capacity = nextPrime(initialCapacity < 11 ? 11 : initialCapacity);
    buckets = new Node*[capacity];
    for (int i = 0; i < capacity; ++i) buckets[i] = nullptr;
    itemCount = 0;
    maxChain = 0;
    lastProbes = 0;
}
HashTable::~HashTable() { clear(); delete[] buckets; }
int HashTable::hashFunction(const string& key) const {
    // Horner: h = (h * 31 + ma_ky_tu) % capacity
    unsigned long long hash = 0;
    for (unsigned char c : key) hash = (hash * 31 + c) % capacity;
    return static_cast<int>(hash);
}
bool HashTable::insert(const string& key, const Word& value) {
    int index = hashFunction(key);
    Node* p = buckets[index];
    while (p) {
        if (p->key == key) { p->data = value; return false; }
        p = p->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    ++itemCount;
    int chainLength = 0;
    for (p = buckets[index]; p; p = p->next) ++chainLength;
    if (chainLength > maxChain) maxChain = chainLength;
    if (loadFactor() > 0.75) rehash(nextPrime(capacity * 2));
    return true;
}
bool HashTable::search(const string& key, Word& result) const {
    int index = hashFunction(key);
    lastProbes = 0;
    for (Node* p = buckets[index]; p; p = p->next) {
        ++lastProbes;
        if (p->key == key) { result = p->data; return true; }
    }
    return false;
}
bool HashTable::remove(const string& key) {
    int index = hashFunction(key);
    Node* p = buckets[index];
    Node* previous = nullptr;
    while (p) {
        if (p->key == key) {
            if (previous) previous->next = p->next;
            else buckets[index] = p->next;
            delete p;
            --itemCount;
            return true;
        }
        previous = p; p = p->next;
    }
    return false;
}
void HashTable::rehash(int newCapacity) {
    Node** oldBuckets = buckets;
    int oldCapacity = capacity;
    capacity = newCapacity;
    buckets = new Node*[capacity];
    for (int i = 0; i < capacity; ++i) buckets[i] = nullptr;
    maxChain = 0;
    for (int i = 0; i < oldCapacity; ++i) {
        Node* p = oldBuckets[i];
        while (p) {
            Node* next = p->next;
            int index = hashFunction(p->key);
            p->next = buckets[index];
            buckets[index] = p;
            p = next;
        }
    }
    delete[] oldBuckets;
    for (int i = 0; i < capacity; ++i) {
        int count = 0;
        for (Node* p = buckets[i]; p; p = p->next) ++count;
        if (count > maxChain) maxChain = count;
    }
}
void HashTable::clear() {
    for (int i = 0; i < capacity; ++i) {
        Node* p = buckets[i];
        while (p) { Node* next = p->next; delete p; p = next; }
        buckets[i] = nullptr;
    }
    itemCount = 0; maxChain = 0;
}
int HashTable::size() const { return itemCount; }
int HashTable::bucketCount() const { return capacity; }
double HashTable::loadFactor() const { return capacity ? static_cast<double>(itemCount) / capacity : 0; }
int HashTable::longestChain() const { return maxChain; }
int HashTable::getLastProbes() const { return lastProbes; }
void HashTable::printStats() const {
    int empty = 0, longest = 0;
    for (int i = 0; i < capacity; ++i) {
        int count = 0;
        for (Node* p = buckets[i]; p; p = p->next) ++count;
        if (count == 0) ++empty;
        if (count > longest) longest = count;
    }
    cout << "\n===== THONG KE BANG BAM =====\n"
         << "So tu: " << itemCount << "\nSo bucket: " << capacity
         << "\nHe so tai: " << loadFactor() << "\nDanh sach dai nhat: " << longest
         << "\nBucket rong: " << empty << '\n';
}
bool HashTable::isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}
int HashTable::nextPrime(int n) { while (!isPrime(n)) ++n; return n; }
