#include "AVLTree.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
using namespace std;

AVLTree::AVLTree() : root(nullptr), nodeCount(0), lastComparisons(0) {}
AVLTree::~AVLTree() { clear(); }
int AVLTree::heightOf(Node* p) { return p ? p->height : 0; }
int AVLTree::getBalance(Node* p) { return p ? heightOf(p->left) - heightOf(p->right) : 0; }
void AVLTree::updateHeight(Node* p) {
    if (p) p->height = 1 + max(heightOf(p->left), heightOf(p->right));
}
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* middle = x->right;
    x->right = y;
    y->left = middle;
    updateHeight(y);
    updateHeight(x);
    return x;
}
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* middle = y->left;
    y->left = x;
    x->right = middle;
    updateHeight(x);
    updateHeight(y);
    return y;
}
AVLTree::Node* AVLTree::balance(Node* p) {
    if (!p) return nullptr;
    updateHeight(p);
    int bf = getBalance(p);
    if (bf > 1) {
        if (getBalance(p->left) < 0) p->left = rotateLeft(p->left); // LR
        return rotateRight(p); // LL
    }
    if (bf < -1) {
        if (getBalance(p->right) > 0) p->right = rotateRight(p->right); // RL
        return rotateLeft(p); // RR
    }
    return p;
}
AVLTree::Node* AVLTree::insertNode(Node* p, const Word& value, bool& inserted) {
    if (!p) { inserted = true; return new Node(value); }
    string key = Utils::normalize(value.word);
    string current = Utils::normalize(p->data.word);
    if (key < current) p->left = insertNode(p->left, value, inserted);
    else if (key > current) p->right = insertNode(p->right, value, inserted);
    else { p->data = value; return p; }
    return balance(p);
}
void AVLTree::insert(const Word& value) {
    if (Utils::isBlank(value.word)) return;
    bool inserted = false;
    root = insertNode(root, value, inserted);
    if (inserted) ++nodeCount;
}
AVLTree::Node* AVLTree::searchNode(Node* p, const string& key) const {
    string target = Utils::normalize(key);
    lastComparisons = 0;
    while (p) {
        ++lastComparisons;
        string current = Utils::normalize(p->data.word);
        if (target == current) return p;
        p = (target < current) ? p->left : p->right;
    }
    return nullptr;
}
const Word* AVLTree::search(const string& key) const {
    Node* found = searchNode(root, key);
    return found ? &found->data : nullptr;
}
AVLTree::Node* AVLTree::minNode(Node* p) {
    while (p && p->left) p = p->left;
    return p;
}
AVLTree::Node* AVLTree::removeNode(Node* p, const string& key, bool& removed) {
    if (!p) return nullptr;
    string target = Utils::normalize(key);
    string current = Utils::normalize(p->data.word);
    if (target < current) p->left = removeNode(p->left, key, removed);
    else if (target > current) p->right = removeNode(p->right, key, removed);
    else {
        removed = true;
        if (!p->left || !p->right) {
            Node* child = p->left ? p->left : p->right;
            delete p;
            return child;
        }
        Node* successor = minNode(p->right);
        p->data = successor->data;
        bool ignored = false;
        p->right = removeNode(p->right, successor->data.word, ignored);
    }
    return balance(p);
}
bool AVLTree::remove(const string& key) {
    bool removed = false;
    root = removeNode(root, key, removed);
    if (removed) --nodeCount;
    return removed;
}
void AVLTree::printInOrder(Node* p) {
    if (!p) return;
    printInOrder(p->left);
    cout << p->data.word << " - " << p->data.meaning << '\n';
    printInOrder(p->right);
}
void AVLTree::displayInOrder() const {
    if (!root) { cout << "Tu dien dang rong.\n"; return; }
    printInOrder(root);
}
void AVLTree::suggestPrefix(Node* p, const string& prefix, int& count, int limit) {
    if (!p || count >= limit) return;
    string key = Utils::normalize(p->data.word);
    // Cắt nhánh: chỉ đi trái nếu khóa hiện tại >= tiền tố.
    if (key >= prefix) suggestPrefix(p->left, prefix, count, limit);
    if (key.compare(0, prefix.size(), prefix) == 0 && count < limit) {
        cout << p->data.word << " - " << p->data.meaning << '\n';
        ++count;
    }
    // Chỉ cần đi phải khi khóa hiện tại không vượt khỏi vùng tiền tố.
    if (key <= prefix || key.compare(0, prefix.size(), prefix) == 0)
        suggestPrefix(p->right, prefix, count, limit);
}
void AVLTree::suggest(const string& prefix, int limit) const {
    string key = Utils::normalize(prefix);
    if (key.empty()) { cout << "Tien to khong duoc rong.\n"; return; }
    int count = 0;
    suggestPrefix(root, key, count, limit);
    if (count == 0) cout << "Khong tim thay tu phu hop.\n";
}
void AVLTree::writeInOrder(Node* p, ostream& out) {
    if (!p) return;
    writeInOrder(p->left, out);
    out << p->data.word << "\t" << p->data.pos << "\t" << p->data.pronunciation << "\t"
        << p->data.meaning << "\t" << p->data.example << "\t" << p->data.flag << '\n';
    writeInOrder(p->right, out);
}
void AVLTree::printFavorites(Node* p) {
    if (!p) return;
    printFavorites(p->left);
    if (p->data.flag) cout << p->data.word << " - " << p->data.meaning << '\n';
    printFavorites(p->right);
}
void AVLTree::saveToFile(ostream& out) const { writeInOrder(root, out); }
void AVLTree::displayFavorites() const { printFavorites(root); }
void AVLTree::destroy(Node* p) {
    if (!p) return;
    destroy(p->left); destroy(p->right); delete p;
}
void AVLTree::clear() { destroy(root); root = nullptr; nodeCount = 0; }
int AVLTree::size() const { return nodeCount; }
int AVLTree::getLastComparisons() const { return lastComparisons; }
bool AVLTree::isEmpty() const { return root == nullptr; }
