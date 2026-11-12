#include "AVLTree.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <utility>

AVLTree::Node::Node(const Word& word)
    : data(word), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr), nodeCount(0) {}

AVLTree::~AVLTree() {
    clear();
}

int AVLTree::heightOf(const Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int AVLTree::balanceFactor(const Node* node) {
    if (node == nullptr) return 0;
    return heightOf(node->left) - heightOf(node->right);
}

void AVLTree::updateHeight(Node* node) {
    if (node == nullptr) return;

    int leftHeight = heightOf(node->left);
    int rightHeight = heightOf(node->right);
    node->height = 1 + std::max(leftHeight, rightHeight);
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* middleSubtree = x->right;

    // Xoay phai: dua con trai len lam goc cua nhanh.
    x->right = y;
    y->left = middleSubtree;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* middleSubtree = y->left;

    // Xoay trai: dua con phai len lam goc cua nhanh.
    y->left = x;
    x->right = middleSubtree;

    updateHeight(x);
    updateHeight(y);
    return y;
}

std::string AVLTree::normalize(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return result;
}

AVLTree::Node* AVLTree::rebalance(Node* node) {
    if (node == nullptr) return nullptr;

    updateHeight(node);
    int bf = balanceFactor(node);

    // Lech trai.
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);  // Truong hop LR
        }
        return rotateRight(node);                 // Truong hop LL
    }

    // Lech phai.
    if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right); // Truong hop RL
        }
        return rotateLeft(node);                    // Truong hop RR
    }

    return node;
}

AVLTree::Node* AVLTree::insertNode(Node* node, const Word& word, bool& inserted) {
    if (node == nullptr) {
        inserted = true;
        return new Node(word);
    }

    std::string newKey = normalize(word.english);
    std::string currentKey = normalize(node->data.english);

    if (newKey < currentKey) {
        node->left = insertNode(node->left, word, inserted);
    } else if (newKey > currentKey) {
        node->right = insertNode(node->right, word, inserted);
    } else {
        // Tu da ton tai: cap nhat nghia, khong tao node moi.
        node->data.vietnamese = word.vietnamese;
        return node;
    }

    return rebalance(node);
}

void AVLTree::insert(const Word& word) {
    if (word.english.empty()) return;

    bool inserted = false;
    root = insertNode(root, word, inserted);
    if (inserted) ++nodeCount;
}

AVLTree::Node* AVLTree::findNode(Node* node, const std::string& english) {
    std::string key = normalize(english);

    while (node != nullptr) {
        std::string currentKey = normalize(node->data.english);

        if (key == currentKey) return node;
        if (key < currentKey) node = node->left;
        else node = node->right;
    }

    return nullptr;
}

const Word* AVLTree::search(const std::string& english) const {
    Node* found = findNode(root, english);
    return (found == nullptr) ? nullptr : &found->data;
}

AVLTree::Node* AVLTree::minNode(Node* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

AVLTree::Node* AVLTree::removeNode(
    Node* node, const std::string& english, bool& removed) {

    if (node == nullptr) return nullptr;

    std::string key = normalize(english);
    std::string currentKey = normalize(node->data.english);

    if (key < currentKey) {
        node->left = removeNode(node->left, english, removed);
    } else if (key > currentKey) {
        node->right = removeNode(node->right, english, removed);
    } else {
        removed = true;

        // Truong hop 0 hoac 1 con.
        if (node->left == nullptr || node->right == nullptr) {
            Node* child = (node->left != nullptr) ? node->left : node->right;
            delete node;
            return child;
        }

        // Truong hop 2 con: lay node nho nhat ben cay con phai.
        Node* successor = minNode(node->right);
        node->data = successor->data;

        // Xoa node successor; khong tang/ giam nodeCount tai day.
        bool successorRemoved = false;
        node->right = removeNode(node->right, successor->data.english, successorRemoved);
    }

    return rebalance(node);
}

bool AVLTree::remove(const std::string& english) {
    bool removed = false;
    root = removeNode(root, english, removed);
    if (removed) --nodeCount;
    return removed;
}

void AVLTree::printInOrder(const Node* node) {
    if (node == nullptr) return;

    printInOrder(node->left);
    std::cout << node->data.english << " : "
              << node->data.vietnamese << '\n';
    printInOrder(node->right);
}

void AVLTree::displayInOrder() const {
    if (isEmpty()) {
        std::cout << "Tu dien dang rong.\n";
        return;
    }
    printInOrder(root);
}

void AVLTree::destroy(Node* node) {
    if (node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void AVLTree::clear() {
    destroy(root);
    root = nullptr;
    nodeCount = 0;
}

int AVLTree::size() const {
    return nodeCount;
}

bool AVLTree::isEmpty() const {
    return root == nullptr;
}
