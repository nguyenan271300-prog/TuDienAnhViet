#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include "Word.h"

// Cay AVL luu tu dien: english la khoa, vietnamese la nghia.
class AVLTree {
private:
    struct Node {
        Word data;
        Node* left;
        Node* right;
        int height;

        explicit Node(const Word& word);
    };

    Node* root;
    int nodeCount;

    static int heightOf(const Node* node);
    static int balanceFactor(const Node* node);
    static void updateHeight(Node* node);

    static Node* rotateRight(Node* y);
    static Node* rotateLeft(Node* x);
    static Node* rebalance(Node* node);

    static std::string normalize(const std::string& text);
    static Node* insertNode(Node* node, const Word& word, bool& inserted);
    static Node* findNode(Node* node, const std::string& english);
    static Node* minNode(Node* node);
    static Node* removeNode(Node* node, const std::string& english, bool& removed);
    static void printInOrder(const Node* node);
    static void destroy(Node* node);

public:
    AVLTree();
    ~AVLTree();

    // Khong cho copy de tranh hai cay cung quan ly mot vung nho.
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // Them tu moi. Neu tu da co, cap nhat nghia tieng Viet.
    void insert(const Word& word);

    // Tra ve con tro den Word neu tim thay, nguoc lai tra ve nullptr.
    const Word* search(const std::string& english) const;

    // Xoa tu theo tieng Anh. Tra ve true neu xoa thanh cong.
    bool remove(const std::string& english);

    // Duyet LNR: hien thi tu theo thu tu alphabet.
    void displayInOrder() const;

    int size() const;
    bool isEmpty() const;
    void clear();
};

#endif
