#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Word.h"
#include <string>
#include <vector>
using namespace std;

struct AVLNode {
    Word data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Word& value) : data(value), height(1), left(NULL), right(NULL) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* p);
    int getBalance(AVLNode* p);
    void updateHeight(AVLNode* p);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balanceNode(AVLNode* p);
    AVLNode* insertNode(AVLNode* p, const Word& value, bool& inserted);
    AVLNode* minNode(AVLNode* p);
    AVLNode* deleteNode(AVLNode* p, const string& key, bool& deleted);
    AVLNode* searchNode(AVLNode* p, const string& key, long long* comparisons);
    void prefixNode(AVLNode* p, const string& prefix, vector<Word>& result);
    void collectNode(AVLNode* p, vector<Word>& result);
    void destroy(AVLNode* p);

public:
    AVLTree();
    ~AVLTree();

    bool insert(const Word& value);
    bool remove(const string& key);
    bool search(const string& key, Word& result, long long* comparisons = NULL);
    bool update(const Word& value);
    void prefixSearch(const string& prefix, vector<Word>& result);
    void getAll(vector<Word>& result);
    void clear();
};

#endif
