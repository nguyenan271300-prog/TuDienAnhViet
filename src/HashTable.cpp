#include "../include/HashTable.h"
#include "../include/Utils.h"
#include <iostream>
#include <algorithm>
#include <cstdint>

HashTable::HashTable(std::size_t capacity) {
    if (capacity < 11) capacity = 11;
    if (!Utils::isPrime(capacity)) capacity = nextPrime(capacity);
    buckets_.resize(capacity);
}

std::size_t HashTable::hashFunction(const std::string& key) const {
    const std::uint64_t BASE = 131;
    std::uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : key) {
        h ^= static_cast<std::uint64_t>(c);
        h *= BASE;
        h ^= (h >> 33);
    }
    return static_cast<std::size_t>(h % buckets_.size());
}

bool HashTable::insert(const std::string& key, const Word& value) {
    std::size_t idx = hashFunction(key);
    auto& chain = buckets_[idx];

    for (auto& kv : chain) {
        if (kv.first == key) {
            kv.second = value;
            return false;
        }
    }

    chain.emplace_back(key, value);
    ++size_;

    if (loadFactor() > MAX_LOAD_FACTOR) {
        rehash(nextPrime(buckets_.size() * 2));
    }
    return true;
}

bool HashTable::search(const std::string& key, Word& outValue) const {
    std::size_t idx = hashFunction(key);
    const auto& chain = buckets_[idx];
    for (const auto& kv : chain) {
        if (kv.first == key) {
            outValue = kv.second;
            return true;
        }
    }
    return false;
}

bool HashTable::contains(const std::string& key) const {
    std::size_t idx = hashFunction(key);
    for (const auto& kv : buckets_[idx])
        if (kv.first == key) return true;
    return false;
}

bool HashTable::remove(const std::string& key) {
    std::size_t idx = hashFunction(key);
    auto& chain = buckets_[idx];

    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->first == key) {
            chain.erase(it);
            --size_;
            if (buckets_.size() > 11 && loadFactor() < MIN_LOAD_FACTOR) {
                rehash(nextPrime(buckets_.size() / 2));
            }
            return true;
        }
    }
    return false;
}

double HashTable::loadFactor() const noexcept {
    return buckets_.empty() ? 0.0 : static_cast<double>(size_) / buckets_.size();
}

void HashTable::rehash(std::size_t newCapacity) {
    std::vector<std::list<KeyValue>> newBuckets(newCapacity);
    for (auto& chain : buckets_) {
        for (auto& kv : chain) {
            std::uint64_t h = 1469598103934665603ULL;
            for (unsigned char c : kv.first) {
                h ^= static_cast<std::uint64_t>(c);
                h *= 131;
                h ^= (h >> 33);
            }
            std::size_t idx = static_cast<std::size_t>(h % newCapacity);
            newBuckets[idx].push_back(std::move(kv));
        }
    }
    buckets_ = std::move(newBuckets);
}

std::size_t HashTable::nextPrime(std::size_t n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) ++n;
    while (!Utils::isPrime(n)) n += 2;
    return n;
}

void HashTable::forEach(const std::function<void(const KeyValue&)>& fn) const {
    for (const auto& chain : buckets_) {
        for (const auto& kv : chain) fn(kv);
    }
}

void HashTable::printStats() const {
    std::size_t maxChain = 0, emptyBuckets = 0;
    double avgChain = 0.0;
    for (const auto& chain : buckets_) {
        maxChain = std::max(maxChain, chain.size());
        if (chain.empty()) ++emptyBuckets;
        avgChain += static_cast<double>(chain.size());
    }
    if (!buckets_.empty()) avgChain /= buckets_.size();

    std::cout << "===== HashTable Stats =====\n"
              << "Buckets       : " << buckets_.size() << "\n"
              << "Size          : " << size_ << "\n"
              << "Load factor   : " << loadFactor() << "\n"
              << "Max chain len : " << maxChain << "\n"
              << "Avg chain len : " << avgChain << "\n"
              << "Empty buckets : " << emptyBuckets << "\n"
              << "===========================\n";
}

void HashTable::clear() {
    for (auto& chain : buckets_) chain.clear();
    size_ = 0;
}