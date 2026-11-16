#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <cstddef>
#include "Word.h" 

class HashTable {
public:
    using KeyValue = std::pair<std::string, Word>;

    explicit HashTable(std::size_t capacity = 101);
    ~HashTable() = default;

    bool insert(const std::string& key, const Word& value);
    bool search(const std::string& key, Word& outValue) const;
    bool contains(const std::string& key) const;
    bool remove(const std::string& key);

    std::size_t size() const noexcept { return size_; }
    std::size_t bucketCount() const noexcept { return buckets_.size(); }
    bool empty() const noexcept { return size_ == 0; }
    double loadFactor() const noexcept;

    void forEach(const std::function<void(const KeyValue&)>& fn) const;
    void printStats() const;
    void clear();

private:
    std::size_t hashFunction(const std::string& key) const;
    void rehash(std::size_t newCapacity);
    static std::size_t nextPrime(std::size_t n);

    std::vector<std::list<KeyValue>> buckets_;
    std::size_t size_ = 0;

    static constexpr double MAX_LOAD_FACTOR = 0.75;
    static constexpr double MIN_LOAD_FACTOR = 0.10;
};

#endif // HASHTABLE_H