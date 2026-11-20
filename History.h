#ifndef HISTORY_H
#define HISTORY_H
#include <string>
using namespace std;

class History {
private:
    struct Node { string word; Node* next; Node(const string& s) : word(s), next(nullptr) {} };
    Node* head;
    int count;
    int limit;
public:
    explicit History(int maxItems = 20);
    ~History();
    History(const History&) = delete;
    History& operator=(const History&) = delete;
    void addSearch(const string& word);
    void display() const;
    void clear();
    bool isEmpty() const;
    int size() const;
};
#endif
