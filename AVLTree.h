#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Word.h"
#include <string>
#include <iostream>
using namespace std;

class AVLTree {
private:
    struct Node {
        Word data;
        Node* left;
        Node* right;
        int height;
        Node(const Word& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int nodeCount;
    mutable int lastComparisons;
    static int heightOf(Node* p);
    static int getBalance(Node* p);
    static void updateHeight(Node* p);
    static Node* rotateLeft(Node* p);
    static Node* rotateRight(Node* p);
    static Node* balance(Node* p);
    static Node* insertNode(Node* p, const Word& value, bool& inserted);
    Node* searchNode(Node* p, const string& key) const;
    static Node* minNode(Node* p);
    static Node* removeNode(Node* p, const string& key, bool& removed);
    static void printInOrder(Node* p);
    static void suggestPrefix(Node* p, const string& prefix, int& count, int limit);
    static void destroy(Node* p);
    static void writeInOrder(Node* p, ostream& out);
    static void printFavorites(Node* p);
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    void insert(const Word& value);
    const Word* search(const string& key) const;
    bool remove(const string& key);
    void displayInOrder() const;
    void saveToFile(ostream& out) const;
    void displayFavorites() const;
    void suggest(const string& prefix, int limit = 20) const;
    int size() const;
    int getLastComparisons() const;
    bool isEmpty() const;
    void clear();
};
#endif
