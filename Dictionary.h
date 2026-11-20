#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "AVLTree.h"
#include "HashTable.h"
#include "History.h"
#include <string>
using namespace std;

class Dictionary {
private:
    AVLTree avl;
    HashTable hash;
    History history;
    string dataFile;
    int loadCount;
    static string makeKey(const string& word);
public:
    explicit Dictionary(const string& fileName = "data/dictionary.txt");
    bool load();
    bool save() const;
    bool addWord(const Word& word);
    bool updateWord(const string& key, const Word& newData);
    bool deleteWord(const string& key);
    bool findWord(const string& key, Word& result, bool recordHistory = true);
    void suggestPrefix(const string& prefix) const;
    bool toggleFavorite(const string& key);
    void showAll() const;
    void showHistory() const;
    void showHashStats() const;
    void showFavoriteWords() const;
    void comparePerformance() const;
    int size() const;
};
#endif
