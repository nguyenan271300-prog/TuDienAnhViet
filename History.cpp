#include "History.h"
#include <iostream>
using namespace std;
History::History(int maxItems) : head(nullptr), count(0), limit(maxItems) {}
History::~History() { clear(); }
void History::addSearch(const string& word) {
    if (word.empty() || limit <= 0) return;
    // Neu tu da co trong lich su, bo node cu de tranh lap lai.
    Node* p = head; Node* previous = nullptr;
    while (p) {
        if (p->word == word) {
            if (previous) previous->next = p->next;
            else head = p->next;
            delete p; --count; break;
        }
        previous = p; p = p->next;
    }
    Node* newNode = new Node(word);
    newNode->next = head; head = newNode; ++count;
    if (count > limit) {
        Node* last = head; Node* beforeLast = nullptr;
        while (last->next) { beforeLast = last; last = last->next; }
        if (beforeLast) beforeLast->next = nullptr;
        delete last; --count;
    }
}
void History::display() const {
    if (!head) { cout << "Chua co lich su tim kiem.\n"; return; }
    cout << "\n===== 20 TU TRA GAN NHAT =====\n";
    int i = 1;
    for (Node* p = head; p; p = p->next) cout << i++ << ". " << p->word << '\n';
}
void History::clear() { while (head) { Node* next = head->next; delete head; head = next; } count = 0; }
bool History::isEmpty() const { return head == nullptr; }
int History::size() const { return count; }
