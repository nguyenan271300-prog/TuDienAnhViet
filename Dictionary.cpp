#include "Dictionary.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;

string Dictionary::makeKey(const string& word) { return Utils::normalize(word); }
Dictionary::Dictionary(const string& fileName) : hash(101), history(20), dataFile(fileName), loadCount(0) {}
bool Dictionary::load() {
    ifstream in(dataFile.c_str());
    if (!in) return false;
    avl.clear(); hash.clear(); loadCount = 0;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1);
        Word item;
        if (Word::fromLine(line, item)) {
            string key = makeKey(item.word);
            avl.insert(item);
            hash.insert(key, item);
            ++loadCount;
        }
    }
    return true;
}
bool Dictionary::save() const {
    ofstream out(dataFile.c_str());
    if (!out) return false;
    avl.saveToFile(out);
    return static_cast<bool>(out);
}
bool Dictionary::addWord(const Word& word) {
    if (Utils::isBlank(word.word)) return false;
    string key = makeKey(word.word);
    Word old;
    if (hash.search(key, old)) return false;
    avl.insert(word); hash.insert(key, word); return true;
}
bool Dictionary::updateWord(const string& key, const Word& newData) {
    string normalized = makeKey(key);
    Word old;
    if (!hash.search(normalized, old)) return false;
    Word updated = newData;
    updated.word = old.word;
    avl.insert(updated); hash.insert(normalized, updated); return true;
}
bool Dictionary::deleteWord(const string& key) {
    string normalized = makeKey(key);
    bool a = avl.remove(normalized);
    bool h = hash.remove(normalized);
    return a && h;
}
bool Dictionary::findWord(const string& key, Word& result, bool recordHistory) {
    string normalized = makeKey(key);
    const Word* found = avl.search(normalized);
    if (!found) return false;
    result = *found;
    if (recordHistory) history.addSearch(found->word);
    return true;
}
void Dictionary::suggestPrefix(const string& prefix) const { avl.suggest(prefix); }
bool Dictionary::toggleFavorite(const string& key) {
    Word item;
    if (!findWord(key, item, false)) return false;
    item.flag = item.flag ? 0 : 1;
    avl.insert(item); hash.insert(makeKey(item.word), item);
    return true;
}
void Dictionary::showAll() const { avl.displayInOrder(); }
void Dictionary::showHistory() const { history.display(); }
void Dictionary::showHashStats() const { hash.printStats(); }
void Dictionary::showFavoriteWords() const {
    avl.displayFavorites();
}
int Dictionary::size() const { return avl.size(); }

void Dictionary::comparePerformance() const {
    ifstream in(dataFile.c_str());
    if (!in) { cout << "Khong mo duoc tep du lieu de thuc nghiem.\n"; return; }
    AVLTree testAVL;
    HashTable testHash(101);
    string line;
    auto startAVL = chrono::high_resolution_clock::now();
    while (getline(in, line)) {
        Word item;
        if (Word::fromLine(line, item)) testAVL.insert(item);
    }
    auto endAVL = chrono::high_resolution_clock::now();
    in.clear(); in.seekg(0);
    auto startHash = chrono::high_resolution_clock::now();
    while (getline(in, line)) {
        Word item;
        if (Word::fromLine(line, item)) testHash.insert(makeKey(item.word), item);
    }
    auto endHash = chrono::high_resolution_clock::now();
    // Chuan bi 100.000 lan tra cuu bang cach lap lai cac tu co trong tep.
    const int TEST_COUNT = 100000;
    string* keys = new string[TEST_COUNT];
    in.clear(); in.seekg(0);
    int loaded = 0;
    while (loaded < TEST_COUNT && getline(in, line)) {
        Word item;
        if (Word::fromLine(line, item)) keys[loaded++] = makeKey(item.word);
    }
    if (loaded == 0) { delete[] keys; cout << "Khong co du lieu hop le.\n"; return; }
    for (int i = loaded; i < TEST_COUNT; ++i) keys[i] = keys[i % loaded];
    long long avlComparisons = 0, hashProbes = 0;
    Word found;
    auto startSearchAVL = chrono::high_resolution_clock::now();
    for (int i = 0; i < TEST_COUNT; ++i) {
        testAVL.search(keys[i]);
        avlComparisons += testAVL.getLastComparisons();
    }
    auto endSearchAVL = chrono::high_resolution_clock::now();
    auto startSearchHash = chrono::high_resolution_clock::now();
    for (int i = 0; i < TEST_COUNT; ++i) {
        testHash.search(keys[i], found);
        hashProbes += testHash.getLastProbes();
    }
    auto endSearchHash = chrono::high_resolution_clock::now();
    cout << "\n===== SO SANH AVL VA BANG BAM =====\n"
         << "So tu xay dung: " << testAVL.size() << '\n'
         << "Thoi gian xay AVL: " << chrono::duration<double, milli>(endAVL - startAVL).count() << " ms\n"
         << "Thoi gian xay Hash: " << chrono::duration<double, milli>(endHash - startHash).count() << " ms\n"
         << "So lan tra cuu: " << TEST_COUNT << '\n'
         << "Thoi gian tra AVL: " << chrono::duration<double, milli>(endSearchAVL - startSearchAVL).count() << " ms\n"
         << "Thoi gian tra Hash: " << chrono::duration<double, milli>(endSearchHash - startSearchHash).count() << " ms\n"
         << "So sanh trung binh AVL: " << static_cast<double>(avlComparisons) / TEST_COUNT << '\n'
         << "So node kiem tra trung binh Hash: " << static_cast<double>(hashProbes) / TEST_COUNT << '\n'
         << "Danh sach lien ket dai nhat Hash: " << testHash.longestChain() << '\n';
    delete[] keys;
}
